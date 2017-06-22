/*
RT1_K:1
RT1_J:1
RT1_I:1
RT2_I:1
RT2_J:1
U_K:1
U_J:1
U_I:2
U_I2:2
U_J2:1
VEC:False
CFLAGS:-O0
U_K2:1
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define n 6
double *mat_a;
double *L;
double *U;
double *P;
void malloc_arrays() {
  int i1;
  mat_a = (double*) malloc((n *n) * sizeof(double));
  L = (double*) malloc((n *n) * sizeof(double));
  U = (double*) malloc((n *n) * sizeof(double));
  P = (double*) malloc((n *n) * sizeof(double));
}
double orio_t_start, orio_t_end, orio_t = (double)LONG_MAX;

void init_input_vars() {
  int i1;
  for (i1=0; i1<n *n; i1++)
   mat_a[i1] = (i1) % 5 + 1;
  for (i1=0; i1<n *n; i1++)
   L[i1] = 0;
  for (i1=0; i1<n *n; i1++)
   U[i1] = 0;
  for (i1=0; i1<n *n; i1++)
   P[i1] = 0;
}





extern double getClock(); 

int main(int argc, char *argv[]) {
  
#ifdef MAIN_DECLARATIONS
  MAIN_DECLARATIONS()
#endif  
  malloc_arrays();
  init_input_vars();


  int orio_i;

  /*
   Coordinate: [1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0] 
  */
  
  
  for (orio_i=0; orio_i<ORIO_REPS; orio_i++) {
    orio_t_start = getClock();
    
    


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
    unrolljam = (['i2','j2'],[U_I2,U_J2]),
    regtile = (['i2','j2'],[RT2_I,RT2_J])
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
    unrolljam = (['i2','j2'],[U_I2,U_J2]),
    regtile = (['i2','j2'],[RT2_I,RT2_J])
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

    transform Composite(
      unrolljam = (['i','j'],[U_I,U_J]),
      regtile = (['i','j'],[RT1_I,RT1_J]),
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
    for (i2=0; i2<=n-2; i2=i2+2) {
      for (j2=0; j2<=n-1; j2++ ) {
        if (i2==j2) 
          P[n*i2+j2]=1;
        else 
          P[n*i2+j2]=0;
        if ((i2+1)==j2) 
          P[n*(i2+1)+j2]=1;
        else 
          P[n*(i2+1)+j2]=0;
      }
    }
    for (i2=n-((n-(0))%2); i2<=n-1; i2=i2+1) 
      for (j2=0; j2<=n-1; j2++ ) {
        if (i2==j2) 
          P[n*i2+j2]=1;
        else 
          P[n*i2+j2]=0;
      }
  }
  {
    int i2;
    for (i2=0; i2<=n-2; i2=i2+2) {
      for (j2=0; j2<=n-1; j2++ ) {
        if (i2==j2) 
          L[n*i2+j2]=1;
        else 
          L[n*i2+j2]=0;
        if ((i2+1)==j2) 
          L[n*(i2+1)+j2]=1;
        else 
          L[n*(i2+1)+j2]=0;
      }
    }
    for (i2=n-((n-(0))%2); i2<=n-1; i2=i2+1) 
      for (j2=0; j2<=n-1; j2++ ) {
        if (i2==j2) 
          L[n*i2+j2]=1;
        else 
          L[n*i2+j2]=0;
      }
  }
  {
    int i2;
    for (i2=0; i2<=size_a-2; i2=i2+2) {
      U[i2]=mat_a[i2];
      U[(i2+1)]=mat_a[(i2+1)];
    }
    for (i2=size_a-((size_a-(0))%2); i2<=size_a-1; i2=i2+1) 
      U[i2]=mat_a[i2];
  }
  for (i=0; i<=n-1; i++ ) {
    if (U[i*n+i]>0) 
      max_a=U[i*n+i];
    else 
      max_a=0-U[i*n+i];
    ind_max=i;
    for (j=i+1; j<=n-1; j++ ) {
      if (U[j*n+i]>0) 
        abs_a=U[j*n+i];
      else 
        abs_a=0-U[j*n+i];
      if (abs_a>max_a) {
        max_a=abs_a;
        ind_max=j;
      }
    }
    if (max_a<=tolerance) {
      cnt_pivots=0-1;
      break;
    }
    cnt_pivots++ ;
    for (k=0; k<=n-1; k++ ) {
      scalar_1=P[i*n+k];
      P[i*n+k]=P[ind_max*n+k];
      P[ind_max*n+k]=scalar_1;
      scalar_2=U[i*n+k];
      U[i*n+k]=U[ind_max*n+k];
      U[ind_max*n+k]=scalar_2;
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


    
    orio_t_end = getClock();
    orio_t = orio_t_end - orio_t_start;
    printf("{'[1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0]' : %g}\n", orio_t);
    
    if (orio_i==0) {
      
    }
  }
  
  
  
  return 0;
}
