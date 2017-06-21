#include "../../linear_algebra.h"

void multiply_matrix(TYPE* mat_a, int rows_a, int cols_a, 
                     TYPE* mat_b, int cols_b, 
                     TYPE* mat_c) {


  /*@ begin PerfTuning (

    def build {
      arg build_command = 'gcc';
      #arg libs = '-lrt';  # Only needed on linux
    } 

    def performance_counter {
      arg repetitions = 5;
    }

    def performance_params {  
      param U_I[] = range(1,31);
      param U_J[] = range(1,31);
      param U_K[] = range(1,31);

      param VEC[] = [False,True];

      param CFLAGS[] = ['-O0', '-O1', '-O2', '-O3'];
      constraint unroll_limit = ((U_I == 1) or (U_J == 1) or (U_K == 1));

    }

    def input_params {
      let N = [10, 20];
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
      arg algorithm = 'Exhaustive';
    }

  ) @*/

  int i, j, k;
  int c_ind, a_row, c_row;


  /*@ begin Loop (  
    transform Composite(
      unrolljam = (['i','j','k'],[U_I,U_J,U_K]),
      vector = (VEC, ['ivdep','vector always'])
    )
    for (i = 0; i <= rows_a-1; i++) {
      a_row = cols_a * i;
      c_row = cols_b * i;
      for (j = 0; j <= cols_b-1; j++) {
        c_ind = j + c_row;
        mat_c[c_ind] = 0;
        for (k = 0; k <= cols_a-1; k++) {
          mat_c[c_ind] += mat_a[a_row + k] * mat_b[cols_b * k + j];
        }
      } 
    }
  ) @*/

  for (i = 0; i <= rows_a-1; i++) {
    a_row = cols_a * i;
    c_row = cols_b * i;
    for (j = 0; j <= cols_b-1; j++) {
      c_ind = j + c_row;
      mat_c[c_ind] = 0;
      for (k = 0; k <= cols_a-1; k++) {
        mat_c[c_ind] += mat_a[a_row + k] * mat_b[cols_b * k + j];
      }
    } 
  }

/*@ end @*/
/*@ end @*/
}
