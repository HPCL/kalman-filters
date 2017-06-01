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

      param VEC[] = [False,True];

      param CFLAGS[] = ['-O0', '-O1', '-O2', '-O3'];

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


  int i, j, k, ind_max, curr_row, next_row, row;

  int ii, jj, kk;
  int iii, jjj, kkk;

  int cnt_pivots = 0;
  int size_a = n*n;
  double tolerance = 5E-300;
  double max_a, abs_a, coeff;
  double temp_row[n];

  
  /*@ begin Loop ( 



  for (i = 0; i <= n-1; i++) {
    row = n * i;
    for (j = 0; j <= n-1; j++) {
      if(i == j)
        P[row + j] = 1;
      else
        P[row + j]= 0;
    }
  }

  for (i = 0; i <= n-1; i++) {
    row = n * i;
    for (j = 0; j <= n-1; j++) {
      if(i == j)
        L[row + j] = 1;
      else
        L[row + j]= 0;
    }
  }

  for (i = 0; i <= size_a-1; i++)
    U[i] = mat_a[i];


  transform Composite(
    unrolljam = (['i'],[U_I])
  )
  for(i = 0; i <= n-1; i++) {
    curr_row = i * n;
    if(U[curr_row + i] > 0) max_a = U[curr_row + i]; 
    else max_a = 0 - U[curr_row + i];
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
    ind_max *= n;

    for (k = 0; k <= n-1; k++)
      temp_row[k] = P[curr_row+k];
    for (k = 0; k <= n-1; k++)
      P[curr_row+k] = P[ind_max+k];
    for (k = 0; k <= n-1; k++)
      P[ind_max+k] = temp_row[k];


    for (k = 0; k <= n-1; k++)
      temp_row[k] = U[curr_row+k];
    for (k = 0; k <= n-1; k++)
      U[curr_row+k] = U[ind_max+k];
    for (k = 0; k <= n-1; k++)
      U[ind_max+k] = temp_row[k];


    for(j = i+1; j <= n-1; j++) {
      next_row = j * n;
      coeff = (U[next_row+i]/U[curr_row+i]);
      L[next_row+i] = coeff;
      for (k = i; k <= n-1; k++) {
        U[next_row + k] -= coeff * U[curr_row + k];
      }
    }

  } //end main for



) @*/

/*@ end @*/
/*@ end @*/

  return cnt_pivots;


}
