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

void print_matrix(KALMAN_TYPE* mat_a, int rows_a, int cols_a) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

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
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif


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
//TODO fix
KALMAN_TYPE determinant_matrix_recur(KALMAN_TYPE* mat_a, int n) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif


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
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif


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
  
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

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

//add matrices together
//pre all matrices are initialized, c shouldn't have any important data in it
//     all matrices should be the same dimensions
//post mat_c has the result of adding mat_a and mat_b
void add_matrix(KALMAN_TYPE* mat_a, int rows, int cols, KALMAN_TYPE* mat_b, KALMAN_TYPE* mat_c) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif



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

//multiply matrices together
//pre all matrices are initialized, c shouldn't have any important data in it
//     all matrices should be the same dimensions
//post mat_c has the result of multipling mat_a and scalar
void multiply_matrix_by_scalar(KALMAN_TYPE* mat_a, int rows, int cols, KALMAN_TYPE scalar, KALMAN_TYPE* mat_c) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

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

//multiply matrices together
//pre all matrices are initialized, c shouldn't have any important data in it
//     rows in b == cols in a
//     c is initialized to the same size as b
//post mat_c has the result of multipling mat_a and mat_b
void multiply_matrix(KALMAN_TYPE* mat_a, int rows_a, int cols_a, 
                     KALMAN_TYPE* mat_b, int cols_b, 
                     KALMAN_TYPE* mat_c) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif


  int i, j, k;
  int c_ind, a_row, c_row;

  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_b; j++) {
      mat_c[j + cols_b * i] = 0;
      for (k = 0; k < cols_a; k++) {
        mat_c[j + cols_b * i] += mat_a[cols_a * i + k] * mat_b[cols_b * k + j];
      }
    } 
  }

}

//transpose a matrix
//pre all matrices are initialized, c shouldn't have any important data in it
//     rows in c == cols in a
//post mat_c has the transpose of mat_a
void transpose_matrix(KALMAN_TYPE* mat_a, int rows_a, int cols_a, KALMAN_TYPE* mat_c) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  int i, j;
  int a_row;

  for (i = 0; i < rows_a; i++) {
    a_row = cols_a * i;
    for (j = 0; j < cols_a; j++) {
      mat_c[rows_a * j + i] = mat_a[a_row + j];
    }
  }
}

//compute LUP factorization of the matrix
//pre all matrices are initialized, L, U, P shouldn't have anything in them
//    all are nxn
//output L is lower, U is upper, P is the P matrix which i don't understand
//returns number of row swaps or -1 if failure
//note this code borrows heavily from here: https://en.wikipedia.org/wiki/LU_decomposition
//TODO make more memory efficient?
int compute_LUP(KALMAN_TYPE* mat_a, KALMAN_TYPE* L, KALMAN_TYPE* U, KALMAN_TYPE* P, int n) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  int i, j, k, ind_max, curr_row, next_row;
  int cnt_pivots = 0;
  int size_a = n*n;
  KALMAN_TYPE tolerance = 5E-300;
  KALMAN_TYPE max_a, abs_a, coeff;
  KALMAN_TYPE temp_row[n];

  set_identity(P, n, n);
  set_identity(L, n, n);
  copy_mat(mat_a, U, size_a);

  for(i = 0; i < n; i++) {
    curr_row = i * n;
    max_a = get_abs(U[curr_row + i]);
    ind_max = i;

    for (j = i+1; j < n; j++) {
      abs_a = get_abs(U[j * n + i]);
      if (abs_a > max_a) {
        max_a = abs_a;
        ind_max = j;
      }
    }

    if (max_a < tolerance) return -1;

    if (ind_max != i) {
      cnt_pivots++;
      ind_max *= n;

      copy_mat(&P[curr_row], temp_row, n);
      copy_mat(&P[ind_max], &P[curr_row], n);
      copy_mat(temp_row, &P[ind_max], n);

      copy_mat(&U[curr_row], temp_row, n);
      copy_mat(&U[ind_max], &U[curr_row], n);
      copy_mat(temp_row, &U[ind_max], n);
    }

    for(j = i+1; j < n; j++) {
      next_row = j * n;
      coeff = (U[next_row+i]/U[curr_row+i]);
      L[next_row+i] = coeff;
      for (k = i; k < n; k++) {
        U[next_row + k] -= coeff * U[curr_row + k];
      }
    }

  } //end main for

  return cnt_pivots;
}

int compute_LUP_inline(KALMAN_TYPE* mat_a, KALMAN_TYPE* L, KALMAN_TYPE* U, KALMAN_TYPE* P, int n) {
  
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  int i, j, k, ind_max, curr_row, next_row, row;
  int cnt_pivots = 0;
  int size_a = n*n;
  KALMAN_TYPE max_a, abs_a, coeff;
  KALMAN_TYPE temp_row[n];

  // set_identity(P, n, n);
  for (i = 0; i < n; i++) {
    row = n * i;
    for (j = 0; j < n; j++) {
      P[row + j] = (double)(i == j);
    }
  }
  // set_identity(L, n, n);
  for (i = 0; i < n; i++) {
    row = n * i;
    for (j = 0; j < n; j++) {
      L[row + j] = (double)(i == j);
    }
  }

  // copy_mat(mat_a, U, size_a);
  for (i = 0; i < size_a; i++)
    U[i] = mat_a[i];

  for(i = 0; i < n; i++) {
    curr_row = i * n;
    // max_a = get_abs(U[curr_row + i]);
    max_a = (((U[curr_row + i] < 0) * -2) + 1) * U[curr_row + i];
    ind_max = i;

    for (j = i+1; j < n; j++) {
      // abs_a = get_abs(U[j * n + i]);
      abs_a = (((U[j * n + i] < 0) * -2) + 1) * U[j * n + i];
      if (abs_a > max_a) {
        max_a = abs_a;
        ind_max = j;
      }
    }

    if (ind_max != i) {
      cnt_pivots++;
      ind_max *= n;

      // copy_mat(&P[curr_row], temp_row, n);
      for (k = 0; k < n; k++)
        temp_row[k] = (&P[curr_row])[k];
      // copy_mat(&P[ind_max], &P[curr_row], n);
      for (k = 0; k < n; k++)
        (&P[curr_row])[k] = (&P[ind_max])[k];
      // copy_mat(temp_row, &P[ind_max], n);
      for (k = 0; k < n; k++)
        (&P[ind_max])[k] = temp_row[k];

      // copy_mat(&U[curr_row], temp_row, n);
      for (k = 0; k < n; k++)
        temp_row[k] = (&U[curr_row])[k];
      // copy_mat(&U[ind_max], &U[curr_row], n);
      for (k = 0; k < n; k++)
        (&U[curr_row])[k] = (&U[ind_max])[k];
      // copy_mat(temp_row, &U[ind_max], n);
      for (k = 0; k < n; k++)
        (&U[ind_max])[k] = temp_row[k];

    }

    for(j = i+1; j < n; j++) {
      next_row = j * n;
      coeff = (U[next_row+i]/U[curr_row+i]);
      L[next_row+i] = coeff;
      for (k = i; k < n; k++) {
        U[next_row + k] -= coeff * U[curr_row + k];
      }
    }

  } //end main for

  return cnt_pivots;
}


//set a matrix to zero
//pre matrix_a has been allocated to rows_a x cols_a
//post mat_a is all zeros
void set_zero(KALMAN_TYPE* mat_a, int rows_a, int cols_a) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

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
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

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
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  int i;
  for (i = 0; i < total_elms; i++)
    mat_c[i] = mat_a[i];
}

//returns abs(a)
//TODO make a macro?
KALMAN_TYPE get_abs(KALMAN_TYPE a) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  return (((a < 0) * -2) + 1) * a;
  
  // return (a < 0) ? -a : a;

}