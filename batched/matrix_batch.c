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

  A->mats = (KALMAN_TYPE***)malloc(rows*sizeof(KALMAN_TYPE**));
  for (i = 0; i <  A->rows; i++) {
    A->mats[i] = (KALMAN_TYPE**)malloc(cols*sizeof(KALMAN_TYPE*));
    for (int j = 0; j <  A->cols; j++) {
      A->mats[i][j] = (KALMAN_TYPE*)malloc(num_mats*sizeof(KALMAN_TYPE));
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


void invert_matrix_2x2_batch(struct batch* A, struct batch* C) {

  int i,j,l;

  const int rows     = A->rows;
  const int cols     = A->cols;
  const int num_mats = A->num_mats;

  KALMAN_TYPE det[num_mats];

  for (l = 0; l < num_mats; l++) {
  
    det[l] = 1. / (A->mats[0][0][l]*A->mats[1][1][l] - A->mats[0][1][l]*A->mats[1][0][l]);

    C->mats[0][0][l] = A->mats[1][1][l] * det[l];
    C->mats[0][1][l] = A->mats[0][1][l] * det[l] * -1.;
    C->mats[1][0][l] = A->mats[1][0][l] * det[l] * -1.;
    C->mats[1][1][l] = A->mats[0][0][l] * det[l];

  }
}

#ifndef TUNED

inline void _multiply_matrix_batch(KALMAN_TYPE*** A, int rows_a, int cols_a,
                            KALMAN_TYPE*** B, int rows_b, int cols_b,
                            KALMAN_TYPE*** C,
                            int num_mats) {

  int i,j,k,l;

  // for (i = 0; i <= rows_a-1; i++) {
  //   for (j = 0; j <= cols_b-1; j++) {
  //     for (l = 0; l <= num_mats-1; l++) {
  //       C[i][j][l] = 0;
  //     }
  //   }
  // } 

  // for (i = 0; i <= rows_a-1; i++) {
  //   for (j = 0; j <= cols_b-1; j++) {
  //     for (k = 0; k <= cols_a-1; k++) {
  //       for (l = 0; l <= num_mats-1; l++) {
  //         C[i][j][l] += A[i][k][l] * B[k][j][l];
  //       }
  //     }
  //   } 
  // }

  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_b; j++) {
      for (l = 0; l < num_mats; l++) {
        C[i][j][l] = 0;
      }
      for (k = 0; k < cols_a; k++) {
        #pragma ivdep
        for (l = 0; l < num_mats; l++) {
          C[i][j][l] += A[i][k][l] * B[k][j][l];
        }
      }
    } 
  }
} 

#endif

void multiply_matrix_batch(struct batch* A, struct batch* B, struct batch* C) {

  int i,j,k,l;

  const int rows_a   = A->rows;
  const int rows_b   = B->rows;
  const int cols_a   = A->cols;
  const int cols_b   = B->cols;
  const int num_mats = A->num_mats;

  _multiply_matrix_batch(A->mats, rows_a, cols_a, B->mats, rows_b, cols_b, C->mats, num_mats);

}

void multiply_matrix_by_scalar_batch(struct batch* A, struct batch* C, KALMAN_TYPE s[]) {
  
  const int rows     = A->rows;
  const int cols     = A->cols;
  const int num_mats = A->num_mats;

  C->rows = rows;
  C->cols = cols;
  C->num_mats = num_mats;

  int i, j, l;
  int a_row;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      for (l = 0; l < num_mats; l++) {
        C->mats[i][j][l] = A->mats[i][j][l] * s[l];
      }
    }
  }

}

void add_matrix_batch(struct batch* A, struct batch* B, struct batch* C) {
  
  const int rows     = A->rows;
  const int cols     = A->cols;
  const int num_mats = A->num_mats;

  C->rows = rows;
  C->cols = cols;
  C->num_mats = num_mats;

  int i, j, l;
  int a_row;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      for (l = 0; l < num_mats; l++) {
        C->mats[i][j][l] = A->mats[i][j][l] + B->mats[i][j][l];
      }
    }
  }

}

void transpose_matrix_batch(struct batch* A, struct batch* C) {
 
  const int rows     = A->rows;
  const int cols     = A->cols;
  const int num_mats = A->num_mats;

  C->rows = cols;
  C->cols = rows;
  C->num_mats = num_mats;

  int i, j, l;
  int a_row;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      for (l = 0; l < num_mats; l++) {
        C->mats[j][i][l] = A->mats[i][j][l];
      }
    }
  }

}

void print_batch(struct batch* A, int mat_id) {

  int i, j;

  for (i = 0; i < A->rows; i++) {
    for (j = 0; j < A->cols; j++) {
      printf("%.4f ", A->mats[i][j][mat_id]);
    }
    printf("\n\n");
  }

}


void copy_mat_batch(struct batch* A, struct batch* C) {

  int i,j,l;

  const int rows     = A->rows;
  const int cols     = A->cols;
  const int num_mats = A->num_mats;

  C->rows = rows;
  C->cols = cols;
  C->num_mats = num_mats;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      for (l = 0; l < num_mats; l++) {
        C->mats[i][j][l] = A->mats[i][j][l];
      }
    }
  }

}

void set_identity_batch(struct batch* A) {
 
  int i,j,l;

  const int rows     = A->rows;
  const int cols     = A->cols;
  const int num_mats = A->num_mats;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      for (l = 0; l < num_mats; l++) {
        if(i==j){
          A->mats[i][j][l] = 1.;
        } else {
          A->mats[i][j][l] = 0.;
        }
      }
    }
  }

}

void set_zero_batch(struct batch* A) {
 
  int i,j,l;

  const int rows     = A->rows;
  const int cols     = A->cols;
  const int num_mats = A->num_mats;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      for (l = 0; l < num_mats; l++) {
        A->mats[i][j][l] = 0.;
      }
    }
  }

}



/* TODO make this work
void invert_matrix_batch(struct batch* A, struct batch* C) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  int i,j,l;

  const int rows     = A->rows;
  const int cols     = A->cols;
  const int num_mats = A->num_mats;

  struct batch* cofactor;
  struct batch* adjoint;
  init_batch(cofactor, num_mats, rows, cols);
  init_batch(adjoint, num_mats, rows, cols);
  KALMAN_TYPE det[num_mats];

  if ((rows == 1) && (cols == 1)) {

    for (l = 0; l < num_mats; l++) {
      C->mats[0][0][l] = 1 / A->mats[0][0][l];
    }

  } else {

    det = determinant_matrix_batch(mat_a, n);
    for (l = 0; l < num_mats; l++) det[l] = 1 / det[l];
    cofactor_matrix_batch(A, rows, cofactor);
    transpose_matrix_batch(cofactor, adjoint);
    multiply_matrix_by_scalar_batch(adjoint, C, det);

  }

  free_batch(cofactor);
  free_batch(adjoint);

}

void determinant_matrix_batch(KALMAN_TYPE* mat_a, KALMAN_TYPE det[]) {
  
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  int i, j, k, l;

  A->num_mats = num_mats;
  A->rows = rows;
  A->cols = cols;

  struct batch* L;
  struct batch* U;
  struct batch* P;
  init_batch(L, num_mats, rows, cols);
  init_batch(U, num_mats, rows, cols);
  init_batch(P, num_mats, rows, cols);

  KALMAN_TYPE num_pivots[num_mats];

  for (l = 0; l < num_mats; l++) det[l] = 1.;
  
  compute_LUP(A, L, U, P, num_pivots);

  for (l = 0; l < num_mats; l++){

    if(num_pivots == -1) {
      det[l] = 0;
    } else{
      det[l] = ((num_pivots%2) == 1) ? -1.0 : 1.0;
      for (i = 0; i < n; i++) {
        det[l] *= U[i*n+i];
      }
    }  

  }

  free_batch(L);
  free_batch(U);
  free_batch(P);

}

void cofactor_matrix_batch(struct batch* A, struct batch* C) {
  
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif


  A->num_mats = num_mats;
  A->rows = rows;
  A->cols = cols;

  struct batch* B;
  init_batch(B, num_mats, rows-1, cols-1);

  int i, j, r, c, k, l, rr, cc;
  int sign[num_mats];
  for (l = 0; l < num_mats; l++) sign[l] = 1;
  KALMAN_TYPE det[num_mats];

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {

        rr = 0;
        for (r = 0; r < n; r++) {
          if(r != i){

            cc = 0;
            for (c = 0; c < n; c++) {
              if(c != j) 
                for (l = 0; l < num_mats; l++) B.mats[rr][cc++][l] = A[r][c][l];
            }
            rr++;

          }
        }

      determinant_matrix_batch(B, det);
      for (l = 0; l < num_mats; l++) C[i][j][l] = sign[l] * det[l];
      for (l = 0; l < num_mats; l++) sign[l] = sign[l] * -1;
    }
    for (l = 0; l < num_mats; l++) sign[l] = sign[l] * -1;
  }


  free_batch(B);

}

void compute_LUP_batch(struct batch* A, 
                      struct batch* L, 
                      struct batch* U, 
                      struct batch* P, 
                      int cnt_pivots[]) {
 
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  int i, j, k, ind_max, curr_row, next_row;
  int cnt_pivots = 0;
  int size_a = n*n;
  KALMAN_TYPE tolerance = 5E-300;
  KALMAN_TYPE max_a, abs_a, coeff;
  KALMAN_TYPE temp_row[n];

  set_identity_batch(P);
  set_identity_batch(L);
  copy_mat_batch(A, U);

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

    // TODO not in the batch
    if (ind_max != i) {
      cnt_pivots++;
      ind_max *= n;

      // TODO row swaps
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

}
*/
