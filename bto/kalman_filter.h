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

#ifndef KALMAN_TYPE
#define KALMAN_TYPE double         // DO NOT CHANGE
#endif
#define ORDER CblasRowMajor // matrix layout

#include SYS
// MKL
//#include <mkl_cblas.h>
//#include <mkl_lapacke.h>

// ATLAS maybe openBLAS
// #include <cblas.h> 
// #include <clapack.h>
// #define MKL_INT int
// #define LAPACK_ROW_MAJOR ORDER

#include <stdlib.h>
#include <stdio.h>


//allocate the memory for various matrices used in computation
//params the pointers that have been created to reference mats and vects
//        n is rows and m is cols
//post pointers point to allocated memory
//      enough is allocated for each matrix based on m and n
//      temp matrices are nxn or mxm (whichever is bigger)
//return 0 for failed allocation other for success
//useage call of these before running the filter
//  sorry they're separated I was just trying to stay sane
char allocate_matrices(KALMAN_TYPE** A, KALMAN_TYPE** C, KALMAN_TYPE** Q, KALMAN_TYPE** R, KALMAN_TYPE** P, KALMAN_TYPE** K, int n, int m);
char allocate_vectors(KALMAN_TYPE** x, KALMAN_TYPE** y, KALMAN_TYPE** x_hat, int n, int m);
char allocate_temp_matrices(KALMAN_TYPE** x_hat_new, KALMAN_TYPE** A_T, KALMAN_TYPE** C_T, KALMAN_TYPE** id,
                            KALMAN_TYPE** temp_1, KALMAN_TYPE** temp_2, KALMAN_TYPE** temp_3, KALMAN_TYPE** temp_4, int n, int m);

//liberate the memory for various matrices used in computation
//useage call of these when you are all done with the filter
void destroy_matrices(KALMAN_TYPE* A, KALMAN_TYPE* C, KALMAN_TYPE* Q, KALMAN_TYPE* R, KALMAN_TYPE* P, KALMAN_TYPE* K);
void destroy_vectors(KALMAN_TYPE* x, KALMAN_TYPE* y, KALMAN_TYPE* x_hat);
void destroy_temp_matrices(KALMAN_TYPE* x_hat_new, KALMAN_TYPE* A_T, KALMAN_TYPE* C_T, KALMAN_TYPE* id,
                           KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2, KALMAN_TYPE* temp_3, KALMAN_TYPE* temp_4);

//@update the filter
//@param
//@post
void update(KALMAN_TYPE* y, KALMAN_TYPE* x_hat, 
            double* t, double dt, MKL_INT n, MKL_INT m,
            KALMAN_TYPE* A, KALMAN_TYPE* C, KALMAN_TYPE* Q, KALMAN_TYPE* R, KALMAN_TYPE* P, KALMAN_TYPE* K,
            KALMAN_TYPE* x_hat_new, KALMAN_TYPE* A_T, KALMAN_TYPE* C_T, KALMAN_TYPE* id,
            KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2, KALMAN_TYPE* temp_3, KALMAN_TYPE* temp_4);

void predict(KALMAN_TYPE* x_hat, 
            MKL_INT n, MKL_INT m,
            KALMAN_TYPE* A, KALMAN_TYPE* Q, KALMAN_TYPE* P,
            KALMAN_TYPE* x_hat_new, KALMAN_TYPE* A_T,
            KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2);

void predict1(int A_nrows,   int A_ncols,   double* A, 
              int Y_nrows,   int Y_ncols,   double* Y, 
              int xh_nrows,  int xh_ncols,  double* xh, 
              int xhn_nrows, int xhn_ncols, double* xhn);

void predict2(int A_nrows, int A_ncols, double* A, 
              int Q_nrows, int Q_ncols, double* Q, 
              int P_nrows, int P_ncols, double* P);

void correct(KALMAN_TYPE* y, KALMAN_TYPE* x_hat, 
            MKL_INT n, MKL_INT m,
            KALMAN_TYPE* C, KALMAN_TYPE* R, KALMAN_TYPE* P, KALMAN_TYPE* K,
            KALMAN_TYPE* x_hat_new, KALMAN_TYPE* C_T, KALMAN_TYPE* id,
            KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2, KALMAN_TYPE* temp_3, KALMAN_TYPE* temp_4);



//@set a matrix to the identity
//@pre matrix_a has been allocated to rows_a x cols_a
//@post mat_a has ones in the diagonal and zeros elsewhere
void set_identity(KALMAN_TYPE* mat_a, int rows_a, int cols_a);

//@deep copy of a to b
void copy_mat(KALMAN_TYPE* mat_a, KALMAN_TYPE* mat_c, int total_elms);

//@add a to b
void add_mats(KALMAN_TYPE* mat_a, KALMAN_TYPE* mat_b, KALMAN_TYPE* mat_c, int total_elms);

void set_zero(KALMAN_TYPE* mat_a, int rows_a, int cols_a);

void print_matrix(KALMAN_TYPE* mat_a, int rows_a, int cols_a);

#endif
