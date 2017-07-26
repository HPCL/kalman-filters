#include "../../linear_algebra.h"

void multiply_matrix(TYPE* mat_a, int rows_a, int cols_a, 
                     TYPE* mat_b, int cols_b, 
                     TYPE* mat_c) {


  /*@ begin PerfTuning (

    def build {
      arg build_command = 'gcc';
    } 

    def performance_counter {
      arg repetitions = 50;
    }

    def performance_params {  
      param U_I0[] = range(1,6);
      param U_J0[] = range(1,6);
      param U_I[] = range(1,6);
      param U_J[] = range(1,6);
      param U_K[] = range(1,6);

      param VEC[] = [False,True];

      param RT0_I[] = [1,2,6];
      param RT0_J[] = [1,2,6];
      param RT1_I[] = [1,2,6];
      param RT1_J[] = [1,2,6];
      param RT1_K[] = [1,2,6];

      param CFLAGS[] = ['-O1', '-O2', '-O3'];
      constraint unroll_limit_0 = ((U_I == 1) or (U_J == 1));
      constraint reg_capacity_0 = (RT1_I*RT1_J <= 150);
      constraint unroll_limit = ((U_I == 1) or (U_J == 1) or (U_K == 1));
      constraint reg_capacity_1 = (RT1_I*RT1_J*RT1_K <= 150);

    }

    def input_params {
      let N = [6, 12];
      param rows_a[] = N;
      param cols_a[] = N;
      param cols_b[] = N;
    }

    def input_vars {
      decl dynamic double mat_a[rows_a*cols_a] = random;
      decl dynamic double mat_b[cols_b*cols_b] = random;
      decl dynamic double mat_c[rows_a*cols_b] = 0;
    }

    def search {
      arg algorithm = 'Randomsearch';
      arg total_runs  = 1000000;
    }

  ) @*/

  int i, j, k;  
  int it,jt, kt;
  int c_ind, a_row, c_row;


  /*@ begin Loop (  
    transform Composite(
      unrolljam = (['i','j'],[U_I0,U_J0]),
      vector = (VEC, ['ivdep','vector always']),
      regtile = (['i','j'],[RT0_I,RT0_J])
    )
    for (i = 0; i <= rows_a-1; i++) {
      for (j = 0; j <= cols_b-1; j++) {
        mat_c[j + cols_b * i] = 0;
      }
    } 

    transform Composite(
      unrolljam = (['i','j','k'],[U_I,U_J,U_K]),
      vector = (VEC, ['ivdep','vector always']),
      regtile = (['i','j','k'],[RT1_I,RT1_J,RT1_K])
    )
    for (i = 0; i <= rows_a-1; i++) {
      for (j = 0; j <= cols_b-1; j++) {
        for (k = 0; k <= cols_a-1; k++) {
          mat_c[j + cols_b * i] += mat_a[cols_a * i + k] * mat_b[cols_b * k + j];
        }
      } 
    }
  ) @*/

  for (i = 0; i <= rows_a-1; i++) {
    for (j = 0; j <= cols_b-1; j++) {
      mat_c[j + cols_b * i] = 0;
    }
  } 

  for (i = 0; i <= rows_a-1; i++) {
    for (j = 0; j <= cols_b-1; j++) {
      for (k = 0; k <= cols_a-1; k++) {
        mat_c[j + cols_b * i] += mat_a[cols_a * i + k] * mat_b[cols_b * k + j];
      }
    } 
  }

/*@ end @*/
/*@ end @*/
}
