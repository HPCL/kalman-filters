#include "../../linear_algebra.h"


int compute_LUP_inline(TYPE* mat_a, TYPE* L, TYPE* U, TYPE* P, int n) {
 

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

      param U_I2[] = range(1,31);
      param U_J2[] = range(1,31);
      param U_K2[] = range(1,31);

      # param VEC[] = [False,True];

      # param CFLAGS[] = ['-O0', '-O1', '-O2', '-O3'];

      # constraint unroll_limit = ((U_I == 1) or (U_J == 1));

    }

    def input_params {
      let N = [100];
      param n[] = N;
    }

    def input_vars {
      decl dynamic double mat_a[n*n] = random;
      decl dynamic double L[n*n] = 0;
      decl dynamic double U[n*n] = 0;
      decl dynamic double P[n*n] = 0;
    }

    def search {
      arg algorithm = 'Exhaustive';
    }

  ) @*/


  int i2, j2, k2;
  int i, j, k, ind_max;
  int ii, jj, kk;
  int iii, jjj, kkk;

  int cnt_pivots = 0;
  int size_a = n*n;
  double tolerance = 5E-300;
  double max_a, abs_a, coeff;
  double temp_row[n];

  
  /*@ begin Loop ( 

  transform Composite(
    unrolljam = (['i2','j2'],[U_I2,U_J2])
  )
  for (i2 = 0; i2 <= n-1; i2++) {
    for (j2 = 0; j2 <= n-1; j2++) {
      if(i2 == j2)
        P[n * i2 + j2] = 1;
      else
        P[n * i2 + j2]= 0;
    }
  }


  transform Composite(
    unrolljam = (['i2'],[U_I2])
  )
  for (i2 = 0; i2 <= n-1; i2++) {
    for (j2 = 0; j2 <= n-1; j2++) {
      if(i2 == j2)
        L[n * i2 + j2] = 1;
      else
        L[n * i2 + j2]= 0;
    }
  }

  transform Composite(
    unrolljam = (['i2'],[U_I2])
  )
  for (i2 = 0; i2 <= size_a-1; i2++) {
    U[i2] = mat_a[i2];
  }


  transform Composite(
    unrolljam = (['i'],[U_I])
  )
  for (i = 0; i <= n-1; i++) {
    if(U[i * n + i] > 0) max_a = U[i * n + i]; 
    else max_a = 0 - U[i * n + i];
    ind_max = i;

    for (j = i+1; j <= n-1; j++) {
      if(U[j * n + i] > 0) abs_a = U[j * n + i]; 
      else abs_a = 0 - U[j * n + i];
      if (abs_a > max_a) {
        max_a = abs_a;
        ind_max = j;
      }
    }
    
    if (max_a <= tolerance) {
      cnt_pivots = 0 - 1;
      break;
    }


    cnt_pivots++;

    for (k = 0; k <= n-1; k++)
      temp_row[k] = P[i * n+k];
    for (k = 0; k <= n-1; k++)
      P[i * n+k] = P[ind_max * n+k];
    for (k = 0; k <= n-1; k++)
      P[ind_max * n+k] = temp_row[k];


    for (k = 0; k <= n-1; k++)
      temp_row[k] = U[i * n+k];
    for (k = 0; k <= n-1; k++)
      U[i * n+k] = U[ind_max * n+k];
    for (k = 0; k <= n-1; k++)
      U[ind_max * n+k] = temp_row[k];


    for(j = i+1; j <= n-1; j++) {
      coeff = (U[j * n+i]/U[i * n+i]);
      L[j * n+i] = coeff;
      for (k = i; k <= n-1; k++) {
        U[j * n + k] -= coeff * U[i * n + k];
      }
    }

  } //end main for



) @*/

/*@ end @*/
/*@ end @*/

  return cnt_pivots;


}
