/*
 * matrix_batch.c
 
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

#include "matrix_batch.h"

void init_batch(struct batch* A, int num_mats, int rows, int cols) {
  int i, j; 
  A->num_mats = num_mats;
  A->rows = rows;
  A->cols = cols;

  A->mats = malloc(rows*sizeof(KALMAN_TYPE**));
  for (i = 0; i <  A->rows; i++) {
    A->mats[i] = malloc(cols*sizeof(KALMAN_TYPE*));
    for (int j = 0; j <  A->cols; j++) {
      A->mats[i][j] = malloc(num_mats*sizeof(KALMAN_TYPE));
    }
  }
}


void free_batch(struct batch* A) {

  int i,j;

  for (i = 0; i < A->rows; i++) {
    for (int j = 0; j <  A->cols; j++) {
      free(A->mats[i][j]);
    }
    free(A->mats[i]);
  }
  free(A->mats);

}


void batch_multiply(struct batch* A, struct batch* B, struct batch* C) {

  int i,j,k,l;

  int rows_a = A->rows;
  int rows_b = B->rows;
  int cols_a = A->cols;
  int cols_b = B->cols;
  int num_mats = A->num_mats;

  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_b; j++) {
      for (l = 0; l < num_mats; l++) {
        C->mats[i][j][l] = 0;
      }
    }
  }

  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_b; j++) {
      for (k = 0; k < cols_a; k++) {
        for (l = 0; l < num_mats; l++) {
          C->mats[i][j][l] += A->mats[i][k][l] * B->mats[k][j][l];
        }
      }
    } 
  }

}

void print_matrix(struct batch* A, int mat_id) {

  int i, j;

  for (i = 0; i < A->rows; i++) {
    for (j = 0; j < A->cols; j++) {
      printf("%.4f ", A->mats[i][j][mat_id]);
    }
    printf("\n\n");
  }

}

