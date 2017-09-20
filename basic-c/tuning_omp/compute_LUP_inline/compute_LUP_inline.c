#include "../../linear_algebra.h"


int compute_LUP(KALMAN_TYPE* mat_a, KALMAN_TYPE* L, KALMAN_TYPE* U, KALMAN_TYPE* P, int n) {
 

  /*@ begin PerfTuning (

    def build {
      arg build_command = 'gcc';
      #arg libs = '-lrt';  # Only needed on linux
   arg libs = '-fopenmp';
    } 

    def performance_counter {
      arg repetitions = 50;
    }

    def performance_params {  
      param U_I[] = range(1,6);
      param U_J[] = range(1,6);
      param U_K[] = range(1,6);

      param U_I2[] = range(1,6);

      param U_I3[] = range(1,6);
      param U_J3[] = range(1,6);

      param U_I5[] = range(1,6);
      param U_J5[] = range(1,6);


      param VEC[] = [False,True];

      param CFLAGS[] = ['-O1', '-O2', '-O3'];

      constraint unroll_limit = ((U_I == 1) or (U_J == 1));
      constraint unroll_limit_3 = ((U_I3 == 1) or (U_J3 == 1));
      constraint unroll_limit_5 = ((U_I5 == 1) or (U_J5 == 1));


    }

    def input_params {
      let N = [6];
      param n[] = N;
    }

    def input_vars {
      decl dynamic double mat_a[n*n] = random;
      decl dynamic double L[n*n] = 0;
      decl dynamic double U[n*n] = 0;
      decl dynamic double P[n*n] = 0;
    }

    def search {
      arg algorithm = 'Randomsearch';
      arg total_runs  = 1000000;
    }

  ) @*/


  int i2, j2, k2;
  int i, j, k, ind_max;
  int it, i2t, jt, j2t, kt, k2t;
  int ii, jj, kk;
  int iii, jjj, kkk;

  int cnt_pivots = 0;
  int size_a = n*n;
  double tolerance = 5E-300;
  double max_a, abs_a, coeff;
  // double temp_row[n];
  double scalar_1, scalar_2;

  
  /*@ begin Loop ( 

  transform Composite(
      vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U_I3, parallelize=True)
  for (i2 = 0; i2 <= n-1; i2++) {
    transform UnrollJam(ufactor=U_J3, parallelize=False)
    for (j2 = 0; j2 <= n-1; j2++) {
      if(i2 == j2) {
        P[n * i2 + j2] = 1;
        L[n * i2 + j2] = 1;
      } else {
        P[n * i2 + j2] = 0;
        L[n * i2 + j2] = 0;
      }
    }
  }

  transform Composite(
      vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U_I2, parallelize=False)
  for (i2 = 0; i2 <= size_a-1; i2++) {
    U[i2] = mat_a[i2];
  }



  for (i = 0; i <= n-1; i++) {
    if(U[i * n + i] > 0) max_a = U[i * n + i]; 
    else max_a = 0 - U[i * n + i];
    ind_max = i;

    transform Composite(
      vector = (VEC, ['ivdep','vector always'])
    )    
    transform UnrollJam(ufactor=U_J, parallelize=False)
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


    if (ind_max == i){}
    else {
      cnt_pivots++;

      transform Composite(
        vector = (VEC, ['ivdep','vector always'])
      )
      transform UnrollJam(ufactor=U_K, parallelize=False)
      for (k = 0; k <= n-1; k++){
        scalar_1 = P[i * n+k];
        P[i * n+k] = P[ind_max * n+k];
        P[ind_max * n+k] = scalar_1;
      
        scalar_2 = U[i * n+k];
        U[i * n+k] = U[ind_max * n+k];
        U[ind_max * n+k] = scalar_2;
      }
    }

    transform Composite(
      vector = (VEC, ['ivdep','vector always'])
    )
    transform UnrollJam(ufactor=U_I5, parallelize=True)
    for(j = i+1; j <= n-1; j++) {
      coeff = (U[j * n+i]/U[i * n+i]);
      L[j * n+i] = coeff;

      transform UnrollJam(ufactor=U_J5, parallelize=False)
      for (k = i; k <= n-1; k++) {
        U[j * n + k] -= coeff * U[i * n + k];
      }
    }

  } //end main for



) @*/

/*@ end @*/
/*@ end @*/



  for (i2 = 0; i2 <= n-1; i2++) {
    for (j2 = 0; j2 <= n-1; j2++) {
      if(i2 == j2) {
        P[n * i2 + j2] = 1;
        L[n * i2 + j2] = 1;
      } else {
        P[n * i2 + j2] = 0;
        L[n * i2 + j2] = 0;
      }
    }
  }


  for (i2 = 0; i2 <= size_a-1; i2++) {
    U[i2] = mat_a[i2];
  }

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


    if ( !(ind_max == i) )  {
      cnt_pivots++;

      for (k = 0; k <= n-1; k++){
        scalar_1 = P[i * n+k];
        P[i * n+k] = P[ind_max * n+k];
        P[ind_max * n+k] = scalar_1;
      
        scalar_2 = U[i * n+k];
        U[i * n+k] = U[ind_max * n+k];
        U[ind_max * n+k] = scalar_2;
      }
    }

    for(j = i+1; j <= n-1; j++) {
      coeff = (U[j * n+i]/U[i * n+i]);
      L[j * n+i] = coeff;
      for (k = i; k <= n-1; k++) {
        U[j * n + k] -= coeff * U[i * n + k];
      }
    }

  } //end main for

  return cnt_pivots;


}
