/*
 * test_linear_algebra.c
 * a small program to test the linear algebra code
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#include "matrix_batch.h"
#include "linear_algebra.h"


#include <mkl.h>
#include <mkl_cblas.h>
// #include <mkl_lapacke.h>
// #define IPIV_TYPE long long

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include <vector>
#include <new>


#ifndef NUM_ELMS
#define NUM_ELMS 8
#endif
#ifndef NUM_MATS
#define NUM_MATS 1000
#endif
#ifndef NUM_REPS
#define NUM_REPS 500
#endif

void test_inverse_batch();
void test_multiply();
void test_multiply_large();
void test_multiply_mkl();
void test_multiply_mkl_batch();
void test_multiply_small_batch();
void test_multiply_batch();
void test_add_batch();
void test_transpose_batch();
void test_mult_by_scalar_batch();
void test_zero_and_id_batch();

int main(int argc, char **argv) {

  char temp[16];
  printf("Enter 'c' to continue. Note it may require multiple entries.\n");
  // test_zero_and_id_batch();
  // scanf("%s", temp);
  // test_inverse_batch();
  // scanf("%s", temp);
  // test_cofactor();
  // scanf("%s", temp);
  // test_determinant();
  // scanf("%s", temp);
  // test_determinant_recur();
  // scanf("%s", temp);
  // test_transpose_batch();
  // scanf("%s", temp);
  // test_mult_by_scalar_batch();
  // scanf("%s", temp);
  // test_add_batch();
  // scanf("%s", temp);
  // test_multiply_large();
  test_multiply_mkl_batch();
  // test_multiply_mkl();
  // scanf("%s", temp);
  // test_multiply_small_batch();
  // test_multiply_batch();
  // test_multiply();
  // scanf("%s", temp);
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

  int num_mats = NUM_MATS;
  int n = NUM_ELMS; 
  int m = NUM_ELMS; 

  int i,j,k,l;
  int num_err = 0;

  double start, end;

  printf("starting batch...\n");
  printf("number of matrices = %d\n", NUM_MATS);
  printf("elements per side  = %d\n", NUM_ELMS);
  init_batch(&A, num_mats, n, m);
  init_batch(&B, num_mats, n, m);
  init_batch(&C, num_mats, n, m);

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        A.mats[i][j][l] = 5.;
        B.mats[i][j][l] = 5.;
        C.mats[i][j][l] = 0.;
      }
    }
  }

  printf("multiplying...\n");
  start = omp_get_wtime();
  for (l = 0; l < NUM_REPS; l++) 
    multiply_matrix_batch(&A, &B, &C);
  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  printf("checking...\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        if (C.mats[i][j][l] != 25.*(double)n) {
          printf("ERROR %f\n", C.mats[i][j][l]);
          num_err++;
        } 
      }
    }
  }
  printf("num_err = %d\n", num_err);
  printf("freeing...\n");
  free_batch(&A);
  free_batch(&B);
  free_batch(&C);
  printf("done...\n");
}

struct target
{
  double* A;
  double* B;
  double* C;
  double* D;
};

void test_multiply_large() {

  int i,j,l, num_mats=NUM_MATS;

  const int col = NUM_ELMS, row = NUM_ELMS;
  std::vector<target> stuff(num_mats);

  struct target* temp;
  double start, end;

  printf("starting regular...\n");
  printf("number of matrices = %d\n", NUM_MATS);
  printf("elements per side  = %d\n", NUM_ELMS);
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++){
    it->A = (double*) malloc(row*col*sizeof(double));
    it->B = (double*) malloc(row*col*sizeof(double));
    it->C = (double*) malloc(row*col*sizeof(double));
    it->D = (double*) malloc(row*col*sizeof(double));
  }
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++) {
    for (j = 0; j < row*col; j++) {
      it->A[j] = 5.;
      it->B[j] = 5.;
      it->C[j] = 5.;
      it->D[j] = 5.;
    }
  
  }

  printf("multiplying...\n");
  start = omp_get_wtime();
  
  for (l = 0; l < NUM_REPS; l++) {
    // multiply_matrix(it->A, row, col, it->B, col, it->C);
    for (std::vector<target>::iterator itt = stuff.begin(); itt != stuff.end(); itt++) {
      multiply_matrix(itt->A, row, col, itt->B, col, itt->C);
    }
  }
  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  printf("freeing...\n");
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++) {
      free(it->A);
      free(it->B);
      free(it->C);
  }

  printf("done\n");

}

void test_multiply_mkl() {


  int i,j,l, num_mats=NUM_MATS;

  const int col = NUM_ELMS, row = NUM_ELMS;
  std::vector<target> stuff(num_mats);

  struct target* temp;
  double start, end;

  printf("starting mkl...\n");
  printf("number of matrices = %d\n", NUM_MATS);
  printf("elements per side  = %d\n", NUM_ELMS);
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++){
    it->A = (double*) malloc(row*col*sizeof(double));
    it->B = (double*) malloc(row*col*sizeof(double));
    it->C = (double*) malloc(row*col*sizeof(double));
    it->D = (double*) malloc(row*col*sizeof(double));
  }
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++) {
    for (j = 0; j < row*col; j++) {
      it->A[j] = 5.;
      it->B[j] = 5.;
      it->C[j] = 5.;
      it->D[j] = 5.;
    }
  
  }

  printf("multiplying...\n");
  start = omp_get_wtime();
  
  for (l = 0; l < NUM_REPS; l++) {
    for (std::vector<target>::iterator itt = stuff.begin(); itt != stuff.end(); itt++) {
      cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, row, row, row, 1, itt->A, row, itt->B, row, 1, itt->C, row);
    }
  }
  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  printf("freeing...\n");
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++) {
      free(it->A);
      free(it->B);
      free(it->C);
  }

  printf("done\n");

}

void test_multiply_mkl_batch() {


  int i,j,l, num_mats=NUM_MATS;

  const int col = NUM_ELMS, row = NUM_ELMS;

  double    **A, **B, **C;

  struct target* temp;
  double start, end;

  printf("starting mkl batch...\n");
  printf("number of matrices = %d\n", NUM_MATS);
  printf("elements per side  = %d\n", NUM_ELMS);
  A = (double**) mkl_malloc(NUM_MATS*sizeof(double*),64);
  B = (double**) mkl_malloc(NUM_MATS*sizeof(double*),64);
  C = (double**) mkl_malloc(NUM_MATS*sizeof(double*),64);
  for (i = 0; i < NUM_MATS; i++){
    A[i] = (double*) mkl_malloc(row*col*sizeof(double),64);
    B[i] = (double*) mkl_malloc(row*col*sizeof(double),64);
    C[i] = (double*) mkl_malloc(row*col*sizeof(double),64);
  }
  for (i = 0; i < NUM_MATS; i++){
    for (j = 0; j < row*col; j++) {
      A[i][j] = 5.;
      B[i][j] = 5.;
      C[i][j] = 5.;
    }
  
  }

  printf("multiplying...\n");
  start = omp_get_wtime();

#define NUM_GRPS 1

MKL_INT    m[NUM_GRPS];
MKL_INT    k[NUM_GRPS];
MKL_INT    n[NUM_GRPS];

MKL_INT    lda[NUM_GRPS];
MKL_INT    ldb[NUM_GRPS];
MKL_INT    ldc[NUM_GRPS];

CBLAS_TRANSPOSE    transA[NUM_GRPS];
CBLAS_TRANSPOSE    transB[NUM_GRPS];

double    alpha[NUM_GRPS];
double    beta[NUM_GRPS];

MKL_INT    size_per_grp[NUM_GRPS];

  for (int i = 0; i < NUM_GRPS; i++) {

    m[i] = NUM_ELMS;
    k[i] = NUM_ELMS;
    n[i] = NUM_ELMS;

    lda[i] = NUM_ELMS;
    ldb[i] = NUM_ELMS;
    ldc[i] = NUM_ELMS;

    transA[i] = CblasNoTrans;
    transB[i] = CblasNoTrans;
    
    alpha[i] = 1.0;
    beta[i] = 1.0;

    size_per_grp[i] = NUM_MATS;

  }

  
  for (l = 0; l < NUM_REPS; l++) {
      
cblas_dgemm_batch ( 
        CblasRowMajor, 
        transA, 
        transB, 
        m,
        n,
        k,
        alpha,
        (const double**) A,
        lda,
        (const double**) B,
        ldb,
        beta,
        C,
        ldc,
        NUM_GRPS,
        size_per_grp);

  }
  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  printf("freeing...\n");
  for (i = 0; i < NUM_MATS; i++){
    mkl_free(A[i]);
    mkl_free(B[i]);
    mkl_free(C[i]);
  }
  mkl_free(A);
  mkl_free(B);
  mkl_free(C);

  printf("done\n");

}
