/*
 * linear_algebra.c
 * simple code for matrix funcitons
 * many of the functions in this "library" are in the various subdirs for tuning purposes
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#include "../linear_algebra.h"
#include <math.h>


void print_matrix(KALMAN_TYPE* mat_a, int rows_a, int cols_a) {

  int i, j;

  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_a; j++) {
      printf("%.4f ", mat_a[i * cols_a + j]);
    }
    printf("\n\n");
  }
}


//get inverse matrix
//pre matrix a has been created and filled with data
//     matrices must be square and the same size
//params mat_a - matrix to invert
//        n -  the matrix side size
//post mat_c has the inverse matrix of mat_a
//TODO clean up and use a better algo
void invert_matrix(KALMAN_TYPE* mat_a, int n, KALMAN_TYPE* mat_c) {

  KALMAN_TYPE cofactor[n*n];
  KALMAN_TYPE adjoint[n*n];
  KALMAN_TYPE det;

  if (n == 1) {
    mat_c[0] = 1 / mat_a[0];

  } else {
    det = determinant_matrix(mat_a, n);
    det = 1 / det;
    // if( isnan(det) )
    // {
    //   printf("\n\nERROR NAN\n");
    //   print_matrix(mat_a, n, n);
    //   printf("\n\n");
    // }
    cofactor_matrix(mat_a, n, cofactor);
    transpose_matrix(cofactor, n, n, adjoint);
    multiply_matrix_by_scalar(adjoint, n, n, det, mat_c);
  }
}

//get matrix determinant recursively
//pre matrix a has been created and filled with data
//     matrix must be square
//params mat_a - matrix to invert
//        n -  the matrix side size
//returms determinant of matrix a
KALMAN_TYPE determinant_matrix_recur(KALMAN_TYPE* mat_a, int n) {

  KALMAN_TYPE det = 0;
  int i, j, k, skip;
  int n_b = n-1;
  int size_b = (n-1) * (n-1);
  int size_a = n * n;
  int sign = 1;
  KALMAN_TYPE mat_b[size_b];

  if(n == 2) {
    det = (mat_a[0] * mat_a[3]) - (mat_a[1] * mat_a[2]);

  } else {

    for (i = 0; i < n; i++) {

      if(mat_a[i] != 0){
        k = 0;
        skip = i + n;

        for(j = n; j < size_a; j++) {
          if(j != skip)
            mat_b[k++] = mat_a[j];
          else
            skip += n;
        }

        det += sign * mat_a[i] * determinant_matrix(mat_b, n_b);
      } // if mat_a[i] != 0
      
      sign = sign * -1;
    } // for loop

  } //else 

  return det;
}

//get matrix determinant iteratively (LU factorization)
//pre matrix a has been created and filled with data
//     matrix must be square
//params mat_a - matrix to invert
//        n -  the matrix side size
//returns determinant of matrix a
KALMAN_TYPE determinant_matrix(KALMAN_TYPE* mat_a, int n) {

  KALMAN_TYPE det = 1.0;

  int i, num_pivots;
  int size_a = n * n;

  KALMAN_TYPE L[size_a];
  KALMAN_TYPE U[size_a];
  KALMAN_TYPE P[size_a];
  
  num_pivots = compute_LUP(mat_a, L, U, P, n);

  if(num_pivots == -1) return 0;

  det = ((num_pivots%2) == 1) ? -1.0 : 1.0;

  for (i = 0; i < n; i++) {
    det *= U[i*n+i];
  }
  
  return det;
}


//get cofactor matrix
//pre matrix a has been created and filled with data
//     matrices must be square and the smae size
//params mat_a - matrix to cofactor
//        n -  the matrix side size
//post mat_c has the cofactor matrix of mat_a
//TODO clean up
void cofactor_matrix(KALMAN_TYPE* mat_a, int n, KALMAN_TYPE* mat_c) {
  KALMAN_TYPE det = 0;
  int i, j, r, c, k, row, rr;
  int n_b = n-1;
  int size_b = (n-1) * (n-1);
  int size_a = n * n;
  int sign = 1;
  KALMAN_TYPE mat_b[size_b];

  for (i = 0; i < n; i++) {
    row = n * i;
    for (j = 0; j < n; j++) {

        k = 0;
        for (r = 0; r < n; r++) {
          if(r != i){
            rr = n * r;
            for (c = 0; c < n; c++) {
              if(c != j) mat_b[k++] = mat_a[rr + c];
            }
          }
        }

      det = determinant_matrix(mat_b, n_b);
      mat_c[row + j] = sign * det;
      sign = sign * -1;
    }
    sign = sign * -1;
  }

}


//set a matrix to zero
//pre matrix_a has been allocated to rows_a x cols_a
//post mat_a is all zeros
void set_zero(KALMAN_TYPE* mat_a, int rows_a, int cols_a) {
  int i, j;
  int a_row;

  for (i = 0; i < rows_a; i++) {
    a_row = cols_a * i;
    for (j = 0; j < cols_a; j++) {
      mat_a[a_row + j] = 0;
    }
  }
}

//set a matrix to the identity
//pre matrix_a has been allocated to rows_a x cols_a
//post mat_a has ones in the diagonal and zeros elsewhere
void set_identity(KALMAN_TYPE* mat_a, int rows_a, int cols_a) {
  int i, j;
  int a_row;

  for (i = 0; i < rows_a; i++) {
    a_row = cols_a * i;
    for (j = 0; j < cols_a; j++) {
      mat_a[a_row + j] = (double)(i == j);
    }
  }
}


//deep copy of a to b
void copy_mat(KALMAN_TYPE* mat_a, KALMAN_TYPE* mat_c, int total_elms) {
  int i;
  for (i = 0; i < total_elms; i++)
    mat_c[i] = mat_a[i];
}

//returns abs(a)
//TODO make a macro?
KALMAN_TYPE get_abs(KALMAN_TYPE a) {
  return (((a < 0) * -2) + 1) * a;
  
  // return (a < 0) ? -a : a;

}