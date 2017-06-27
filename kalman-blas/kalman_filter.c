/*
 * kalman_filter.c
 * super basic Kalman filter implementation
 * using LAPACK and BLAS and MKL
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff
 * this code is based heavily on a version by Hayk Martirosyan
 *    https://github.com/hmartiro/kalman-cpp

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

 * Things that need to be established
    n - num states
    m - num measurements

    A - system dynamics nxn
    C - H matrix - the measurement one, also output? mxn
    Q - process noise covariance nxn
    R - measurement noise covariance mxm
    P - error covariance nxn
    K - kalman gain nxm

    x     - estimated state n x m
    x_hat - the next prediction n x m
    y     - measurements m

    t  - time
    dt - time step
*/

#include "kalman_filter.h"

char allocate_matrices(TYPE** A, TYPE** C, TYPE** Q, TYPE** R, TYPE** P, TYPE** K, int n, int m) {

  *A = (TYPE*) malloc(n * n * sizeof(TYPE)); 
  *C = (TYPE*) malloc(m * n * sizeof(TYPE));
  *Q = (TYPE*) malloc(n * n * sizeof(TYPE));
  *R = (TYPE*) malloc(m * m * sizeof(TYPE));
  *P = (TYPE*) malloc(n * n * sizeof(TYPE));
  *K = (TYPE*) malloc(n * m * sizeof(TYPE));

  return !( (*A == 0) || (*C == 0) || (*Q == 0) || (*R == 0) || (*P == 0) || (*K == 0) );

}

char allocate_vectors(TYPE** x, TYPE** y, TYPE** x_hat, int n, int m) {
  *x     = (TYPE*) malloc(n * sizeof(TYPE));
  *y     = (TYPE*) malloc(m * sizeof(TYPE));
  *x_hat = (TYPE*) malloc(n * sizeof(TYPE));

  set_zero(*x_hat, n, 1);

  return !( (*x == 0) || (*y == 0) || (*x_hat == 0) );
}

char allocate_temp_matrices(TYPE** x_hat_new, TYPE** A_T, TYPE** C_T, TYPE** id,
                            TYPE** temp_1, TYPE** temp_2, TYPE** temp_3, TYPE** temp_4, int n, int m) {
  char fail = 0;
  int  size = n > m ? n*n : m*m;

  *x_hat_new = (TYPE*) malloc(n * sizeof(TYPE));     // n x 1
  *A_T       = (TYPE*) malloc(n * n * sizeof(TYPE)); // n x n
  *C_T       = (TYPE*) malloc(n * m * sizeof(TYPE)); // m x n
  *id        = (TYPE*) malloc(n * n * sizeof(TYPE)); // n x n identity  
  set_identity(*id, n, n);
  fail = fail || (x_hat_new == 0) || (A_T == 0) || (C_T == 0) || (id == 0);

  size = size * sizeof(TYPE);
  *temp_1     = (TYPE*) malloc(size); // n x n or m x m if bigger
  *temp_2     = (TYPE*) malloc(size); // n x n or m x m if bigger
  *temp_3     = (TYPE*) malloc(size); // n x n or m x m if bigger
  *temp_4     = (TYPE*) malloc(size); // n x n or m x m if bigger
  fail = fail || (temp_1 == 0) || (temp_2 == 0) || (temp_3 == 0) || (temp_4 == 0);

  return !fail;
}

void destroy_matrices(TYPE* A, TYPE* C, TYPE* Q, TYPE* R, TYPE* P, TYPE* K) {
  free(A);
  free(C);
  free(Q);
  free(R);
  free(P);
  free(K);
}

void destroy_vectors(TYPE* x, TYPE* y, TYPE* x_hat) {
  free(x);
  free(y);
  free(x_hat);
}

void destroy_temp_matrices(TYPE* x_hat_new, TYPE* A_T, TYPE* C_T, TYPE* id,
                           TYPE* temp_1, TYPE* temp_2, TYPE* temp_3, TYPE* temp_4) {
  free(x_hat_new);
  free(A_T);
  free(C_T);
  free(id);
  free(temp_1);
  free(temp_2);
  free(temp_3);
  free(temp_4);
}

//@update the filter
//@param y is a vector same size as x and x_hat
//@post
//TODO maybe make more thn one funciton
void update(TYPE* y, TYPE* x_hat, 
            double* t, double dt, MKL_INT n, MKL_INT m,
            TYPE* A, TYPE* C, TYPE* Q, TYPE* R, TYPE* P, TYPE* K,
            TYPE* x_hat_new, TYPE* A_T, TYPE* C_T, TYPE* id,
            TYPE* temp_1, TYPE* temp_2, TYPE* temp_3, TYPE* temp_4) {

  predict(x_hat, n, m, A, Q, P, 
          x_hat_new, A_T, temp_1, temp_2);

  correct(y, x_hat, n, m, C, R, P, K,
          x_hat_new, C_T, id, temp_1, temp_2, temp_3, temp_4);

}

//@predict the state and update P
//@param
//@post
void predict(TYPE* x_hat, 
            MKL_INT n, MKL_INT m,
            TYPE* A, TYPE* Q, TYPE* P,
            TYPE* x_hat_new, TYPE* A_T,
            TYPE* temp_1, TYPE* temp_2) {

  MKL_INT inc = sizeof(TYPE);

  //x_hat_new = A * x_hat
  cblas_dgemv(ORDER, CblasNoTrans, n, n, 1, A, n, x_hat, 1, 0, x_hat_new, 1);

  //P = A*P*A_T + Q;
  cblas_dgemm(ORDER, CblasNoTrans, CblasNoTrans, n, n, n, 1, A, n, P, n, 0, temp_1, n);
  cblas_dgemm(ORDER, CblasNoTrans, CblasTrans, n, n, n, 1, temp_1, n, A, n, 0, temp_2, n);
  add_mats(temp_2, Q, P, n*n);
}

//@correct the filter based on measurement
//@param 
//@post
void correct(TYPE* y, TYPE* x_hat, 
            MKL_INT n, MKL_INT m,
            TYPE* C, TYPE* R, TYPE* P, TYPE* K,
            TYPE* x_hat_new, TYPE* C_T, TYPE* id,
            TYPE* temp_1, TYPE* temp_2, TYPE* temp_3, TYPE* temp_4) { 

  MKL_INT info;
  MKL_INT inc = sizeof(TYPE);
  long long ipiv[m*m];

  // K = P*C_T*(C*P*C_T+R)^-1
  cblas_dgemm(ORDER, CblasNoTrans, CblasNoTrans, m, n, n, 1, C, n, P, n, 0, temp_1, n);
  cblas_dgemm(ORDER, CblasNoTrans, CblasTrans, m, m, n, 1, temp_1, n, C, n, 0, temp_2, m);
  add_mats(temp_2, R, temp_1, m*m);  
  LAPACKE_dgetrf(LAPACK_ROW_MAJOR,m,m,temp_1,m,ipiv);
  LAPACKE_dgetri(LAPACK_ROW_MAJOR,m,temp_1,m,ipiv); // (C*P*C_T+R)^-1
  cblas_dgemm(ORDER, CblasNoTrans, CblasTrans, n, m, n, 1, P, n, C, n, 0, temp_2, m); // P*C_T
  cblas_dgemm(ORDER, CblasNoTrans, CblasNoTrans, n, m, m, 1, temp_2, m, temp_1, m, 0, K, m);

  // x_hat = x_hat_new + K * (y - C*x_hat_new);
  cblas_dgemv (ORDER, CblasNoTrans, m, n, -1, C, n, x_hat_new, 1, 0, temp_3, 1);
  add_mats(y, temp_3, temp_4, m);
  cblas_dgemv (ORDER, CblasNoTrans, n, m, 1, K, m, temp_4, 1, 0, temp_3, 1);
  add_mats(x_hat_new, temp_3, x_hat, n);

  // P = (I - K*C)*P;
  cblas_dgemm(ORDER, CblasNoTrans, CblasNoTrans, n, n, m, -1, K, m, C, n, 0, temp_1, n);
  add_mats(id, temp_1, temp_2, n*n);
  cblas_dgemm(ORDER, CblasNoTrans, CblasNoTrans, n, n, n, 1, temp_2, n, P, n, 0, temp_1, n);
  copy_mat(temp_1, P, n * n);
}


//@set a matrix to the identity
//@pre matrix_a has been allocated to rows_a x cols_a
//@post mat_a has ones in the diagonal and zeros elsewhere
void set_identity(TYPE* mat_a, int rows_a, int cols_a) {
  int i, j;
  int a_row;

  for (i = 0; i < rows_a; i++) {
    a_row = cols_a * i;
    for (j = 0; j < cols_a; j++) {
      mat_a[a_row + j] = (double)(i == j);
    }
  }
}

//@deep copy of a to b
void copy_mat(TYPE* mat_a, TYPE* mat_c, int total_elms) {
  int i;
  for (i = 0; i < total_elms; i++)
    mat_c[i] = mat_a[i];
}

//@add a to b
void add_mats(TYPE* mat_a, TYPE* mat_b, TYPE* mat_c, int total_elms) {
  int i;
  for (i = 0; i < total_elms; i++)
    mat_c[i] = mat_a[i] + mat_b[i];
}


void set_zero(TYPE* mat_a, int rows_a, int cols_a) {
  int i, total_elms = rows_a*cols_a;
  for (int i = 0; i < total_elms; i++)
    mat_a[i] = 0;
}
 
void print_matrix(TYPE* mat_a, int rows_a, int cols_a) {

  int i, j;

  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_a; j++) {
      printf("%.4f ", mat_a[i * cols_a + j]);
    }
    printf("\n\n");
  }
}
 