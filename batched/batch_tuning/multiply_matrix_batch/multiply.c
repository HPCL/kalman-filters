
#include "../../matrix_batch.h"

void _multiply_matrix_batch(KALMAN_TYPE*** A, int rows_a, int cols_a,
                            KALMAN_TYPE*** B, int rows_b, int cols_b,
                            KALMAN_TYPE*** C,
                            int num_mats) {

/*@ begin PerfTuning (

    def build {
      arg build_command = 'icc -O2';
      #arg libs = '-lrt';  # Only needed on linux
    } 

    def performance_counter {
      arg repetitions = 2;
    }

    def performance_params {  
      param U_L[] = range(1,129);

      param VEC[] = [False,True];

      param RT1_L[] = [1,32];

      param T1_L[] = [1, 512, 1024];

      constraint tile2 = ((T1_L == 1) or (RT1_L == 1));
    }

    def input_params {
      let N = [8, 64, 128, 256];
      let M = [64, 256, 1000, 5000];
      param rows_a[] = N;
      param num_mats[] = M;
    }

    def input_vars {
      decl dynamic double A[rows_a][rows_a][num_mats] = random;
      decl dynamic double B[rows_a][rows_a][num_mats] = random;
      decl dynamic double C[rows_a][rows_a][num_mats] = 0;
    }

    def search {
      arg algorithm = 'MSimplex';
      arg total_runs  = 250;
    }

  ) @*/

  int i,j,k,l;
  int it,jt,kt,lt, ll;
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y)) 


  // transform Composite(
  //   unrolljam = (['l'],[U_L]),
  //   regtile = (['l'],[RT1_L]),
  //   tile = ([('l',T1_L,'ll')]),
  //   vector = (VEC, ['vector always'])
  // )
  // for (i = 0; i <= rows_a-1; i++) {
  //   for (j = 0; j <= rows_a-1; j++) {
  //     for (l = 0; l <= num_mats-1; l++) {
  //       C[i][j][l] = 0;
  //     }
  //   }
  // }

/*@ begin Loop (  
  

      
  transform Composite(
    unrolljam = (['l'],[U_L]),
    regtile = (['l'],[RT1_L]),
    tile = ([('l',T1_L,'ll')]),
    vector = (VEC, ['ivdep'])
  )
  for (i = 0; i <= rows_a-1; i++) {
    for (j = 0; j <= rows_a-1; j++) {
      for (k = 0; k <= rows_a-1; k++) {
        for (l = 0; l <= num_mats-1; l++) {
          C[i][j][l] += A[i][k][l] * B[k][j][l];
        }
      }
    } 
  }

  ) @*/

     

  for (i = 0; i <= rows_a-1; i++) {
    for (j = 0; j <= rows_a-1; j++) {
      for (k = 0; k <= rows_a-1; k++) {
        #pragma ivdep
        for (l = 0; l <= num_mats-1; l++) {
          C[i][j][l] += A[i][k][l] * B[k][j][l];
        }
      }
    } 
  }

/*@ end @*/
/*@ end @*/
} 
