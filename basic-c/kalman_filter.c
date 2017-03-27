/*
 * kalman_filter.c
 * super basic Kalman filter implementation
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate or introductions to potential employers.

 * Things that need to be established
    n - one dimension of the matrix
    m - the other dimension

    A - these are all matrices of the same size
    C - I have no idea what the difference is between them
    Q
    R
    P
    K

    x  - estimated state
    xp - the next prediction

    t  - time
    dt - time step
*/

#define TYPE double


void allocate_matrices(TYPE* &A, TYPE* &C, TYPE* &Q, TYPE* &R, TYPE* &P, TYPE* &K, int n, int m) {

  int size = n * m;

  A = malloc(size * sizeof(TYPE)); //TODO make these global or something?
  C = malloc(size * sizeof(TYPE));
  Q = malloc(size * sizeof(TYPE));
  R = malloc(size * sizeof(TYPE));
  P = malloc(size * sizeof(TYPE));
  K = malloc(size * sizeof(TYPE));

  x_hat.setZero();
  P = P0;
  t0 = 0;
  t = t0;
}

void allocate_vectors(TYPE* &x, TYPE* &y, TYPE* &x_hat, int n) {
  x     = malloc(n * sizeof(TYPE));
  y     = malloc(n * sizeof(TYPE));
  x_hat = malloc(n * sizeof(TYPE));
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

void prediction() {
  //TODO figure out what to do with this
}

//@update the filter
//@param y is a vector same size as x and x_hat
//@post
//TODO fix m and n
//TODO understand what is going on with this math
void update(TYPE* &y, TYPE* &x_hat, 
            double &t, double dt, int n, int m,
            TYPE* &A, TYPE* &C, TYPE* &Q, TYPE* &R, TYPE* &P, TYPE* &K) {

  //TODO make function?
  x_hat_new = malloc(n * sizeof(TYPE));
  temp_v1   = malloc(n * sizeof(TYPE));
  temp_v2   = malloc(n * sizeof(TYPE));

  A_T    = malloc(n * m * sizeof(TYPE));
  C_T    = malloc(n * m * sizeof(TYPE));
  temp_1 = malloc(n * m * sizeof(TYPE));
  temp_2 = malloc(n * m * sizeof(TYPE));
  id     = malloc(n * m * sizeof(TYPE));

  set_identity(id, n, m);
  transpose_matrix(A, n, m, A_T);
  transpose_matrix(C, n, m, C_T);  

  multiply_matrix(A, n, m, x_hat, 1, x_hat_new);

  //P = A*P*A_T + Q;
  multiply_matrix(A, n, m, P, n, temp_1);
  multiply_matrix(temp_1, n, m, A_T, n, temp_2);
  add_matrix(temp_2, n, m, Q, P);

  // K = P*C_T*(C*P*C_T+R)^-1
  multiply_matrix(C, n, m, P, n, temp_1);
  multiply_matrix(temp_1, n, m, C_T, n, temp_2);
  invert_matrix(temp_2, n, temp_1); // (C*P*C_T+R)^-1
  multiply_matrix(P, n, m, C_T, n, temp_2); // P*C_T
  multiply_matrix(temp_2, n, m, temp_1, n, K);

  // x_hat = x_hat_new + K * (y - C*x_hat_new);
  multiply_matrix(C, n, m, x_hat_new, 1, temp_v1);
  multiply_matrix_by_scalar(temp_v1, n, 1, -1, temp_v2);
  add_matrix(y, n, 1, temp_v2, temp_v1);
  multiply_matrix(K, n, m, temp_v1, 1, temp_v2);
  add_matrix(x_hat_new, n, 1, temp_v2, x_hat);

  // P = (I - K*C)*P;
  multiply_matrix(K, n, m, C, n, temp_1);
  multiply_matrix_by_scalar(temp_1, n, m, -1, temp_2);
  add_matrix(id, n, m, temp_2, temp_1);
  multiply_matrix(temp_1, n, m, P, n, temp_2);
  copy_mat(temp_2, P, n * m);

  t += dt;

  free x_hat_new;
  free temp_v1;
  free temp_v2;

  free A_T;
  free C_T;
  free temp_1;
  free temp_2;
  free id;
}
