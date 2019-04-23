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


void _untuned_multiply_matrix_batch(KALMAN_TYPE*** A, int rows_a, int cols_a,
                            KALMAN_TYPE*** B, int rows_b, int cols_b,
                            KALMAN_TYPE*** C,
                            int num_mats){
  int i,j,k,l;
  #pragma omp parallel for private(i,j, k, l)
  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_b; j++) {
      for (l = 0; l < num_mats; l++) C[i][j][l] = 0.;
      for (k = 0; k < cols_a; k++) {
        #pragma ivdep
        for (l = 0; l < num_mats; l++) {
          C[i][j][l] = A[i][k][l] * B[k][j][l] + C[i][j][l];
        }
      }
    } 
  }

} 


void untuned_multiply_matrix_batch(struct batch* A, struct batch* B, struct batch* C) {

  int i,j,k,l;

  const int rows_a   = A->rows;
  const int rows_b   = B->rows;
  const int cols_a   = A->cols;
  const int cols_b   = B->cols;
  const int num_mats = A->num_mats;

  // for (i = 0; i < rows_a; i++) 
  //   for (j = 0; j < cols_b; j++) 
  //     #pragma ivdep
  //     for (l = 0; l < num_mats; l++) 
  //       C->mats[i][j][l] = 0;

  _untuned_multiply_matrix_batch(A->mats, rows_a, cols_a, B->mats, rows_b, cols_b, C->mats, num_mats);


}


void multiply_matrix_batch(struct batch* A, struct batch* B, struct batch* C) {

  int i,j,k,l;

  const int rows_a   = A->rows;
  const int rows_b   = B->rows;
  const int cols_a   = A->cols;
  const int cols_b   = B->cols;
  const int num_mats = A->num_mats;


#ifdef TUNED

  // for (i = 0; i < rows_a; i++) 
  //   for (j = 0; j < cols_b; j++) 
  //     #pragma ivdep
  //     for (l = 0; l < num_mats; l++) 
  //       C->mats[i][j][l] = 0.;

  // struct batch BT;
  // init_batch(&BT, num_mats, rows_b, cols_b);
  // transpose_matrix_batch(B, &BT);

  // for (i = 0; i < rows_a; i++) {
  //   for (j = 0; j < cols_b; j++) {
  //     for (k = 0; k < cols_a; k++) {
  //       #pragma vector always
  //       for (l = 0; l < num_mats; l++) {
  //         C->mats[i][j][l] = A->mats[i][k][l] * B->mats[k][j][l] + C->mats[i][j][l];
  //       }
  //     }
  //   } 
  // }

  // free_batch(&BT);

  _multiply_matrix_batch(A->mats, rows_a, cols_a, B->mats, rows_b, cols_b, C->mats, num_mats);

#else

  _untuned_multiply_matrix_batch(A->mats, rows_a, cols_a, B->mats, rows_b, cols_b, C->mats, num_mats);

#endif

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

void subtract_matrix_batch(struct batch* A, struct batch* B, struct batch* C) {
  
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
        C->mats[i][j][l] = A->mats[i][j][l] - B->mats[i][j][l];
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




