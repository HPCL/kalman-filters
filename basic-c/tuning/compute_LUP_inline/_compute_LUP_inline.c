#include "../../linear_algebra.h"


int compute_LUP(KALMAN_TYPE* mat_a, KALMAN_TYPE* L, KALMAN_TYPE* U, KALMAN_TYPE* P, int n) {
  
#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  /*@ begin PerfTuning (

    def build {
      arg build_command = 'icc';
      #arg libs = '-lrt';  # Only needed on linux
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

      param RT1_I[] = [1,2,6];
      param RT1_J[] = [1,2,6];
      param RT1_K[] = [1,2,6];

      param RT2_I[] = [1,2,6];

      param RT3_I[] = [1,2,6];
      param RT3_J[] = [1,2,6];

      param RT4_I[] = [1,2,6];
      param RT4_J[] = [1,2,6];

      param RT5_I[] = [1,2,6];
      param RT5_J[] = [1,2,6];

      param VEC[] = [False,True];

      param CFLAGS[] = ['-O1', '-O2', '-O3'];

      constraint unroll_limit = ((U_I == 1) or (U_J == 1));
      constraint unroll_limit_3 = ((U_I3 == 1) or (U_J3 == 1));
      constraint unroll_limit_5 = ((U_I5 == 1) or (U_J5 == 1));

      constraint reg_capacity_1 = (RT1_I*RT1_J*RT1_K <= 150);
      constraint reg_capacity_3 = (RT3_I*RT3_J <= 150);
      constraint reg_capacity_5 = (RT5_I*RT5_J <= 150);

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
/**-- (Generated by Orio) 
Best performance cost: 
  [2.302e-06, 1.07e-06, 8.6e-07, 8.16e-07, 8.11e-07, 8.07e-07, 8.07e-07, 8e-07, 8.2e-07, 8.17e-07, 7.98e-07, 8.03e-07, 8.12e-07, 7.99e-07, 8.13e-07, 7.99e-07, 8.1e-07, 8.07e-07, 8.07e-07, 8.09e-07, 8.1e-07, 8.13e-07, 8.33e-07, 8.11e-07, 8e-07, 8.07e-07, 8.02e-07, 8e-07, 8.04e-07, 8.07e-07, 8.03e-07, 8.08e-07, 8.14e-07, 7.99e-07, 8.09e-07, 8.02e-07, 7.95e-07, 8.05e-07, 8.07e-07, 8.1e-07, 8.05e-07, 8.05e-07, 7.98e-07, 8.06e-07, 8.02e-07, 8.07e-07, 8.02e-07, 7.96e-07, 8.04e-07, 8.07e-07] 
Tuned for specific problem sizes: 
  n = 6 
Best performance parameters: 
  CFLAGS = -O3 
  RT1_I = 1 
  RT1_J = 1 
  RT1_K = 6 
  RT2_I = 2 
  RT3_I = 1 
  RT3_J = 2 
  RT4_I = 6 
  RT4_J = 2 
  RT5_I = 6 
  RT5_J = 1 
  U_I = 1 
  U_I2 = 4 
  U_I3 = 3 
  U_I5 = 5 
  U_J = 4 
  U_J3 = 1 
  U_J5 = 1 
  U_K = 4 
  VEC = False 
--**/



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
    unrolljam = (['i2','j2'],[U_I3,U_J3]),
    regtile = (['i2','j2'],[RT3_I,RT3_J])
  )
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

  transform Composite(
    unrolljam = (['i2'],[U_I2]),
    regtile = (['i2'],[RT2_I])
  )
  for (i2 = 0; i2 <= size_a-1; i2++) {
    U[i2] = mat_a[i2];
  }



  for (i = 0; i <= n-1; i++) {
    if(U[i * n + i] > 0) max_a = U[i * n + i]; 
    else max_a = 0 - U[i * n + i];
    ind_max = i;

    transform Composite(
      unrolljam = (['j'],[U_J]),
      regtile = (['j'],[RT1_J])
    )
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
        unrolljam = (['k'],[U_K]),
        regtile = (['k'],[RT1_K])
      )
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
      unrolljam = (['i','j'],[U_I5,U_J5]),
      regtile = (['i','j'],[RT5_I,RT5_J]),
      vector = (VEC, ['ivdep','vector always'])
    )
    for(j = i+1; j <= n-1; j++) {
      coeff = (U[j * n+i]/U[i * n+i]);
      L[j * n+i] = coeff;
      for (k = i; k <= n-1; k++) {
        U[j * n + k] -= coeff * U[i * n + k];
      }
    }

  } //end main for



) @*/
  {
    int i2;
    for (i2=0; i2<=n-3; i2=i2+3) {
      for (j2t=0; j2t<=n-2; j2t=j2t+2) {
        if (i2==j2t) {
          P[n*i2+j2t]=1;
          L[n*i2+j2t]=1;
        } else {
          P[n*i2+j2t]=0;
          L[n*i2+j2t]=0;
        }
        if (i2==(j2t+1)) {
          P[n*i2+j2t+1]=1;
          L[n*i2+j2t+1]=1;
        } else {
          P[n*i2+j2t+1]=0;
          L[n*i2+j2t+1]=0;
        }
        if ((i2+1)==j2t) {
          P[n*(i2+1)+j2t]=1;
          L[n*(i2+1)+j2t]=1;
        } else {
          P[n*(i2+1)+j2t]=0;
          L[n*(i2+1)+j2t]=0;
        }
        if ((i2+1)==(j2t+1)) {
          P[n*(i2+1)+j2t+1]=1;
          L[n*(i2+1)+j2t+1]=1;
        } else {
          P[n*(i2+1)+j2t+1]=0;
          L[n*(i2+1)+j2t+1]=0;
        }
        if ((i2+2)==j2t) {
          P[n*(i2+2)+j2t]=1;
          L[n*(i2+2)+j2t]=1;
        } else {
          P[n*(i2+2)+j2t]=0;
          L[n*(i2+2)+j2t]=0;
        }
        if ((i2+2)==(j2t+1)) {
          P[n*(i2+2)+j2t+1]=1;
          L[n*(i2+2)+j2t+1]=1;
        } else {
          P[n*(i2+2)+j2t+1]=0;
          L[n*(i2+2)+j2t+1]=0;
        }
      }
      for (j2=j2t; j2<=n-1; j2=j2+1) {
        if (i2==j2) {
          P[n*i2+j2]=1;
          L[n*i2+j2]=1;
        } else {
          P[n*i2+j2]=0;
          L[n*i2+j2]=0;
        }
        if ((i2+1)==j2) {
          P[n*(i2+1)+j2]=1;
          L[n*(i2+1)+j2]=1;
        } else {
          P[n*(i2+1)+j2]=0;
          L[n*(i2+1)+j2]=0;
        }
        if ((i2+2)==j2) {
          P[n*(i2+2)+j2]=1;
          L[n*(i2+2)+j2]=1;
        } else {
          P[n*(i2+2)+j2]=0;
          L[n*(i2+2)+j2]=0;
        }
      }
    }
    for (i2=n-((n-(0))%3); i2<=n-1; i2=i2+1) {
      for (j2t=0; j2t<=n-2; j2t=j2t+2) {
        if (i2==j2t) {
          P[n*i2+j2t]=1;
          L[n*i2+j2t]=1;
        } else {
          P[n*i2+j2t]=0;
          L[n*i2+j2t]=0;
        }
        if (i2==(j2t+1)) {
          P[n*i2+(j2t+1)]=1;
          L[n*i2+(j2t+1)]=1;
        } else {
          P[n*i2+(j2t+1)]=0;
          L[n*i2+(j2t+1)]=0;
        }
      }
      for (j2=j2t; j2<=n-1; j2=j2+1) {
        if (i2==j2) {
          P[n*i2+j2]=1;
          L[n*i2+j2]=1;
        } else {
          P[n*i2+j2]=0;
          L[n*i2+j2]=0;
        }
      }
    }
  }
  {
    for (i2t=0; i2t<=size_a-2; i2t=i2t+2) {
      U[i2t]=mat_a[i2t];
      U[(i2t+1)]=mat_a[(i2t+1)];
    }
    {
      int i2;
      for (i2=i2t; i2<=size_a-4; i2=i2+4) {
        U[i2]=mat_a[i2];
        U[(i2+1)]=mat_a[(i2+1)];
        U[(i2+2)]=mat_a[(i2+2)];
        U[(i2+3)]=mat_a[(i2+3)];
      }
      for (i2=size_a-((size_a-(i2t))%4); i2<=size_a-1; i2=i2+1) 
        U[i2]=mat_a[i2];
    }
  }
  for (i=0; i<=n-1; i++ ) {
    if (U[i*n+i]>0) 
      max_a=U[i*n+i];
    else 
      max_a=0-U[i*n+i];
    ind_max=i;
    {
      int j;
      for (j=i+1; j<=n-4; j=j+4) {
        if (U[j*n+i]>0) 
          abs_a=U[j*n+i];
        else 
          abs_a=-U[j*n+i];
        if (abs_a>max_a) {
          max_a=abs_a;
          ind_max=j;
        }
        if (U[(j+1)*n+i]>0) 
          abs_a=U[(j+1)*n+i];
        else 
          abs_a=-U[(j+1)*n+i];
        if (abs_a>max_a) {
          max_a=abs_a;
          ind_max=(j+1);
        }
        if (U[(j+2)*n+i]>0) 
          abs_a=U[(j+2)*n+i];
        else 
          abs_a=-U[(j+2)*n+i];
        if (abs_a>max_a) {
          max_a=abs_a;
          ind_max=(j+2);
        }
        if (U[(j+3)*n+i]>0) 
          abs_a=U[(j+3)*n+i];
        else 
          abs_a=-U[(j+3)*n+i];
        if (abs_a>max_a) {
          max_a=abs_a;
          ind_max=(j+3);
        }
      }
      for (j=n-((n-i-1)%4); j<=n-1; j=j+1) {
        if (U[j*n+i]>0) 
          abs_a=U[j*n+i];
        else 
          abs_a=0-U[j*n+i];
        if (abs_a>max_a) {
          max_a=abs_a;
          ind_max=j;
        }
      }
    }
    if (max_a<=tolerance) {
      cnt_pivots=0-1;
      break;
    }
    if (ind_max==i) {
    } else {
      cnt_pivots++ ;
      {
        for (kt=0; kt<=n-6; kt=kt+6) {
          scalar_1=P[i*n+kt];
          P[i*n+kt]=P[ind_max*n+kt];
          P[ind_max*n+kt]=scalar_1;
          scalar_2=U[i*n+kt];
          U[i*n+kt]=U[ind_max*n+kt];
          U[ind_max*n+kt]=scalar_2;
          scalar_1=P[i*n+(kt+1)];
          P[i*n+(kt+1)]=P[ind_max*n+(kt+1)];
          P[ind_max*n+(kt+1)]=scalar_1;
          scalar_2=U[i*n+(kt+1)];
          U[i*n+(kt+1)]=U[ind_max*n+(kt+1)];
          U[ind_max*n+(kt+1)]=scalar_2;
          scalar_1=P[i*n+(kt+2)];
          P[i*n+(kt+2)]=P[ind_max*n+(kt+2)];
          P[ind_max*n+(kt+2)]=scalar_1;
          scalar_2=U[i*n+(kt+2)];
          U[i*n+(kt+2)]=U[ind_max*n+(kt+2)];
          U[ind_max*n+(kt+2)]=scalar_2;
          scalar_1=P[i*n+(kt+3)];
          P[i*n+(kt+3)]=P[ind_max*n+(kt+3)];
          P[ind_max*n+(kt+3)]=scalar_1;
          scalar_2=U[i*n+(kt+3)];
          U[i*n+(kt+3)]=U[ind_max*n+(kt+3)];
          U[ind_max*n+(kt+3)]=scalar_2;
          scalar_1=P[i*n+(kt+4)];
          P[i*n+(kt+4)]=P[ind_max*n+(kt+4)];
          P[ind_max*n+(kt+4)]=scalar_1;
          scalar_2=U[i*n+(kt+4)];
          U[i*n+(kt+4)]=U[ind_max*n+(kt+4)];
          U[ind_max*n+(kt+4)]=scalar_2;
          scalar_1=P[i*n+(kt+5)];
          P[i*n+(kt+5)]=P[ind_max*n+(kt+5)];
          P[ind_max*n+(kt+5)]=scalar_1;
          scalar_2=U[i*n+(kt+5)];
          U[i*n+(kt+5)]=U[ind_max*n+(kt+5)];
          U[ind_max*n+(kt+5)]=scalar_2;
        }
        {
          int k;
          for (k=kt; k<=n-4; k=k+4) {
            scalar_1=P[i*n+k];
            P[i*n+k]=P[ind_max*n+k];
            P[ind_max*n+k]=scalar_1;
            scalar_2=U[i*n+k];
            U[i*n+k]=U[ind_max*n+k];
            U[ind_max*n+k]=scalar_2;
            scalar_1=P[i*n+k+1];
            P[i*n+k+1]=P[ind_max*n+k+1];
            P[ind_max*n+k+1]=scalar_1;
            scalar_2=U[i*n+k+1];
            U[i*n+k+1]=U[ind_max*n+k+1];
            U[ind_max*n+k+1]=scalar_2;
            scalar_1=P[i*n+k+2];
            P[i*n+k+2]=P[ind_max*n+k+2];
            P[ind_max*n+k+2]=scalar_1;
            scalar_2=U[i*n+k+2];
            U[i*n+k+2]=U[ind_max*n+k+2];
            U[ind_max*n+k+2]=scalar_2;
            scalar_1=P[i*n+k+3];
            P[i*n+k+3]=P[ind_max*n+k+3];
            P[ind_max*n+k+3]=scalar_1;
            scalar_2=U[i*n+k+3];
            U[i*n+k+3]=U[ind_max*n+k+3];
            U[ind_max*n+k+3]=scalar_2;
          }
          for (k=n-((n-(kt))%4); k<=n-1; k=k+1) {
            scalar_1=P[i*n+k];
            P[i*n+k]=P[ind_max*n+k];
            P[ind_max*n+k]=scalar_1;
            scalar_2=U[i*n+k];
            U[i*n+k]=U[ind_max*n+k];
            U[ind_max*n+k]=scalar_2;
          }
        }
      }
    }
    for (j=i+1; j<=n-1; j++ ) {
      coeff=(U[j*n+i]/U[i*n+i]);
      L[j*n+i]=coeff;
      for (k=i; k<=n-1; k++ ) {
        U[j*n+k]=U[j*n+k]-coeff*U[i*n+k];
      }
    }
  }
  /*//end main for*/
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
