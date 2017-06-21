// not tuned yet
#include "../../linear_algebra.h"

void cofactor_matrix(TYPE* mat_a, int n, TYPE* mat_c) {


  /* begin PerfTuning (

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
      param U_R[] = range(1,31);

      param VEC[] = [False,True];

      param CFLAGS[] = ['-O0', '-O1', '-O2', '-O3'];

    }

    def input_params {
      let N = [10, 20];
      param n[] = N;
    }

    def input_vars {
      decl dynamic double mat_a[n*n] = random;
      decl dynamic double mat_c[n*n] = 0;
    }

    def search {
      arg algorithm = 'Exhaustive';
    }

  ) */

  TYPE det = 0;
  int i, j, r, c, k, row, rr;
  int n_b = n-1;
  int size_b = (n-1) * (n-1);
  int size_a = n * n;
  int sign = 1;
  TYPE mat_b[size_b];



  /* begin Loop (  
  transform Composite(
    unrolljam = (['i','j','r'],[U_I,U_J,U_R]),
    vector = (VEC, ['ivdep','vector always'])
  )
  for (i = 0; i <= n-1; i++) {
    row = n * i;
    for (j = 0; j <= n-1; j++) {

        k = 0;
        for (r = 0; r <= n-1; r++) {
          if(r != i){
            rr = n * r;
            for (c = 0; c <= n-1; c++) {
              if(c != j) mat_b[k++] = mat_a[rr + c];
            }
          }
        }

      det = determinant_matrix(mat_b, n_b);
      mat_c[row + j] = sign * det;
      sign = sign * -1;
    }
    sign = sign * -1;
  }
  ) */

  for (i = 0; i <= n-1; i++) {
    row = n * i;
    for (j = 0; j <= n-1; j++) {

        k = 0;
        for (r = 0; r <= n-1; r++) {
          if(r != i){
            rr = n * r;
            for (c = 0; c <= n-1; c++) {
              if(c != j) mat_b[k++] = mat_a[rr + c];
            }
          }
        }

      det = determinant_matrix(mat_b, n_b);
      mat_c[row + j] = sign * det;
      sign = sign * -1;
    }
    sign = sign * -1;
  }


/* end @*/
/* end @*/

}
