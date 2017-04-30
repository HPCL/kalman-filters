/*
 * linear_algebra.c
 * simple code for matrix funcitons
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#include "linear_algebra.h"
#include <math.h>
 
void print_matrix(TYPE* mat_a, int rows_a, int cols_a) {

  int i, j;

  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_a; j++) {
      printf("%.4f ", mat_a[i * cols_a + j]);
    }
    printf("\n\n");
  }
}
 
//@get inverse matrix
//@pre matrix a has been created and filled with data
//     matrices must be square and the same size
//@params mat_a - matrix to invert
//        n -  the matrix side size
//@post mat_c has the inverse matrix of mat_a
//TODO clean up and use a better algo
void invert_matrix(TYPE* mat_a, int n, TYPE* mat_c) {

  TYPE cofactor[n*n];
  TYPE adjoint[n*n];
  TYPE det;

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

//@get matrix determinant recursively
//@pre matrix a has been created and filled with data
//     matrix must be square
//@params mat_a - matrix to invert
//        n -  the matrix side size
//@returms determinant of matrix a
//TODO use better algorithm or make this not recursive
TYPE determinant_matrix_recur(TYPE* mat_a, int n) {

  TYPE det = 0;
  int i, j, k, skip;
  int n_b = n-1;
  int size_b = (n-1) * (n-1);
  int size_a = n * n;
  int sign = 1;
  TYPE mat_b[size_b];

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

//@get matrix determinant iteratively (LU factorization)
//@pre matrix a has been created and filled with data
//     matrix must be square
//@params mat_a - matrix to invert
//        n -  the matrix side size
//@returms determinant of matrix a
//TODO make this dolittle LU factoization
TYPE determinant_matrix(TYPE* mat_a, int n) {

  TYPE det = 0, coeff;

  int i, j, k;
  int size_a = n * n;
  int curr_row, next_row;

  TYPE L[size_a];
  TYPE U[size_a];
  TYPE row[n];
  set_identity(L, n, n);
  copy_mat(mat_a, U, size_a);
  
  for(i = 0; i < n-1; i++) {
    curr_row = i * n;
    for(j = i+1; j < n; j++) {
      next_row = j * n;
      coeff = -1 * (U[next_row+i]/U[curr_row+i]);
      L[next_row+i] = -1 * coeff;
      for (k = 0; k < n; k++) {
        U[next_row + k] += coeff * U[curr_row + k];
      }
    }
  }

  printf("U:\n");
  print_matrix(U,n,n);
  printf("L:\n");
  print_matrix(L,n,n);

  return det;
}


//@get cofactor matrix
//@pre matrix a has been created and filled with data
//     matrices must be square and the smae size
//@params mat_a - matrix to cofactor
//        n -  the matrix side size
//@post mat_c has the cofactor matrix of mat_a
//TODO clean up
void cofactor_matrix(TYPE* mat_a, int n, TYPE* mat_c) {
  TYPE det = 0;
  int i, j, r, c, k, row, rr;
  int n_b = n-1;
  int size_b = (n-1) * (n-1);
  int size_a = n * n;
  int sign = 1;
  TYPE mat_b[size_b];

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

//@add matrices together
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
//     all matrices should be the same dimensions
//@post mat_c has the result of multipling mat_a and scalar
void multiply_matrix_by_scalar(TYPE* mat_a, int rows, int cols, TYPE scalar, TYPE* mat_c) {
  int i, j;
  int ind, row;

  for (i = 0; i < rows; i++) {
    row = cols * i;
    for (j = 0; j < cols; j++) {
      ind = row + j;
      mat_c[ind] = mat_a[ind] * scalar;
    }
  }
}

//@multiply matrices together
//@pre all matrices are initialized, c shouldn't have any important data in it
//     rows in b == cols in a
//     c is initialized to the same size as b
//@post mat_c has the result of multipling mat_a and mat_b
void multiply_matrix(TYPE* mat_a, int rows_a, int cols_a, 
                     TYPE* mat_b, int cols_b, 
                     TYPE* mat_c) {

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
      mat_c[rows_a * j + i] = mat_a[a_row + j];
    }
  }
}

//@set a matrix to zero
//@pre matrix_a has been allocated to rows_a x cols_a
//@post mat_a is all zeros
void set_zero(TYPE* mat_a, int rows_a, int cols_a) {
  int i, j;
  int a_row;

  for (i = 0; i < rows_a; i++) {
    a_row = cols_a * i;
    for (j = 0; j < cols_a; j++) {
      mat_a[a_row + j] = 0;
    }
  }
}

//@set a matrix to the identity
//@pre matrix_a has been allocated to rows_a x cols_a
//@post mat_a has ones in the diagonal and zeros elsewhere
void set_identity(TYPE* mat_a, int rows_a, int cols_a) {
  int i, j;
  int a_row;

  for (i = 0; i < rows_a; i++) {
    a_row = cols_a * i;
    for (j = 0; j < cols_a; j++) {
      mat_a[a_row + j] = (double)(i == j);
    }
  }
}

//@deep copy of a to b
void copy_mat(TYPE* mat_a, TYPE* mat_c, int total_elms) {
  int i;
  for (i = 0; i < total_elms; i++)
    mat_c[i] = mat_a[i];
}