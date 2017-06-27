#include "../../kalman_filter.h"

void predict(TYPE* x_hat, int n, int m, TYPE* A, TYPE* Q, TYPE* P, TYPE* x_hat_new, TYPE* A_T, TYPE* temp_1, TYPE* temp_2) {
  

/*@ begin PerfTuning (

 def build {
   arg build_command = 'gcc';
   #arg libs = '-lrt';  # Only needed on linux
 } 

 def performance_counter {
   arg repetitions = 50;
 }

 def performance_params {  
  param U1_I[]  = range(1,6);
  param U1_J[]  = range(1,6);
  param U2_I[]  = range(1,6);
  param U2_K[]  = range(1,6);
  param U02_I[] = range(1,6);
  param U3_I[]  = range(1,6);
  param U3_J[]  = range(1,6);
  param U3_K[]  = range(1,6);
  param U03_I[] = range(1,6);
  param U03_J[] = range(1,6);
  param U4_I[]  = range(1,6);
  param U4_J[]  = range(1,6);
  param U4_K[]  = range(1,6);
  param U04_I[] = range(1,6);
  param U04_J[] = range(1,6);
  param U5_I[]  = range(1,6);
  param U5_J[]  = range(1,6);

  param RT1_I[]  = [1,2,6];
  param RT1_J[]  = [1,2,6];
  param RT2_I[]  = [1,2,6];
  param RT2_K[]  = [1,2,6];
  param RT02_I[] = [1,2,6];
  param RT3_I[]  = [1,2,6];
  param RT3_J[]  = [1,2,6];
  param RT3_K[]  = [1,2,6];
  param RT03_I[] = [1,2,6];
  param RT03_J[] = [1,2,6];
  param RT4_I[]  = [1,2,6];
  param RT4_J[]  = [1,2,6];
  param RT4_K[]  = [1,2,6];
  param RT04_I[] = [1,2,6];
  param RT04_J[] = [1,2,6];
  param RT5_I[]  = [1,2,6];
  param RT5_J[]  = [1,2,6];

  param VEC[] = [False,True];

  param CFLAGS[] = ['-O1', '-O2', '-O3'];

  constraint unroll_limit_1  = ((U1_I == 1) or (U1_J == 1));
  constraint unroll_limit_2  = ((U2_I == 1) or (U2_K == 1));
  constraint unroll_limit_3  = ((U3_I == 1) or (U3_J == 1) or (U3_K == 1));
  constraint unroll_limit_03 = ((U03_I == 1) or (U03_J == 1));
  constraint unroll_limit_4  = ((U4_I == 1) or (U4_J == 1) or (U4_K == 1));
  constraint unroll_limit_04 = ((U04_I == 1) or (U04_J == 1));
  constraint unroll_limit_5  = ((U5_I == 1) or (U5_J == 1));

  constraint reg_capacity_1  = (RT1_I*RT1_J <= 150);
  constraint reg_capacity_2  = (RT2_I*RT2_K <= 150);
  constraint reg_capacity_3  = (RT3_I*RT3_J*RT3_K <= 150);
  constraint reg_capacity_03 = (RT03_I*RT03_J <= 150);
  constraint reg_capacity_4  = (RT4_I*RT4_J*RT4_K <= 150);
  constraint reg_capacity_04 = (RT04_I*RT04_J <= 150);
  constraint reg_capacity_5  = (RT5_I*RT5_J <= 150);

 }
 
 def input_params {
    let N = [6];
    let M = [2];
    param n[] = N;
    param m[] = M;
 }
 
 def input_vars {
   decl dynamic double x_hat[n] = random;
   decl dynamic double x_hat_new[n] = 0;
   decl dynamic double A[n*n] = random;
   decl dynamic double Q[n*n] = random;
   decl dynamic double P[n*n] = random;
   decl dynamic double A_T[n*n] = 0;
   decl dynamic double temp_1[n*n] = 0;
   decl dynamic double temp_2[n*n] = 0;
 }
 
 def search {
    arg algorithm = 'Randomsearch';
    arg total_runs  = 100000;
 }

) @*/

  int i, j, k;
  int it, jt, kt;
  int a_row, c_ind, c_row;


/*@ begin Loop ( 

  transform Composite(
    unrolljam = (['i','j'],[U1_I,U1_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT1_I,RT1_J])
  )
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      A_T[n * j + i] = A[n * i + j];
    }
  }


  transform Composite(
    unrolljam = (['i'],[U02_I]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i'],[RT02_I])
  )
  for (i = 0; i <= n-1; i++)
    x_hat_new[i] = 0;

  transform Composite(
    unrolljam = (['i','k'],[U2_I,U2_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','k'],[RT2_I,RT2_K])
  )
  for (i = 0; i <= n-1; i++) {
    for (k = 0; k <= n-1; k++) {
      x_hat_new[i] += A[n * i + k] * x_hat[k];
    }
  }


  transform Composite(
    unrolljam = (['i','j'],[U03_I,U03_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT03_I,RT03_J])
  )
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= n-1; j++)
      temp_1[j + n * i] = 0;

  transform Composite(
    unrolljam = (['i','j','k'],[U3_I,U3_J,U3_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j','k'],[RT3_I,RT3_J,RT3_K])
  )
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_1[j + n * i] += A[n * i + k] * P[n * k + j];
      }
    } 
  }



  transform Composite(
    unrolljam = (['i','j'],[U04_I,U04_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT04_I,RT04_J])
  )
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= n-1; j++)
      temp_2[j + n * i] = 0;

  transform Composite(
    unrolljam = (['i','j','k'],[U4_I,U4_J,U4_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j','k'],[RT4_I,RT4_J,RT4_K])
  )
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_2[j + n * i] += temp_1[n * i + k] * A_T[n * k + j];
      }
    } 
  }

  transform Composite(
    unrolljam = (['i','j'],[U5_I,U5_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT5_I,RT5_J])
  )
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      P[n * i + j] = temp_2[n * i + j] + Q[n * i + j];
    }
  }


) @*/

  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      A_T[n * j + i] = A[n * i + j];
    }
  }

  for (i = 0; i <= n-1; i++) {
    x_hat_new[i] = 0;
    for (k = 0; k <= n-1; k++) {
      x_hat_new[i] += A[n * i + k] * x_hat[k];
    }
  }


  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      temp_1[j + n * i] = 0;
      for (k = 0; k <= n-1; k++) {
        temp_1[j + n * i] += A[n * i + k] * P[n * k + j];
      }
    } 
  }


  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      temp_2[j + n * i] = 0;
      for (k = 0; k <= n-1; k++) {
        temp_2[j + n * i] += temp_1[n * i + k] * A_T[n * k + j];
      }
    } 
  }

  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      P[n * i + j] = temp_2[n * i + j] + Q[n * i + j];
    }
  }
/*@ end @*/
/*@ end @*/


}

