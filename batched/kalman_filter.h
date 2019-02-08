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

#include "linear_algebra.h"
#include <stdlib.h>
#include <stdio.h>


#ifdef USE_CALI
#include <caliper/cali.h>
#endif

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

//update the filter
//param
//post
void update(KALMAN_TYPE* y, KALMAN_TYPE* x_hat, 
            double* t, double dt, int n, int m,
            KALMAN_TYPE* A, KALMAN_TYPE* C, KALMAN_TYPE* Q, KALMAN_TYPE* R, KALMAN_TYPE* P, KALMAN_TYPE* K,
            KALMAN_TYPE* x_hat_new, KALMAN_TYPE* A_T, KALMAN_TYPE* C_T, KALMAN_TYPE* id,
            KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2, KALMAN_TYPE* temp_3, KALMAN_TYPE* temp_4);

void predict(KALMAN_TYPE* x_hat, 
            int n, int m,
            KALMAN_TYPE* A, KALMAN_TYPE* Q, KALMAN_TYPE* P,
            KALMAN_TYPE* x_hat_new, KALMAN_TYPE* A_T,
            KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2);

void correct(KALMAN_TYPE* y, KALMAN_TYPE* x_hat, 
            int n, int m,
            KALMAN_TYPE* C, KALMAN_TYPE* R, KALMAN_TYPE* P, KALMAN_TYPE* K,
            KALMAN_TYPE* x_hat_new, KALMAN_TYPE* C_T, KALMAN_TYPE* id,
            KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2, KALMAN_TYPE* temp_3, KALMAN_TYPE* temp_4);

#endif