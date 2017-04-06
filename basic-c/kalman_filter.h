/*
 * kalman_filter.c
 * super basic Kalman filter implementation
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

 * Things that need to be established
    n - one dimension of the matrix
    m - the other dimension

    A - something to do with the system model?
    C - H matrix - the measurement one
    Q - noise covariance 
    R - 
    P - error covariance 
    K

    x  - estimated state
    xp - the next prediction

    t  - time
    dt - time step
*/

#define TYPE double


void allocate_matrices(TYPE* &A, TYPE* &C, TYPE* &Q, TYPE* &R, TYPE* &P, TYPE* &K, int n, int m);

void allocate_vectors(TYPE* &x, TYPE* &y, TYPE* &x_hat, int n);

void destroy_matrices(TYPE* &A, TYPE* &C, TYPE* &Q, TYPE* &R, TYPE* &P, TYPE* &K);

void destroy_vectors(TYPE* &x, TYPE* &x_hat);

//@update the filter
//@param y is a vector same size as x and x_hat
//@post
//TODO fix m and n
//TODO maybe make more thn one funciton
void update(TYPE* &y, TYPE* &x_hat, 
            double &t, double dt, int n, int m,
            TYPE* &A, TYPE* &C, TYPE* &Q, TYPE* &R, TYPE* &P, TYPE* &K);