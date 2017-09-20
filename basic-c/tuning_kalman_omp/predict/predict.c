#include "../../kalman_filter.h"

void predict(KALMAN_TYPE* x_hat, int n, int m, KALMAN_TYPE* A, KALMAN_TYPE* Q, KALMAN_TYPE* P, KALMAN_TYPE* x_hat_new, KALMAN_TYPE* A_T, KALMAN_TYPE* temp_1, KALMAN_TYPE* temp_2) {
  

/*@ begin PerfTuning (

 def build {
   arg build_command = 'icc';
   #arg libs = '-lrt';  # Only needed on linux
   arg libs = '-fopenmp';
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


  param VEC[] = [False,True];

  param CFLAGS[] = ['-O1', '-O2', '-O3'];

  constraint unroll_limit_1  = ((U1_I == 1) or (U1_J == 1));
  constraint unroll_limit_2  = ((U2_I == 1) or (U2_K == 1));
  constraint unroll_limit_3  = ((U3_I == 1) or (U3_J == 1) or (U3_K == 1));
  constraint unroll_limit_03 = ((U03_I == 1) or (U03_J == 1));
  constraint unroll_limit_4  = ((U4_I == 1) or (U4_J == 1) or (U4_K == 1));
  constraint unroll_limit_04 = ((U04_I == 1) or (U04_J == 1));
  constraint unroll_limit_5  = ((U5_I == 1) or (U5_J == 1));


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
    arg total_runs  = 1000000;
 }

) @*/

  int i, j, k;
  int it, jt, kt;
  int a_row, c_ind, c_row;


/*@ begin Loop ( 

  transform Composite(
    vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U1_I, parallelize=True)
  for (i = 0; i <= n-1; i++) {
    transform UnrollJam(ufactor=U1_J, parallelize=False)
    for (j = 0; j <= n-1; j++) {
      A_T[n * j + i] = A[n * i + j];
    }
  }


  transform Composite(
    vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U02_I, parallelize=True)
  for (i = 0; i <= n-1; i++)
    x_hat_new[i] = 0;

  transform Composite(
    vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U2_I, parallelize=True)
  for (i = 0; i <= n-1; i++) {
    transform UnrollJam(ufactor=U2_K, parallelize=False)
    for (k = 0; k <= n-1; k++) {
      x_hat_new[i] += A[n * i + k] * x_hat[k];
    }
  }


  transform Composite(
    vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U03_I, parallelize=True)
  for (i = 0; i <= n-1; i++)
    transform UnrollJam(ufactor=U03_J, parallelize=False)
    for (j = 0; j <= n-1; j++)
      temp_1[j + n * i] = 0;

  transform Composite(
    vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U3_I, parallelize=True)
  for (i = 0; i <= n-1; i++) {
    transform UnrollJam(ufactor=U3_J, parallelize=False)
    for (j = 0; j <= n-1; j++) {
      transform UnrollJam(ufactor=U3_K, parallelize=False)
      for (k = 0; k <= n-1; k++) {
        temp_1[j + n * i] += A[n * i + k] * P[n * k + j];
      }
    } 
  }



  transform Composite(
    vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U04_I, parallelize=True)
  for (i = 0; i <= n-1; i++)
    transform UnrollJam(ufactor=U04_J, parallelize=False)
    for (j = 0; j <= n-1; j++)
      temp_2[j + n * i] = 0;

  transform Composite(
    vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U4_I, parallelize=True)
  for (i = 0; i <= n-1; i++) {
    transform UnrollJam(ufactor=U4_J, parallelize=False)
    for (j = 0; j <= n-1; j++) {
      transform UnrollJam(ufactor=U4_K, parallelize=False)
      for (k = 0; k <= n-1; k++) {
        temp_2[j + n * i] += temp_1[n * i + k] * A_T[n * k + j];
      }
    } 
  }

  transform Composite(
    vector = (VEC, ['ivdep','vector always'])
  )
  transform UnrollJam(ufactor=U5_I, parallelize=True)
  for (i = 0; i <= n-1; i++) {
    transform UnrollJam(ufactor=U5_J, parallelize=False)
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

