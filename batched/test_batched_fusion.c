/*
 * test_batched_fusion.c
 * a small program to test the linear algebra code with fused and batched matrix algebra
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#include "matrix_batch.h"
#include "linear_algebra.h"


// #include <cblas.h>

#include <mkl.h>
#include <mkl_cblas.h>
#include <mkl_lapacke.h>
#define IPIV_TYPE long long

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
#ifndef BATCH_SIZE
#define BATCH_SIZE 128
#endif

struct target
{
  double* K;
  double* H;
  double* F;
  double* x_old;
  double* x_new;
  double* m;
};


void test_equations_normal();
void test_equations_batch();
void test_equations_mkl();
void test_equations_mkl_batch();

int main(int argc, char **argv) {

  test_equations_normal();

  return 0;
}



void test_equations_normal() {

#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  int i,j,l, num_mats=NUM_MATS;

  const int col = NUM_ELMS, row = NUM_ELMS;
  std::vector<target> stuff(num_mats);

  struct target* temp;
  double start, end;

  printf("starting regular...\n");
  printf("number of matrices = %d\n", NUM_MATS);
  printf("elements per side  = %d\n", NUM_ELMS);
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++){
    it->K      = (double*) _mm_malloc(row*col*sizeof(double), 64);
    it->H      = (double*) _mm_malloc(row*col*sizeof(double), 64);
    it->F      = (double*) _mm_malloc(row*col*sizeof(double), 64);

    it->x_old  = (double*) _mm_malloc(col*sizeof(double), 64);
    it->x_new  = (double*) _mm_malloc(col*sizeof(double), 64);
    it->m      = (double*) _mm_malloc(col*sizeof(double), 64);
  }

  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++) {

    for (j = 0; j < row*col; j++) {
      it->K[j] = 5.;
      it->H[j] = 5.;
      it->F[j] = 5.;
    }

    for (j = 0; j < col; j++) {
      it->x_old[j] = 5.;
      it->x_new[j] = 5.;
      it->m[j]     = 5.;
    }
  
  }

  printf("multiplying...\n");
  start = omp_get_wtime();
  

  double * x_mid      = (double*) _mm_malloc(col*sizeof(double), 64);
  double * temp_vec_1 = (double*) _mm_malloc(col*sizeof(double), 64);
  double * temp_vec_2 = (double*) _mm_malloc(col*sizeof(double), 64);

  for (l = 0; l < NUM_REPS; l++) {

    for (std::vector<target>::iterator itt = stuff.begin(); itt != stuff.end(); itt++) {
      multiply_matrix(itt->F, row, col, itt->x_old, 1, x_mid);
    }

  }
  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  int vec_row = 1, num_err = 0;  
  printf("checking...\n");
  for (i = 0; i < col; i++) {
    for (j = 0; j < vec_row; j++) {
      // for (l = 0; l < num_mats; l++) {
        if (x_mid[j + vec_row * i] != 25.*(double)col) {
          printf("ERROR %f\n", x_mid[j + vec_row * i]);
          num_err++;
        } 
      // }
    }
  }

  printf("freeing...\n");
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++) {
      _mm_free(it->K);
      _mm_free(it->H);
      _mm_free(it->F);
      _mm_free(it->x_old);
      _mm_free(it->x_new);
      _mm_free(it->m);
  }

  printf("done\n");

}
/*
void test_equations_batch(int batch_size) {

#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif


  // int batch_size = 10;
  int num_mats   = NUM_MATS/batch_size;
  if (NUM_MATS%batch_size != 0) {
    printf("ERROR: NUM_MATS (%d) doesn't fit with batch_size (%d)\n", NUM_MATS, batch_size);
    exit(1); 
  }

  int n = NUM_ELMS; 
  int m = NUM_ELMS; 

  struct batch A[num_mats];
  struct batch B[num_mats];
  struct batch C[num_mats];
  // struct batch A;
  // struct batch B;
  // struct batch C;

  int v,i,j,k,l,ll;
  int num_err = 0;

  double start, end;

  printf("starting tuned batch...\n");
  printf("number of matrices = %d\n", NUM_MATS);
  printf("number of batches  = %d\n", num_mats);
  printf("num mats per batch = %d\n", batch_size);
  printf("elements per side  = %d\n", NUM_ELMS);

  for (v = 0; v < num_mats; v++){
    init_batch(&A[v], batch_size, n, m);
    init_batch(&B[v], batch_size, n, m);
    init_batch(&C[v], batch_size, n, m);
  }

  printf("filling batches...\n");
  for (v = 0; v < num_mats; v++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
        for (l = 0; l < batch_size; l++) {
          A[v].mats[i][j][l] = 5.;
          B[v].mats[i][j][l] = 5.;
          C[v].mats[i][j][l] = 0.;
        }
      }
    }
  }
  
  printf("multiplying...\n");
  start = omp_get_wtime();

  // struct batch BT;
  // init_batch(&BT, num_mats, B.rows, B.cols);



  for (ll = 0; ll < NUM_REPS; ll++) {
    // multiply_matrix_batch(&A, &B, &C);

  // transpose_matrix_batch(&B, &BT);

  #pragma omp parallel for private(i,j, k, l)
  for (v = 0; v < num_mats; v++){
    for (i = 0; i < A[v].rows; i++) {
      for (j = 0; j < B[v].cols; j++) {

          // #pragma vector always
          for (l = 0; l < batch_size; l++) C[v].mats[i][j][l] = 0.;

        for (k = 0; k < A[v].cols; k++) {
        
          // #pragma vector always
          // #pragma ivdep
          for (l = 0; l < batch_size; l++) {
            C[v].mats[i][j][l] = A[v].mats[i][k][l] * B[v].mats[k][j][l] + C[v].mats[i][j][l];
          }

        }
      } 
    }
  }

  } // num reps

  // free_batch(&BT);
  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  printf("num_err = %d\n", num_err);
  printf("freeing...\n");
  for (v = 0; v < num_mats; v++){
    free_batch(&A[v]);
    free_batch(&B[v]);
    free_batch(&C[v]);
  }
  printf("done...\n");
}

void test_equations_mkl() {

#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

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
  }
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++) {
    for (j = 0; j < row*col; j++) {
      it->A[j] = 5.;
      it->B[j] = 5.;
      it->C[j] = 5.;
    }
  
  }

  printf("multiplying...\n");
  start = omp_get_wtime();
  
  for (l = 0; l < NUM_REPS; l++) {
    #pragma omp parallel for
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


#ifdef MKLROOT

void test_equations_mkl_batch() {

#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

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
#endif
*/

