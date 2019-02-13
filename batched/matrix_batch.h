/*
 * matrix_batch.h
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * this is code for batched matrix operations
 * the key is that the matrices are held in a 3D array
 *   - the 3rd dimension is which matrix it belongs to
 *   - this allows the operations to be SIMDized 

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#ifndef MATRIX_BATCH_H
#define MATRIX_BATCH_H

#include <stdio.h>
#include <stdlib.h>

#ifndef KALMAN_TYPE
#define KALMAN_TYPE double // in retrospect this will probably always be double
#endif

struct batch
{
  int num_mats;  // number of matrices
  int rows;      // number of rows
  int cols;      // number of columns
  KALMAN_TYPE*** mats; //will be n X m X num_mats
};

void init_batch(struct batch* b, int num_mats, int n, int m);
void free_batch(struct batch* b);

//Tuned helper funciton
void _multiply_matrix_batch(KALMAN_TYPE*** A, int rows_a, int cols_a,
                            KALMAN_TYPE*** B, int rows_b, int cols_b,
                            KALMAN_TYPE*** C,
                            int num_mats);

void invert_matrix_2x2_batch(struct batch* A, struct batch* C);
void batch_multiply(struct batch* A, struct batch* B, struct batch* C);
void multiply_matrix_batch(struct batch* A, struct batch* B, struct batch* C);
void multiply_matrix_by_scalar_batch(struct batch* A, struct batch* C, KALMAN_TYPE s[]);
void add_matrix_batch(struct batch* A, struct batch* B, struct batch* C);
void transpose_matrix_batch(struct batch* A, struct batch* C);

void print_batch(struct batch* A, int mat_id);
void copy_mat_batch(struct batch* A, struct batch* C);
void set_identity_batch(struct batch* A);
void set_zero_batch(struct batch* A);


#endif
