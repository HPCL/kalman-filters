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


double test_equations_normal();
double test_equations_batch(int batch_size);
double test_equations_batch_fusion(int batch_size);
double test_equations_mkl();
double test_equations_mkl_batch();

int main(int argc, char **argv) {

  printf("regular,batched,fused\n");

  for (int i = 0; i < 5; i++) {

    double reg = test_equations_normal();
    double bat = test_equations_batch(BATCH_SIZE);
    double fus = test_equations_batch_fusion(BATCH_SIZE);
    printf("%f,%f,%f\n", reg,bat,fus);

  }

  return 0;
}



double test_equations_normal() {

#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  int i,j,l, num_mats=NUM_MATS;

  const int col = NUM_ELMS, row = NUM_ELMS;
  std::vector<target> stuff(num_mats);

  struct target* temp;
  double start, end;

  // printf("starting regular...\n");
  // printf("number of matrices = %d\n", NUM_MATS);
  // printf("elements per side  = %d\n", NUM_ELMS);
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

  // printf("multiplying...\n");
  start = omp_get_wtime();
  

  double * x_mid      = (double*) _mm_malloc(col*sizeof(double), 64);
  double * temp_vec_1 = (double*) _mm_malloc(col*sizeof(double), 64);
  double * temp_vec_2 = (double*) _mm_malloc(col*sizeof(double), 64);

  for (l = 0; l < NUM_REPS; l++) {

    for (std::vector<target>::iterator itt = stuff.begin(); itt != stuff.end(); itt++) {
      multiply_matrix(itt->F, row, col, itt->x_old, 1, x_mid);
      multiply_matrix(itt->H, row, col, x_mid,      1, temp_vec_1);

      subtract_matrix(itt->m, col, 1, temp_vec_1, temp_vec_2);
      multiply_matrix(itt->K, row, col, temp_vec_2, 1, temp_vec_1);
      add_matrix(x_mid, col, 1, temp_vec_1, itt->x_new);
    }

  }
  end = omp_get_wtime();
  // printf("time %f seconds \n", end - start);

  int vec_row = 1, num_err = 0;  
  // printf("checking...\n");
  // for (i = 0; i < col; i++) {
  //   for (j = 0; j < vec_row; j++) {
  //     // for (l = 0; l < num_mats; l++) {
  //       if (x_mid[j + vec_row * i] != 25.*(double)col) {
  //         printf("ERROR %f\n", x_mid[j + vec_row * i]);
  //         num_err++;
  //       } 
  //     // }
  //   }
  // }

  // printf("freeing...\n");
  for (std::vector<target>::iterator it = stuff.begin(); it != stuff.end(); it++) {
      _mm_free(it->K);
      _mm_free(it->H);
      _mm_free(it->F);
      _mm_free(it->x_old);
      _mm_free(it->x_new);
      _mm_free(it->m);
  }

  // printf("done\n");

  return end - start;
}

double test_equations_batch(int batch_size) {

#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif


  // int batch_size = 10;
  int num_blocks   = NUM_MATS/batch_size;
  if (NUM_MATS%batch_size != 0) {
    printf("ERROR: NUM_MATS (%d) doesn't fit with batch_size (%d)\n", NUM_MATS, batch_size);
    exit(1); 
  }

  int row = NUM_ELMS; 
  int col = NUM_ELMS; 

  struct batch K[num_blocks];
  struct batch H[num_blocks];
  struct batch F[num_blocks];

  struct batch x_old[num_blocks];
  struct batch x_mid[num_blocks];
  struct batch x_new[num_blocks];
  struct batch m[num_blocks];

  struct batch temp_vec_1[num_blocks];
  struct batch temp_vec_2[num_blocks];

  int v,i,j,k,l,ll;
  int num_err = 0;

  double start, end;

  // printf("starting tuned batch...\n");
  // printf("number of matrices = %d\n", NUM_MATS);
  // printf("number of batches  = %d\n", num_blocks);
  // printf("num mats per batch = %d\n", batch_size);
  // printf("elements per side  = %d\n", NUM_ELMS);

  for (v = 0; v < num_blocks; v++){
    init_batch(&K[v], batch_size, row, col);
    init_batch(&H[v], batch_size, row, col);
    init_batch(&F[v], batch_size, row, col);

    init_batch(&x_old[v], batch_size, col, 1);
    init_batch(&x_mid[v], batch_size, col, 1);
    init_batch(&x_new[v], batch_size, col, 1);
    init_batch(&m[v],     batch_size, col, 1);

    init_batch(&temp_vec_1[v], batch_size, col, 1);
    init_batch(&temp_vec_2[v], batch_size, col, 1);
  }

  // printf("filling batches...\n");
  for (v = 0; v < num_blocks; v++) {
    for (i = 0; i < row; i++) {
      for (j = 0; j < col; j++) {
        for (l = 0; l < batch_size; l++) {
          K[v].mats[i][j][l] = 5.;
          H[v].mats[i][j][l] = 5.;
          F[v].mats[i][j][l] = 5.;
        }
      }
    }
    for (i = 0; i < col; i++) {
      for (j = 0; j < 1; j++) {
        for (l = 0; l < batch_size; l++) {
          x_old[v].mats[i][j][l] = 5.;
          x_mid[v].mats[i][j][l] = 5.;
          x_new[v].mats[i][j][l] = 5.;
          m[v].mats[i][j][l] = 5.;

          temp_vec_1[v].mats[i][j][l] = 5.;
          temp_vec_2[v].mats[i][j][l] = 5.;
        }
      }
    }
  }
  
  // printf("multiplying...\n");
  start = omp_get_wtime();

  for (ll = 0; ll < NUM_REPS; ll++) {

    for (v = 0; v < num_blocks; v++) {  
      multiply_matrix_batch(&F[v], &x_old[v], &x_mid[v]);
      multiply_matrix_batch(&H[v], &x_mid[v], &temp_vec_1[v]);

      subtract_matrix_batch(&m[v], &temp_vec_1[v], &temp_vec_2[v]);
      multiply_matrix_batch(&K[v], &temp_vec_2[v], &temp_vec_1[v]);
      add_matrix_batch(&x_mid[v], &temp_vec_1[v], &x_new[v]);
    }

  } // num reps

  // free_batch(&BT);
  end = omp_get_wtime();
  // printf("time %f seconds \n", end - start);

  // printf("num_err = %d\n", num_err);
  // printf("freeing...\n");
  for (v = 0; v < num_blocks; v++){
    free_batch(&K[v]);
    free_batch(&H[v]);
    free_batch(&F[v]);

    free_batch(&x_old[v]);
    free_batch(&x_mid[v]);
    free_batch(&x_new[v]);
    free_batch(&m[v]);

    free_batch(&temp_vec_1[v]);
    free_batch(&temp_vec_2[v]);
  }
  // printf("done...\n");

  return end - start;
}


double test_equations_batch_fusion(int batch_size) {

#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif


  // int batch_size = 10;
  int num_blocks   = NUM_MATS/batch_size;
  if (NUM_MATS%batch_size != 0) {
    printf("ERROR: NUM_MATS (%d) doesn't fit with batch_size (%d)\n", NUM_MATS, batch_size);
    exit(1); 
  }

  int row = NUM_ELMS; 
  int col = NUM_ELMS; 

  struct batch K[num_blocks];
  struct batch H[num_blocks];
  struct batch F[num_blocks];

  struct batch x_old[num_blocks];
  struct batch x_mid[num_blocks];
  struct batch x_new[num_blocks];
  struct batch m[num_blocks];

  struct batch temp_vec_1[num_blocks];
  struct batch temp_vec_2[num_blocks];

  int v,i,j,k,l,ll;
  int num_err = 0;

  double start, end;

  // printf("starting tuned batch fusion...\n");
  // printf("number of matrices = %d\n", NUM_MATS);
  // printf("number of batches  = %d\n", num_blocks);
  // printf("num mats per batch = %d\n", batch_size);
  // printf("elements per side  = %d\n", NUM_ELMS);

  for (v = 0; v < num_blocks; v++){
    init_batch(&K[v], batch_size, row, col);
    init_batch(&H[v], batch_size, row, col);
    init_batch(&F[v], batch_size, row, col);

    init_batch(&x_old[v], batch_size, col, 1);
    init_batch(&x_mid[v], batch_size, col, 1);
    init_batch(&x_new[v], batch_size, col, 1);
    init_batch(&m[v],     batch_size, col, 1);

    init_batch(&temp_vec_1[v], batch_size, col, 1);
    init_batch(&temp_vec_2[v], batch_size, col, 1);
  }

  // printf("filling batches...\n");
  for (v = 0; v < num_blocks; v++) {
    for (i = 0; i < row; i++) {
      for (j = 0; j < col; j++) {
        for (l = 0; l < batch_size; l++) {
          K[v].mats[i][j][l] = 5.;
          H[v].mats[i][j][l] = 5.;
          F[v].mats[i][j][l] = 5.;
        }
      }
    }
    for (i = 0; i < col; i++) {
      for (j = 0; j < 1; j++) {
        for (l = 0; l < batch_size; l++) {
          x_old[v].mats[i][j][l] = 5.;
          x_mid[v].mats[i][j][l] = 5.;
          x_new[v].mats[i][j][l] = 5.;
          m[v].mats[i][j][l] = 5.;

          temp_vec_1[v].mats[i][j][l] = 5.;
          temp_vec_2[v].mats[i][j][l] = 5.;
        }
      }
    }
  }
  
  // printf("multiplying...\n");
  start = omp_get_wtime();

  for (ll = 0; ll < NUM_REPS; ll++) {
    for (v = 0; v < num_blocks; v++) {  

      // #pragma omp parallel for private(i,j, k, l)
      for (i = 0; i < row; i++) {
        // for (j = 0; j < 1; j++) {
          for (l = 0; l < batch_size; l++) x_mid[v].mats[i][0][l] = 0.;
          for (k = 0; k < col; k++) {
            #pragma ivdep
            for (l = 0; l < batch_size; l++) {
              x_mid[v].mats[i][0][l] = F[v].mats[i][k][l] * x_old[v].mats[k][0][l] 
                                        + x_mid[v].mats[i][0][l];
            }
          }
        // } 
      }

      for (i = 0; i < row; i++) {
        // for (j = 0; j < 1; j++) {
          for (l = 0; l < batch_size; l++) temp_vec_1[v].mats[i][0][l] = 0.;
          for (k = 0; k < col; k++) {
            #pragma ivdep
            for (l = 0; l < batch_size; l++) {
              temp_vec_1[v].mats[i][0][l] = H[v].mats[i][k][l] * x_mid[v].mats[k][0][l] 
                                        + temp_vec_1[v].mats[i][0][l];
            }
          }
        // } 
      }

      for (i = 0; i < col; i++) {
        // for (j = 0; j < 1; j++) {
          for (l = 0; l < batch_size; l++) {
            temp_vec_2[v].mats[i][0][l] = m[v].mats[i][0][l] - temp_vec_1[v].mats[i][0][l];
          }
        // }
      }

      for (i = 0; i < row; i++) {
        // for (j = 0; j < 1; j++) {
          for (l = 0; l < batch_size; l++) temp_vec_1[v].mats[i][0][l] = 0.;
          for (k = 0; k < col; k++) {
            #pragma ivdep
            for (l = 0; l < batch_size; l++) {
              temp_vec_1[v].mats[i][0][l] = K[v].mats[i][k][l] * temp_vec_2[v].mats[k][0][l] 
                                        + temp_vec_1[v].mats[i][0][l];
            }
          }
        // } 
      }

      for (i = 0; i < col; i++) {
        // for (j = 0; j < 1; j++) {
          for (l = 0; l < batch_size; l++) {
            x_new[v].mats[i][0][l] = x_mid[v].mats[i][0][l] + temp_vec_1[v].mats[i][0][l];
          }
        // }
      }

    } //num blocks
  } // num reps

  // free_batch(&BT);
  end = omp_get_wtime();
  // printf("time %f seconds \n", end - start);

  // printf("num_err = %d\n", num_err);
  // printf("freeing...\n");
  for (v = 0; v < num_blocks; v++){
    free_batch(&K[v]);
    free_batch(&H[v]);
    free_batch(&F[v]);

    free_batch(&x_old[v]);
    free_batch(&x_mid[v]);
    free_batch(&x_new[v]);
    free_batch(&m[v]);

    free_batch(&temp_vec_1[v]);
    free_batch(&temp_vec_2[v]);
  }
  // printf("done...\n");

  return end - start;
}

/*
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

