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

#include "../basic-c/kalman_filter.h"

#define MKL_INT int



void predict1(int A_nrows,   int A_ncols,   double* A, 
           int A2_nrows,  int A2_ncols,  double* A2, 
           int Q_nrows,   int Q_ncols,   double* Q, 
           int xh_nrows,  int xh_ncols,  double* xh, 
           int P_nrows,   int P_ncols,   double* P, 
           int xhn_nrows, int xhn_ncols, double* xhn);

// void predict1(int A_nrows,   int A_ncols,   double* A, 
//               int Y_nrows,   int Y_ncols,   double* Y, 
//               int xh_nrows,  int xh_ncols,  double* xh, 
//               int xhn_nrows, int xhn_ncols, double* xhn);

// void predict2(int A_nrows, int A_ncols, double* A, 
//               int Q_nrows, int Q_ncols, double* Q, 
//               int P_nrows, int P_ncols, double* P);

void correct3a(int C_nrows,    int C_ncols,    double* C, 
               int P_nrows,    int P_ncols,    double* P, 
               int R_nrows,    int R_ncols,    double* R, 
               int temp_nrows, int temp_ncols, double* temp);

void correct3b(int C_nrows,    int C_ncols,    double* C, 
               int P_nrows,    int P_ncols,    double* P, 
               int temp_nrows, int temp_ncols, double* temp, 
               int K_nrows,    int K_ncols,    double* K);

void correct4(int C_nrows,   int C_ncols,   double* C, 
              int I_nrows,   int I_ncols,   double* I, 
              int K_nrows,   int K_ncols,   double* K, 
              int xhn_nrows, int xhn_ncols, double* xhn, 
              int y_nrows,   int y_ncols,   double* y, 
              int P_nrows,   int P_ncols,   double* P, 
              int xh_nrows,  int xh_ncols,  double* xh);

char allocate_matrices(KALMAN_TYPE** A, KALMAN_TYPE** C, KALMAN_TYPE** Q, KALMAN_TYPE** R, KALMAN_TYPE** P, KALMAN_TYPE** K, int n, int m) {

  *A = (KALMAN_TYPE*) malloc(n * n * sizeof(KALMAN_TYPE)); 
  *C = (KALMAN_TYPE*) malloc(m * n * sizeof(KALMAN_TYPE));
  *Q = (KALMAN_TYPE*) malloc(n * n * sizeof(KALMAN_TYPE));
  *R = (KALMAN_TYPE*) malloc(m * m * sizeof(KALMAN_TYPE));
  *P = (KALMAN_TYPE*) malloc(n * n * sizeof(KALMAN_TYPE));
  *K = (KALMAN_TYPE*) malloc(n * m * sizeof(KALMAN_TYPE));

  return !( (*A == 0) || (*C == 0) || (*Q == 0) || (*R == 0) || (*P == 0) || (*K == 0) );

}

char allocate_vectors(KALMAN_TYPE** x, KALMAN_TYPE** y, KALMAN_TYPE** x_hat, int n, int m) {
  *x     = (KALMAN_TYPE*) malloc(n * sizeof(KALMAN_TYPE));
  *y     = (KALMAN_TYPE*) malloc(m * sizeof(KALMAN_TYPE));
  *x_hat = (KALMAN_TYPE*) malloc(n * sizeof(KALMAN_TYPE));

  set_zero(*x_hat, n, 1);

  return !( (*x == 0) || (*y == 0) || (*x_hat == 0) );
}

char allocate_temp_matrices(KALMAN_TYPE** x_hat_new, KALMAN_TYPE** A_T, KALMAN_TYPE** C_T, KALMAN_TYPE** id,
                            KALMAN_TYPE** temp_1, KALMAN_TYPE** temp_2, KALMAN_TYPE** temp_3, KALMAN_TYPE** temp_4, int n, int m) {
  char fail = 0;
  int  size = n > m ? n*n : m*m;

  *x_hat_new = (KALMAN_TYPE*) malloc(n * sizeof(KALMAN_TYPE));     // n x 1
  *A_T       = (KALMAN_TYPE*) malloc(n * n * sizeof(KALMAN_TYPE)); // n x n
  *C_T       = (KALMAN_TYPE*) malloc(n * m * sizeof(KALMAN_TYPE)); // m x n
  *id        = (KALMAN_TYPE*) malloc(n * n * sizeof(KALMAN_TYPE)); // n x n identity  
  set_identity(*id, n, n);
  fail = fail || (x_hat_new == 0) || (A_T == 0) || (C_T == 0) || (id == 0);

  size = size * sizeof(KALMAN_TYPE);
  *temp_1     = (KALMAN_TYPE*) malloc(size); // n x n or m x m if bigger
  *temp_2     = (KALMAN_TYPE*) malloc(size); // n x n or m x m if bigger
  *temp_3     = (KALMAN_TYPE*) malloc(size); // n x n or m x m if bigger
  *temp_4     = (KALMAN_TYPE*) malloc(size); // n x n or m x m if bigger
  fail = fail || (temp_1 == 0) || (temp_2 == 0) || (temp_3 == 0) || (temp_4 == 0);

  return !fail;
}

void destroy_matrices(KALMAN_TYPE* A, KALMAN_TYPE* C, KALMAN_TYPE* Q, KALMAN_TYPE* R, KALMAN_TYPE* P, KALMAN_TYPE* K) {
  free(A);
  free(C);
  free(Q);
  free(R);
  free(P);
  free(K);
}

void destroy_vectors(KALMAN_TYPE* x, KALMAN_TYPE* y, KALMAN_TYPE* x_hat) {
  free(x);
  free(y);
  free(x_hat);
}

void destroy_temp_matrices(KALMAN_TYPE* x_hat_new, KALMAN_TYPE* A_T, KALMAN_TYPE* C_T, KALMAN_TYPE* id,
                           KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2, KALMAN_TYPE* temp_3, KALMAN_TYPE* temp_4) {
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
void update(KALMAN_TYPE* y, KALMAN_TYPE* x_hat, 
            double* t, double dt, int n, int m,
            KALMAN_TYPE* A, KALMAN_TYPE* C, KALMAN_TYPE* Q, KALMAN_TYPE* R, KALMAN_TYPE* P, KALMAN_TYPE* K,
            KALMAN_TYPE* x_hat_new, KALMAN_TYPE* A_T, KALMAN_TYPE* C_T, KALMAN_TYPE* id,
            KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2, KALMAN_TYPE* temp_3, KALMAN_TYPE* temp_4) {

  predict(x_hat, n, m, A, Q, P, 
          x_hat_new, A_T, temp_1, temp_2);

  correct(y, x_hat, n, m, C, R, P, K,
          x_hat_new, C_T, id, temp_1, temp_2, temp_3, temp_4);

}

//@predict the state and update P
//@param
//@post
void predict(KALMAN_TYPE* x_hat, 
            int n, int m,
            KALMAN_TYPE* A, KALMAN_TYPE* Q, KALMAN_TYPE* P,
            KALMAN_TYPE* x_hat_new, KALMAN_TYPE* A_T,
            KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2) {

  int inc = sizeof(KALMAN_TYPE);

  // TODO fix this
  int A_nrows = n;
  int A_ncols = n;
  int Q_nrows = n;
  int Q_ncols = n;
  int P_nrows = n;
  int P_ncols = n;
  int Y_nrows = n;
  int Y_ncols = 1;
  int xh_nrows = n;
  int xh_ncols = 1;
  int xhn_nrows = n;
  int xhn_ncols = 1;

  // int i;
  // for (i = 0; i < Y_nrows*Y_ncols; i++) {
  //  temp_1[i] = 0;
  // } 

  predict1(A_nrows,   A_ncols,   A, 
           A_nrows,   A_ncols,   A, 
           Q_nrows,   Q_ncols,   Q, 
           xh_nrows,  xh_ncols,  x_hat, 
           P_nrows,   P_ncols,   P, 
           xhn_nrows, xhn_ncols, x_hat_new);

  // predict1(A_nrows, A_ncols, A, Y_nrows, Y_ncols, temp_1, xh_nrows, xh_ncols, x_hat, xhn_nrows, xhn_ncols, x_hat_new);
  // predict2(A_nrows, A_ncols, A, Q_nrows, Q_ncols, Q, P_nrows, P_ncols, P);

}

//@correct the filter based on measurement
//@param 
//@post
void correct(KALMAN_TYPE* y, KALMAN_TYPE* x_hat, 
            int n, int m,
            KALMAN_TYPE* C, KALMAN_TYPE* R, KALMAN_TYPE* P, KALMAN_TYPE* K,
            KALMAN_TYPE* x_hat_new, KALMAN_TYPE* C_T, KALMAN_TYPE* id,
            KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2, KALMAN_TYPE* temp_3, KALMAN_TYPE* temp_4) { 

  int info;
  int inc = sizeof(KALMAN_TYPE);

  int C_nrows   = m;
  int C_ncols   = n; 
  int I_nrows   = m;
  int I_ncols   = m; 
  int K_nrows   = n;
  int K_ncols   = m; 
  int xhn_nrows = n;
  int xhn_ncols = 1; 
  int y_nrows   = m;
  int y_ncols   = 1; 
  int P_nrows   = n;
  int P_ncols   = n; 
  int R_nrows    = m;
  int R_ncols    = m; 
  int temp_nrows = m;
  int temp_ncols = m; 
  int xh_nrows   = n;
  int xh_ncols   = 1;

  // K = P*C_T*(C*P*C_T+R)^-1
  correct3a(C_nrows,    C_ncols,    C, 
            P_nrows,    P_ncols,    P, 
            R_nrows,    R_ncols,    R, 
            temp_nrows, temp_ncols, temp_1);
  invert_matrix(temp_1, temp_nrows, temp_2);
  correct3b(C_nrows,    C_ncols,    C, 
            P_nrows,    P_ncols,    P, 
            temp_nrows, temp_ncols, temp_2, 
            K_nrows,    K_ncols,    K);


  // x_hat = x_hat_new + K * (y - C*x_hat_new);
  // P = (I - K*C)*P;
  correct4(C_nrows,   C_ncols,   C, 
           I_nrows,   I_ncols,   id, 
           K_nrows,   K_ncols,   K, 
           xhn_nrows, xhn_ncols, x_hat_new, 
           y_nrows,   y_ncols,   y, 
           P_nrows,   P_ncols,   P, 
           xh_nrows,  xh_ncols,  x_hat);

}


// //@set a matrix to the identity
// //@pre matrix_a has been allocated to rows_a x cols_a
// //@post mat_a has ones in the diagonal and zeros elsewhere
// void set_identity(KALMAN_TYPE* mat_a, int rows_a, int cols_a) {
//   int i, j;
//   int a_row;

//   for (i = 0; i < rows_a; i++) {
//     a_row = cols_a * i;
//     for (j = 0; j < cols_a; j++) {
//       mat_a[a_row + j] = (double)(i == j);
//     }
//   }
// }

// //@deep copy of a to b
// void copy_mat(KALMAN_TYPE* mat_a, KALMAN_TYPE* mat_c, int total_elms) {
//   int i;
//   for (i = 0; i < total_elms; i++)
//     mat_c[i] = mat_a[i];
// }

// //@add a to b
// void add_mats(KALMAN_TYPE* mat_a, KALMAN_TYPE* mat_b, KALMAN_TYPE* mat_c, int total_elms) {
//   int i;
//   for (i = 0; i < total_elms; i++)
//     mat_c[i] = mat_a[i] + mat_b[i];
// }


// void set_zero(KALMAN_TYPE* mat_a, int rows_a, int cols_a) {
//   int i, total_elms = rows_a*cols_a;
//   for (i = 0; i < total_elms; i++)
//     mat_a[i] = 0;
// }
 
// void print_matrix(KALMAN_TYPE* mat_a, int rows_a, int cols_a) {

//   int i, j;

//   for (i = 0; i < rows_a; i++) {
//     for (j = 0; j < cols_a; j++) {
//       printf("%.4f ", mat_a[i * cols_a + j]);
//     }
//     printf("\n\n");
//   }
// }
 