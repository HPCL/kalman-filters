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

void allocate_matrices(TYPE* &A, TYPE* &C, TYPE* &Q, TYPE* &R, TYPE* &P, TYPE* &K, int n, int m) {

  A = malloc(n * n * sizeof(TYPE)); //TODO make these global or something?
  C = malloc(m * n * sizeof(TYPE));
  Q = malloc(n * n * sizeof(TYPE));
  R = malloc(m * m * sizeof(TYPE));
  P = malloc(n * n * sizeof(TYPE));
  K = malloc(n * m * sizeof(TYPE));

}

void allocate_vectors(TYPE* &x, TYPE* &y, TYPE* &x_hat, int n, int m) {
  x     = malloc(n * sizeof(TYPE));
  y     = malloc(m * sizeof(TYPE));
  x_hat = malloc(n * sizeof(TYPE));

  set_zero(x_hat, n, 1);
}

void destroy_matrices(TYPE* &A, TYPE* &C, TYPE* &Q, TYPE* &R, TYPE* &P, TYPE* &K) {
  free A;
  free C;
  free Q;
  free R;
  free P;
  free K;
}

void destroy_vectors(TYPE* &x, TYPE* &x_hat) {
  free x;
  free y;
  free x_hat;
}

//@update the filter
//@param y is a vector same size as x and x_hat
//@post
//TODO maybe make more thn one funciton
void update(TYPE* &y, TYPE* &x_hat, 
            double &t, double dt, int n, int m,
            TYPE* &A, TYPE* &C, TYPE* &Q, TYPE* &R, TYPE* &P, TYPE* &K) {

  //TODO make function?
  TYPE* x_hat_new = (TYPE*) malloc(n * sizeof(TYPE)); // n x 1
  TYPE* nx1_1   = (TYPE*) malloc(n * sizeof(TYPE));   // n x 1
  TYPE* nx1_2   = (TYPE*) malloc(n * sizeof(TYPE));   // n x 1

  TYPE* A_T       = (TYPE*) malloc(n * n * sizeof(TYPE)); // n x n
  TYPE* C_T       = (TYPE*) malloc(n * m * sizeof(TYPE)); // m x n

  TYPE* nxn_1     = (TYPE*) malloc(n * n * sizeof(TYPE)); // n x n
  TYPE* nxn_2     = (TYPE*) malloc(n * n * sizeof(TYPE)); // n x n

  TYPE* mxn_1     = (TYPE*) malloc(n * m * sizeof(TYPE)); // m x n
  TYPE* mxn_2     = (TYPE*) malloc(n * m * sizeof(TYPE)); // m x n

  TYPE* nxm_1     = (TYPE*) malloc(n * m * sizeof(TYPE)); // n x m
  TYPE* nxm_2     = (TYPE*) malloc(n * m * sizeof(TYPE)); // n x m

  TYPE* mx1_1     = (TYPE*) malloc(m * sizeof(TYPE)); // m x 1
  TYPE* mx1_2     = (TYPE*) malloc(m * sizeof(TYPE)); // m x 1

  TYPE* mxm_1     = (TYPE*) malloc(m * m * sizeof(TYPE)); // m x m
  TYPE* mxm_2     = (TYPE*) malloc(m * m * sizeof(TYPE)); // m x m
  
  TYPE* id        = (TYPE*) malloc(n * m * sizeof(TYPE)); // n x n identity

  set_identity(id, n, m);
  transpose_matrix(A, n, m, A_T);
  transpose_matrix(C, n, m, C_T);  

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
  multiply_matrix(P, n, n, C_T, m, mxn_1); // P*C_T
  multiply_matrix(mxn_1, m, n, mxm_2, m, K);

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

  t += dt;

  free x_hat_new;
  free nx1_1;
  free nx1_2;
  free A_T;
  free C_T;
  free nxn_1;
  free nxn_2;
  free mxn_1;
  free mxn_2;
  free nxm_1;
  free nxm_2;
  free mx1_1;
  free mx1_2;
  free mxm_1;
  free mxm_2;
  free id;
}
