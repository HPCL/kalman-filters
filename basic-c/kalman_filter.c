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

#include "kalman_filter.h"

// temporary matrices for computation
TYPE* x_hat_new; // n x 1
TYPE* nx1_1;     // n x 1
TYPE* nx1_2;     // n x 1

TYPE* A_T;       // n x n
TYPE* C_T;       // m x n

TYPE* nxn_1;     // n x n
TYPE* nxn_2;     // n x n

TYPE* mxn_1;     // m x n
TYPE* mxn_2;     // m x n

TYPE* nxm_1;     // n x m
TYPE* nxm_2;     // n x m

TYPE* mx1_1;     // m x 1
TYPE* mx1_2;     // m x 1

TYPE* mxm_1;     // m x m
TYPE* mxm_2;     // m x m

TYPE* id;        // m x m identity

char allocate_matrices(TYPE** A, TYPE** C, TYPE** Q, TYPE** R, TYPE** P, TYPE** K, int n, int m) {

  *A = (TYPE*) malloc(n * n * sizeof(TYPE)); //TODO make these global or something?
  *C = (TYPE*) malloc(m * n * sizeof(TYPE));
  *Q = (TYPE*) malloc(n * n * sizeof(TYPE));
  *R = (TYPE*) malloc(m * m * sizeof(TYPE));
  *P = (TYPE*) malloc(n * n * sizeof(TYPE));
  *K = (TYPE*) malloc(n * m * sizeof(TYPE)); //TODO tis might be n x 1

  return !( (*A == 0) || (*C == 0) || (*Q == 0) || (*R == 0) || (*P == 0) || (*K == 0) );

}

char allocate_vectors(TYPE** x, TYPE** y, TYPE** x_hat, int n, int m) {
  *x     = (TYPE*) malloc(n * sizeof(TYPE));
  *y     = (TYPE*) malloc(m * sizeof(TYPE));
  *x_hat = (TYPE*) malloc(n * sizeof(TYPE));

  set_zero(*x_hat, n, 1);

  return !( (*x == 0) || (*y == 0) || (*x_hat == 0) );
}

char allocate_temp_matrices(int n, int m) {
  char fail = 0;
  x_hat_new = (TYPE*) malloc(n * sizeof(TYPE));     // n x 1
  nx1_1     = (TYPE*) malloc(n * sizeof(TYPE));     // n x 1
  nx1_2     = (TYPE*) malloc(n * sizeof(TYPE));     // n x 1
  fail = fail || (x_hat_new == 0) || (nx1_1 == 0) || (nx1_2 == 0);

  A_T       = (TYPE*) malloc(n * n * sizeof(TYPE)); // n x n
  C_T       = (TYPE*) malloc(n * m * sizeof(TYPE)); // m x n
  fail = fail || (A_T == 0) || (C_T == 0);

  nxn_1     = (TYPE*) malloc(n * n * sizeof(TYPE)); // n x n
  nxn_2     = (TYPE*) malloc(n * n * sizeof(TYPE)); // n x n
  fail = fail || (nxn_1 == 0) || (nxn_2 == 0);

  mxn_1     = (TYPE*) malloc(n * m * sizeof(TYPE)); // m x n
  mxn_2     = (TYPE*) malloc(n * m * sizeof(TYPE)); // m x n
  fail = fail || (mxn_1 == 0) || (mxn_2 == 0);

  nxm_1     = (TYPE*) malloc(n * m * sizeof(TYPE)); // n x m
  nxm_2     = (TYPE*) malloc(n * m * sizeof(TYPE)); // n x m
  fail = fail || (nxm_1 == 0) || (nxm_2 == 0);

  mx1_1     = (TYPE*) malloc(m * sizeof(TYPE));     // m x 1
  mx1_2     = (TYPE*) malloc(m * sizeof(TYPE));     // m x 1
  fail = fail || (mx1_1 == 0) || (mx1_2 == 0);

  mxm_1     = (TYPE*) malloc(m * m * sizeof(TYPE)); // m x m
  mxm_2     = (TYPE*) malloc(m * m * sizeof(TYPE)); // m x m
  fail = fail || (mxm_1 == 0) || (mxm_2 == 0);
  
  id        = (TYPE*) malloc(n * n * sizeof(TYPE)); // n x n identity
  fail = fail || (id == 0);

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

void destroy_temp_matrices() {
  free(x_hat_new);
  free(nx1_1);
  free(nx1_2);
  free(A_T);
  free(C_T);
  free(nxn_1);
  free(nxn_2);
  free(mxn_1);
  free(mxn_2);
  free(nxm_1);
  free(nxm_2);
  free(mx1_1);
  free(mx1_2);
  free(mxm_1);
  free(mxm_2);
  free(id);
}

//@update the filter
//@param y is a vector same size as x and x_hat
//@post
//TODO maybe make more thn one funciton
void update(TYPE* y, TYPE* x_hat, 
            double* t, double dt, int n, int m,
            TYPE* A, TYPE* C, TYPE* Q, TYPE* R, TYPE* P, TYPE* K) {

  set_identity(id, n, n);
  transpose_matrix(A, n, n, A_T);
  transpose_matrix(C, m, n, C_T);  

  //x_hat_new = A * x_hat
  multiply_matrix(A, n, n, x_hat, 1, x_hat_new);

  //P = A*P*A_T + Q;
  multiply_matrix(A, n, n, P, n, nxn_1);
  multiply_matrix(nxn_1, n, n, A_T, n, nxn_2);
  add_matrix(nxn_2, n, n, Q, P);

  // K = P*C_T*(C*P*C_T+R)^-1
  multiply_matrix(C, m, n, P, n, mxn_1);
  multiply_matrix(mxn_1, m, n, C_T, n, mxm_1);
  invert_matrix(mxm_1, m, mxm_2); // (C*P*C_T+R)^-1
  multiply_matrix(P, n, n, C_T, m, nxm_1); // P*C_T
  multiply_matrix(nxm_1, n, m, mxm_2, m, K);

  // x_hat = x_hat_new + K * (y - C*x_hat_new);
  multiply_matrix(C, m, n, x_hat_new, 1, mx1_1);
  multiply_matrix_by_scalar(mx1_1, m, 1, -1, mx1_2);
  add_matrix(y, m, 1, mx1_2, mx1_1);
  multiply_matrix(K, n, m, mx1_1, 1, nx1_2);
  add_matrix(x_hat_new, n, 1, nx1_2, x_hat);

  // P = (I - K*C)*P;
  multiply_matrix(K, n, m, C, n, nxn_1);
  multiply_matrix_by_scalar(nxn_1, n, n, -1, nxn_2);
  add_matrix(id, n, n, nxn_2, nxn_1);
  multiply_matrix(nxn_1, n, n, P, n, nxn_2);
  copy_mat(nxn_2, P, n * n);

  *t += dt; //TODO should this be moved outside the filter?
}


