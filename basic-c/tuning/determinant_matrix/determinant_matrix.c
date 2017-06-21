// currently not tuned because of function calls

#include "../../linear_algebra.h"

double determinant_matrix(double* mat_a, int n) {


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

      param VEC[] = [False,True];

      param CFLAGS[] = ['-O0', '-O1', '-O2', '-O3'];

    }

    def input_params {
      let N = [10, 20];
      param n[] = N;
    }

    def input_vars {
      decl dynamic double mat_a[n*n] = random;
    }

    def search {
      arg algorithm = 'Exhaustive';
    }

  ) */


  double det = 1.0;

  int i, num_pivots;
  int size_a = n * n;

  double L[size_a];
  double U[size_a];
  double P[size_a];
  
  num_pivots = compute_LUP(mat_a, L, U, P, n);

  if(num_pivots == -1) return 0;
  
  det = (num_pivots%2) == 1 ? -1.0 : 1.0;


  /* begin Loop (  
    transform Composite(
      unrolljam = (['i'],[U_I]),
      vector = (VEC, ['ivdep','vector always'])
    )
    for (i = 0; i <= n-1; i++) {
      det *= U[i*n+i];
    }
  ) */

  for (i = 0; i <= n-1; i++) {
    det *= U[i*n+i];
  }
  

/* end @*/
/* end @*/

  return det;
}

