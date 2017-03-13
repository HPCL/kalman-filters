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
 
void invert_matrix(TYPE* mat_a, int n, TYPE* mat_c) {

}

//@get matrix determinant
//@pre matrix a has been created and filled with data
//     matrix must be square
//@params mat_a - matrix to invert
//        n -  the matrix side size
//@post mat_c has the result of multipling mat_a and mat_b
//@note recursive
//TODO use better algorithm or make this not recursive
TYPE determinant_matrix(TYPE* mat_a, int n) {
  TYPE det = 0;
  int i, row, col, row_b, col_b;
  int n_b = n-1, size_b = (n-1) * (n-1);
  int sign = 1;
  TYPE mat_b[size_b];

  if(n == 2) {
    det = (mat_a[0] * mat_a[3]) - (mat_a[1] * mat_a[2]);

  } else {

    for (i = 0; i < n; i++) {

      if(mat_a[i] != 0){
        for(row = 1; row < size_b; row++) {
          row_b = row * n_b;
          col_b = 0;
          for (col = 0; col < size_b; col++) {
            if(col != i)
              mat_b[row_b + col_b++] = mat_a[row_b + col];
          }
        }

        det += sign * mat_a[i] * determinant_matrix(mat_b, n_b);
      } // if mat_a[i] != 0
      
      sign = sign * -1;
    } // for loop

  } //else 

  return det;
}

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

//@transpose a matrix
//@pre all matrices are initialized, c shouldn't have any important data in it
//     rows in c == cols in a
//@post mat_c has the transpose of mat_a
void transpose_matrix(TYPE* mat_a, int rows_a, int cols_a, TYPE* mat_c) {
  int i, j;
  int a_row;

  for (i = 0; i < rows_a; i++) {
    a_row = cols_a * i;
    for (j = 0; j < cols_a; j++) {
      mat_c[rows_a * j +i] = mat_a[a_row + j];
    }
  }

}