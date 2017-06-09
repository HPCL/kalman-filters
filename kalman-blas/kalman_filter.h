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

    x     - estimated state n x 1
    x_hat - the next prediction n x 1
    y     - measurements m

    t  - time
    dt - time step
*/

#ifndef KALMAN_FILTER
#define KALMAN_FILTER


#define TYPE double         // DO NOT CHANGE
#define ORDER CblasRowMajor // matrix layout

#include <cblas.h>
//#include <mkl_blas.h> //maybe
#include <stdlib.h>
#include <stdio.h>

//@allocate the memory for various matrices used in computation
//@params the pointers that have been created to reference mats and vects
//        n is rows and m is cols
//@post pointers point to allocated memory
//      enough is allocated for each matrix based on m and n
//      temp matrices are nxn or mxm (whichever is bigger)
//@return 0 for failed allocation other for success
//@useage call of these before running the filter
//  sorry they're separated I was just trying to stay sane
char allocate_matrices(TYPE** A, TYPE** C, TYPE** Q, TYPE** R, TYPE** P, TYPE** K, MKL_INT n, MKL_INT m);
char allocate_vectors(TYPE** x, TYPE** y, TYPE** x_hat, MKL_INT n, MKL_INT m);
char allocate_temp_matrices(TYPE** x_hat_new, TYPE** A_T, TYPE** C_T, TYPE** id,
                            TYPE** temp_1, TYPE** temp_2, TYPE** temp_3, TYPE** temp_4, MKL_INT n, MKL_INT m);

//@liberate the memory for various matrices used in computation
//@useage call of these when you are all done with the filter
void destroy_matrices(TYPE* A, TYPE* C, TYPE* Q, TYPE* R, TYPE* P, TYPE* K);
void destroy_vectors(TYPE* x, TYPE* y, TYPE* x_hat);
void destroy_temp_matrices(TYPE* x_hat_new, TYPE* A_T, TYPE* C_T, TYPE* id,
                           TYPE* temp_1, TYPE* temp_2, TYPE* temp_3, TYPE* temp_4);

//@update the filter
//@param
//@post
void update(TYPE* y, TYPE* x_hat, 
            double* t, double dt, MKL_INT n, MKL_INT m,
            TYPE* A, TYPE* C, TYPE* Q, TYPE* R, TYPE* P, TYPE* K,
            TYPE* x_hat_new, TYPE* A_T, TYPE* C_T, TYPE* id,
            TYPE* temp_1, TYPE* temp_2, TYPE* temp_3, TYPE* temp_4);

void predict(TYPE* x_hat, 
            MKL_INT n, MKL_INT m,
            TYPE* A, TYPE* Q, TYPE* P,
            TYPE* x_hat_new, TYPE* A_T,
            TYPE* temp_1, TYPE* temp_2);

void correct(TYPE* y, TYPE* x_hat, 
            MKL_INT n, MKL_INT m,
            TYPE* C, TYPE* R, TYPE* P, TYPE* K,
            TYPE* x_hat_new, TYPE* C_T, TYPE* id,
            TYPE* temp_1, TYPE* temp_2, TYPE* temp_3, TYPE* temp_4);


//@set a matrix to the identity
//@pre matrix_a has been allocated to rows_a x cols_a
//@post mat_a has ones in the diagonal and zeros elsewhere
void set_identity(TYPE* mat_a, int rows_a, int cols_a);

//@deep copy of a to b
void copy_mat(TYPE* mat_a, TYPE* mat_c, int total_elms);

//@add a to b
void add_mats(TYPE* mat_a, TYPE* mat_b, TYPE* mat_c, int total_elms);

#endif