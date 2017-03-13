/*
 * linear_algebra.c
 * simple code for matrix funcitons
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate or introductions to potential employers.

*/

#include "linear_algebra.h"
 
void print_matrix(TYPE* mat_a, int rows_a, int cols_a) {

  int i, j;

  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_a; j++) {
      printf("%4.1f ", mat_a[i * cols_a + j]);
    }
    printf("\n\n");
  }
}
 
// void invert_matrix() {

// }

//@multiply matrices together
//@pre all matrices are initialized, c shouldn't have any important data in it
//     all matrices should be the same dimensions
//@post mat_c has the result of multipling mat_a and mat_b
void add_matrix(TYPE* mat_a, int rows, int cols, TYPE* mat_b, TYPE* mat_c) {

  int i, j;
  int ind, row;

  for (i = 0; i < rows; i++) {
    row = cols * i;
    for (j = 0; j < cols; j++) {
      ind = row + j;
      mat_c[ind] = mat_a[ind] + mat_b[ind];
    }
  }

}

//@multiply matrices together
//@pre all matrices are initialized, c shouldn't have any important data in it
//     rows in b == cols in a
//     c is initialized to the same size as b
//@post mat_c has the result of multipling mat_a and mat_b
void multiply_matrix(TYPE* mat_a, int rows_a, int cols_a, TYPE* mat_b, int cols_b, TYPE* mat_c) {

  int i, j, k;
  int c_ind, a_row, c_row;

  for (i = 0; i < rows_a; i++) {
    a_row = cols_a * i;
    c_row = cols_b * i;
    for (j = 0; j < cols_b; j++) {
      c_ind = j + c_row;
      mat_c[c_ind] = 0;
      for (k = 0; k < cols_a; k++) {
        mat_c[c_ind] += mat_a[a_row + k] * mat_b[cols_b * k + j];
      }
    } 
  }

}

// void transpose_matrix() {

// }