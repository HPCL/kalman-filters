/*
 * test_linear_algebra.c
 * a small program to test the linear algebra code
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate or introductions to potential employers.

*/

#include "matrix_batch.h"
#include "linear_algebra.h"

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void test_inverse_batch();
void test_multiply();
void test_multiply_large();
void test_multiply_small_batch();
void test_multiply_batch();
void test_add_batch();
void test_transpose_batch();
void test_mult_by_scalar_batch();
void test_zero_and_id_batch();

int main(int argc, char **argv) {

  char temp[16];
  printf("Enter 'c' to continue. Note it may require multiple entries.\n");
  test_zero_and_id_batch();
  scanf("%s", temp);
  test_inverse_batch();
  // scanf("%s", temp);
  // test_cofactor();
  // scanf("%s", temp);
  // test_determinant();
  // scanf("%s", temp);
  // test_determinant_recur();
  scanf("%s", temp);
  test_transpose_batch();
  scanf("%s", temp);
  test_mult_by_scalar_batch();
  scanf("%s", temp);
  test_add_batch();
  scanf("%s", temp);
  // test_multiply_large();
  // scanf("%s", temp);
  test_multiply_small_batch();
  // test_multiply_batch();
  // test_multiply();
  scanf("%s", temp);
  // test_compute_LUP();
  // scanf("%s", temp);
  // test_compute_LUP_inline();
  // scanf("%s", temp);
  printf("Bye now!\n");

  return 0;
}

void test_add_batch() {
  struct batch A;
  struct batch B;
  struct batch C;

  int num_mats = 3;
  int n = 5; 
  int m = 2; 

  int i,j,k,l;

  printf("\n\ntesting add...\n");

  init_batch(&A, num_mats, n, m);
  init_batch(&B, num_mats, n, m);
  init_batch(&C, num_mats, n, m);

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        A.mats[i][j][l] = 5;
        B.mats[i][j][l] = 5;
        C.mats[i][j][l] = 5;
      }
    }
  }

  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  add_matrix_batch(&A, &B, &C);

  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  free_batch(&A);
  free_batch(&B);
  free_batch(&C);
}


void test_transpose_batch() {
  struct batch A;
  struct batch C;

  int num_mats = 3;
  int n = 4; 
  int m = 2; 

  int i,j,k,l;

  printf("\n\ntesting traspose...\n");

  init_batch(&A, num_mats, n, m);
  init_batch(&C, num_mats, m, n);

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        A.mats[i][j][l] = i+j+l;
        C.mats[j][i][l] = i+j+l;
      }
    }
  }

  for (l = 0; l < num_mats; l++) {
    print_batch(&A, l);
  }

  transpose_matrix_batch(&A, &C);

  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  free_batch(&A);
  free_batch(&C);

}


void test_mult_by_scalar_batch() {
  struct batch A;
  struct batch C;

  int num_mats = 3;
  int n = 2; 
  int m = 2; 

  int i,j,k,l;

  KALMAN_TYPE s[num_mats];
  for (l = 0; l < num_mats; l++) s[l] = l;

  printf("\n\ntesting mult by scalar...\n");

  init_batch(&A, num_mats, n, m);
  init_batch(&C, num_mats, n, m);

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        A.mats[i][j][l] = i+j+l;
        C.mats[i][j][l] = i+j+l;
      }
    }
  }

  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  multiply_matrix_by_scalar_batch(&A, &C, s);

  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  free_batch(&A);
  free_batch(&C);

}

void test_zero_and_id_batch() {
  struct batch A;
  struct batch B;
  struct batch C;

  int num_mats = 3;
  int n = 3; 
  int m = 3; 

  int i,j,k,l;

  printf("\n\ntesting zero/add...\n");

  init_batch(&A, num_mats, n, m);
  init_batch(&C, num_mats, n, m);

  set_zero_batch(&A);
  set_identity_batch(&C);

  for (l = 0; l < num_mats; l++) {
    print_batch(&A, l);
  }
  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  free_batch(&A);
  free_batch(&C);
}


void test_inverse_batch() {
  struct batch A;
  struct batch C;

  int num_mats = 3;
  int n = 2; 
  int m = 2; 

  int i,j,k,l;

  printf("\n\ntesting invert...\n");

  init_batch(&A, num_mats, n, m);
  init_batch(&C, num_mats, n, m);

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        A.mats[i][j][l] = i*j+l;
        C.mats[i][j][l] = i*j+l;
      }
    }
  }

  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  invert_matrix_2x2_batch(&A, &C);

  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  free_batch(&A);
  free_batch(&C);
}


void test_multiply_small_batch() {
  struct batch A;
  struct batch B;
  struct batch C;

  int num_mats = 3;
  int n = 5; 
  int m = 2; 

  int i,j,k,l;

  printf("\n\ntesting multiply...\n");

  init_batch(&A, num_mats, n, m);
  init_batch(&B, num_mats, n, m);
  init_batch(&C, num_mats, n, m);

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        A.mats[i][j][l] = 5;
        B.mats[i][j][l] = 5;
        C.mats[i][j][l] = 5;
      }
    }
  }

  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  multiply_matrix_batch(&A, &B, &C);

  for (l = 0; l < num_mats; l++) {
    print_batch(&C, l);
  }

  free_batch(&A);
  free_batch(&B);
  free_batch(&C);

}


void test_multiply_batch() {
  struct batch A;
  struct batch B;
  struct batch C;

  int num_mats = 1000000;
  int n = 6; 
  int m = 6; 

  int i,j,k,l;

  double start, end;

  printf("starting batch...\n");
  init_batch(&A, num_mats, n, m);
  init_batch(&B, num_mats, n, m);
  init_batch(&C, num_mats, n, m);

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        A.mats[i][j][l] = 5.;
        B.mats[i][j][l] = 5.;
        C.mats[i][j][l] = 5.;
      }
    }
  }

  printf("multiplying...\n");
  start = omp_get_wtime();
  multiply_matrix_batch(&A, &B, &C);
  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  printf("checking...\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        if (C.mats[i][j][l] != 150.) printf("ERROR\n");
      }
    }
  }
  printf("freeing...\n");
  free_batch(&A);
  free_batch(&B);
  free_batch(&C);
  printf("done...\n");
}

void test_multiply_large() {

  int i,j, num_mats=1000000;

  int col = 6, row = 6;
  double **A, **B, **C;
  double start, end;

  printf("starting regular...\n");
  A = (double**)malloc(num_mats*sizeof(double*));
  B = (double**)malloc(num_mats*sizeof(double*));
  C = (double**)malloc(num_mats*sizeof(double*));
  for(i = 0; i < num_mats; i++){
    A[i] = (double*)malloc(col*row*sizeof(double));
    B[i] = (double*)malloc(col*row*sizeof(double));
    C[i] = (double*)malloc(col*row*sizeof(double));
  }

  for (i = 0; i < num_mats; i++) {
    for (j = 0; j < row*col; j++) {
      A[i][j] = 5.;
      B[i][j] = 5.;
      C[i][j] = 5.;
    }
  }

  printf("multiplying...\n");
  start = omp_get_wtime();
  for(i = 0; i < num_mats; i++){
    multiply_matrix(A[i], row, col, B[i], col, C[i]);
  }
  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  printf("freeing...\n");
  for(i = 0; i < num_mats; i++){
    free(A[i]);
    free(B[i]);
    free(C[i]);
  }
  free(A);
  free(B);
  free(C);

  printf("done\n");

}
