/*
 * kalman_filter.c
 * super basic Kalman filter implementation
 
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

#include "../kalman_filter.h"

    
//set a matrix to zero
//pre matrix_a has been allocated to rows_a x cols_a
//post mat_a is all zeros
void set_zero(TYPE* mat_a, int rows_a, int cols_a) {
  int i, j;
  int a_row;

  for (i = 0; i < rows_a; i++) {
    a_row = cols_a * i;
    for (j = 0; j < cols_a; j++) {
      mat_a[a_row + j] = 0;
    }
  }
}

//set a matrix to the identity
//pre matrix_a has been allocated to rows_a x cols_a
//post mat_a has ones in the diagonal and zeros elsewhere
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

//deep copy of a to b
void copy_mat(TYPE* mat_a, TYPE* mat_c, int total_elms) {
  int i;
  for (i = 0; i < total_elms; i++)
    mat_c[i] = mat_a[i];
}

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

void update(TYPE* y, TYPE* x_hat, 
            double* t, double dt, int n, int m,
            TYPE* A, TYPE* C, TYPE* Q, TYPE* R, TYPE* P, TYPE* K,
            TYPE* x_hat_new, TYPE* A_T, TYPE* C_T, TYPE* id,
            TYPE* temp_1, TYPE* temp_2, TYPE* temp_3, TYPE* temp_4) {

  predict(x_hat, n, m, A, Q, P, 
          x_hat_new, A_T, temp_1, temp_2);
  correct(y, x_hat, n, m, C, R, P, K,
          x_hat_new, C_T, id, temp_1, temp_2, temp_3, temp_4);

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

