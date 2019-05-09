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

void test_inverse_batch();
void test_multiply();
void test_multiply_large();
void test_multiply_mkl();
void test_multiply_mkl_batch();
void test_multiply_small_batch();
void test_mkl_compact();
// void test_multiply_batch();
void test_multiply_batch(int batch_size);
void test_multiply_batch_untuned();
void test_add_batch();
void test_transpose_batch();
void test_mult_by_scalar_batch();
void test_zero_and_id_batch();

int main(int argc, char **argv) {

  // char temp[16];
  // printf("Enter 'c' to continue. Note it may require multiple entries.\n");
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
  printf("\n");
  // test_multiply_large(); printf("\n");
  // test_multiply_batch_untuned(); printf("\n");
  // test_multiply_batch(BATCH_SIZE); printf("\n");
  // test_multiply_mkl(); printf("\n");
  // test_multiply_mkl_batch(); printf("\n");
  test_mkl_compact(); printf("\n");
  // scanf("%s", temp);
  // test_multiply_small_batch();
  // test_multiply();
  // scanf("%s", temp);
  // test_compute_LUP();
  // scanf("%s", temp);
  // test_compute_LUP_inline();
  // scanf("%s", temp);
  // printf("Bye now!\n");

  return 0;
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


void test_multiply_batch(int batch_size) {

// #ifdef USE_CALI
// CALI_CXX_MARK_FUNCTION;
// #endif


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

#ifdef USE_CALI
CALI_MARK_BEGIN("mult");
#endif


  
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

#ifdef USE_CALI
CALI_MARK_END("mult");
#endif
  // printf("checking...\n");
  // for (i = 0; i < n; i++) {
  //   for (j = 0; j < m; j++) {
  //     for (l = 0; l < num_mats; l++) {
  //       if (C.mats[i][j][l] != 25.*(double)n) {
  //         printf("ERROR %f\n", C.mats[i][j][l]);
  //         num_err++;
  //       } 
  //     }
  //   }
  // }
  printf("num_err = %d\n", num_err);
  printf("freeing...\n");
  for (v = 0; v < num_mats; v++){
    free_batch(&A[v]);
    free_batch(&B[v]);
    free_batch(&C[v]);
  }
  printf("done...\n");
}



void test_multiply_batch_untuned() {

#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  struct batch A;
  struct batch B;
  struct batch C;

  int num_mats = NUM_MATS;
  int n = NUM_ELMS; 
  int m = NUM_ELMS; 

  int i,j,k,l;
  int num_err = 0;

  double start, end;

  printf("starting untuned batch...\n");
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
    untuned_multiply_matrix_batch(&A, &B, &C);
  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  // printf("checking...\n");
  // for (i = 0; i < n; i++) {
  //   for (j = 0; j < m; j++) {
  //     for (l = 0; l < num_mats; l++) {
  //       if (C.mats[i][j][l] != 25.*(double)n) {
  //         printf("ERROR %f\n", C.mats[i][j][l]);
  //         num_err++;
  //       } 
  //     }
  //   }
  // }
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


void test_multiply_mkl_batch() {

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

  printf("multiplying...\n");
  start = omp_get_wtime();
  
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

void test_mkl_compact() {

// #ifdef USE_CALI
// CALI_CXX_MARK_FUNCTION;
// #endif


  int i,j,l, num_mats=NUM_MATS;

  const int col = NUM_ELMS, row = NUM_ELMS;

  double **A, **B, **C;
  double *_A, *_B, *_C;

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

  MKL_COMPACT_PACK mkl_format = mkl_get_format_compact();
  MKL_INT mkl_size_compact    = mkl_dget_size_compact (NUM_ELMS, NUM_ELMS, mkl_format, NUM_MATS);

  _A = (double*) mkl_malloc(mkl_size_compact,64);
  _B = (double*) mkl_malloc(mkl_size_compact,64);
  _C = (double*) mkl_malloc(mkl_size_compact,64);

#ifdef USE_CALI
CALI_MARK_BEGIN("mult");
#endif


  
  mkl_dgepack_compact(MKL_ROW_MAJOR, NUM_ELMS, NUM_ELMS, A, NUM_ELMS, _A, NUM_ELMS, mkl_format, NUM_MATS);
  mkl_dgepack_compact(MKL_ROW_MAJOR, NUM_ELMS, NUM_ELMS, B, NUM_ELMS, _B, NUM_ELMS, mkl_format, NUM_MATS);
  mkl_dgepack_compact(MKL_ROW_MAJOR, NUM_ELMS, NUM_ELMS, C, NUM_ELMS, _C, NUM_ELMS, mkl_format, NUM_MATS);

  printf("multiplying...\n");
  start = omp_get_wtime();

  
  for (l = 0; l < NUM_REPS; l++) {
  mkl_dgemm_compact(
    MKL_ROW_MAJOR,  // layout 
    MKL_NOTRANS,    // transpose A
    MKL_NOTRANS,    // transpose B
    NUM_ELMS,       // A rows
    NUM_ELMS,       // B cols
    NUM_ELMS,       // A col B row
    1.0,            // alpha (scalar for A)
    _A,             // double* to A
    NUM_ELMS,       // still have no idea
    _B,             // double* to B
    NUM_ELMS,       // still have no idea
    0.0,            // beta (scalar for C)
    _C,             // double* to C
    NUM_ELMS,       // still have no idea
    mkl_format,     // compact format from the mkl function
    NUM_MATS        // total number of matrices
  );
  }

  end = omp_get_wtime();
  printf("time %f seconds \n", end - start);

  mkl_dgeunpack_compact (MKL_ROW_MAJOR, NUM_ELMS, NUM_ELMS, A, NUM_ELMS, _A, NUM_ELMS, mkl_format, NUM_MATS);
  mkl_dgeunpack_compact (MKL_ROW_MAJOR, NUM_ELMS, NUM_ELMS, B, NUM_ELMS, _B, NUM_ELMS, mkl_format, NUM_MATS);
  mkl_dgeunpack_compact (MKL_ROW_MAJOR, NUM_ELMS, NUM_ELMS, C, NUM_ELMS, _C, NUM_ELMS, mkl_format, NUM_MATS);




#ifdef USE_CALI
CALI_MARK_END("mult");
#endif
  printf("freeing...\n");
  for (i = 0; i < NUM_MATS; i++){
    mkl_free(A[i]);
    mkl_free(B[i]);
    mkl_free(C[i]);
  }
  mkl_free(A);
  mkl_free(B);
  mkl_free(C);

  mkl_free(_A);
  mkl_free(_B);
  mkl_free(_C);

  printf("done\n");


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

