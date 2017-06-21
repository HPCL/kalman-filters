/*
U_K:21
U_J:1
U_I:18
U_I2:12
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

#define n 10
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
   Coordinate: [17, 0, 20, 11, 0, 0, 0, 0] 
  */
  
  
  for (orio_i=0; orio_i<ORIO_REPS; orio_i++) {
    orio_t_start = getClock();
    
    


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



  for (i = 0; i <= n-1; i++) {
    if(U[i * n + i] > 0) max_a = U[i * n + i]; 
    else max_a = 0 - U[i * n + i];
    ind_max = i;

    transform Composite(
      unrolljam = (['j'],[U_J])
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
      unrolljam = (['k'],[U_K])
    )
    for (k = 0; k <= n-1; k++)
      temp_row[k] = P[i * n+k];
    for (k = 0; k <= n-1; k++)
      P[i * n+k] = P[ind_max * n+k];
    for (k = 0; k <= n-1; k++)
      P[ind_max * n+k] = temp_row[k];


    transform Composite(
      unrolljam = (['k'],[U_K])
    )
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
  {
    int i2;
    for (i2=0; i2<=n-12; i2=i2+12) {
      for (j2=0; j2<=n-1; j2++ ) {
        if (i2==j2) 
          P[n*i2+j2]=1;
        else 
          P[n*i2+j2]=0;
        if ((i2+1)==j2) 
          P[n*(i2+1)+j2]=1;
        else 
          P[n*(i2+1)+j2]=0;
        if ((i2+2)==j2) 
          P[n*(i2+2)+j2]=1;
        else 
          P[n*(i2+2)+j2]=0;
        if ((i2+3)==j2) 
          P[n*(i2+3)+j2]=1;
        else 
          P[n*(i2+3)+j2]=0;
        if ((i2+4)==j2) 
          P[n*(i2+4)+j2]=1;
        else 
          P[n*(i2+4)+j2]=0;
        if ((i2+5)==j2) 
          P[n*(i2+5)+j2]=1;
        else 
          P[n*(i2+5)+j2]=0;
        if ((i2+6)==j2) 
          P[n*(i2+6)+j2]=1;
        else 
          P[n*(i2+6)+j2]=0;
        if ((i2+7)==j2) 
          P[n*(i2+7)+j2]=1;
        else 
          P[n*(i2+7)+j2]=0;
        if ((i2+8)==j2) 
          P[n*(i2+8)+j2]=1;
        else 
          P[n*(i2+8)+j2]=0;
        if ((i2+9)==j2) 
          P[n*(i2+9)+j2]=1;
        else 
          P[n*(i2+9)+j2]=0;
        if ((i2+10)==j2) 
          P[n*(i2+10)+j2]=1;
        else 
          P[n*(i2+10)+j2]=0;
        if ((i2+11)==j2) 
          P[n*(i2+11)+j2]=1;
        else 
          P[n*(i2+11)+j2]=0;
      }
    }
    for (i2=n-((n-(0))%12); i2<=n-1; i2=i2+1) 
      for (j2=0; j2<=n-1; j2++ ) {
        if (i2==j2) 
          P[n*i2+j2]=1;
        else 
          P[n*i2+j2]=0;
      }
  }
  {
    int i2;
    for (i2=0; i2<=n-12; i2=i2+12) {
      for (j2=0; j2<=n-1; j2++ ) {
        if (i2==j2) 
          L[n*i2+j2]=1;
        else 
          L[n*i2+j2]=0;
        if ((i2+1)==j2) 
          L[n*(i2+1)+j2]=1;
        else 
          L[n*(i2+1)+j2]=0;
        if ((i2+2)==j2) 
          L[n*(i2+2)+j2]=1;
        else 
          L[n*(i2+2)+j2]=0;
        if ((i2+3)==j2) 
          L[n*(i2+3)+j2]=1;
        else 
          L[n*(i2+3)+j2]=0;
        if ((i2+4)==j2) 
          L[n*(i2+4)+j2]=1;
        else 
          L[n*(i2+4)+j2]=0;
        if ((i2+5)==j2) 
          L[n*(i2+5)+j2]=1;
        else 
          L[n*(i2+5)+j2]=0;
        if ((i2+6)==j2) 
          L[n*(i2+6)+j2]=1;
        else 
          L[n*(i2+6)+j2]=0;
        if ((i2+7)==j2) 
          L[n*(i2+7)+j2]=1;
        else 
          L[n*(i2+7)+j2]=0;
        if ((i2+8)==j2) 
          L[n*(i2+8)+j2]=1;
        else 
          L[n*(i2+8)+j2]=0;
        if ((i2+9)==j2) 
          L[n*(i2+9)+j2]=1;
        else 
          L[n*(i2+9)+j2]=0;
        if ((i2+10)==j2) 
          L[n*(i2+10)+j2]=1;
        else 
          L[n*(i2+10)+j2]=0;
        if ((i2+11)==j2) 
          L[n*(i2+11)+j2]=1;
        else 
          L[n*(i2+11)+j2]=0;
      }
    }
    for (i2=n-((n-(0))%12); i2<=n-1; i2=i2+1) 
      for (j2=0; j2<=n-1; j2++ ) {
        if (i2==j2) 
          L[n*i2+j2]=1;
        else 
          L[n*i2+j2]=0;
      }
  }
  {
    int i2;
    for (i2=0; i2<=size_a-12; i2=i2+12) {
      U[i2]=mat_a[i2];
      U[(i2+1)]=mat_a[(i2+1)];
      U[(i2+2)]=mat_a[(i2+2)];
      U[(i2+3)]=mat_a[(i2+3)];
      U[(i2+4)]=mat_a[(i2+4)];
      U[(i2+5)]=mat_a[(i2+5)];
      U[(i2+6)]=mat_a[(i2+6)];
      U[(i2+7)]=mat_a[(i2+7)];
      U[(i2+8)]=mat_a[(i2+8)];
      U[(i2+9)]=mat_a[(i2+9)];
      U[(i2+10)]=mat_a[(i2+10)];
      U[(i2+11)]=mat_a[(i2+11)];
    }
    for (i2=size_a-((size_a-(0))%12); i2<=size_a-1; i2=i2+1) 
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
    {
      int k;
      for (k=0; k<=n-21; k=k+21) {
        temp_row[k]=P[i*n+k];
        temp_row[(k+1)]=P[i*n+k+1];
        temp_row[(k+2)]=P[i*n+k+2];
        temp_row[(k+3)]=P[i*n+k+3];
        temp_row[(k+4)]=P[i*n+k+4];
        temp_row[(k+5)]=P[i*n+k+5];
        temp_row[(k+6)]=P[i*n+k+6];
        temp_row[(k+7)]=P[i*n+k+7];
        temp_row[(k+8)]=P[i*n+k+8];
        temp_row[(k+9)]=P[i*n+k+9];
        temp_row[(k+10)]=P[i*n+k+10];
        temp_row[(k+11)]=P[i*n+k+11];
        temp_row[(k+12)]=P[i*n+k+12];
        temp_row[(k+13)]=P[i*n+k+13];
        temp_row[(k+14)]=P[i*n+k+14];
        temp_row[(k+15)]=P[i*n+k+15];
        temp_row[(k+16)]=P[i*n+k+16];
        temp_row[(k+17)]=P[i*n+k+17];
        temp_row[(k+18)]=P[i*n+k+18];
        temp_row[(k+19)]=P[i*n+k+19];
        temp_row[(k+20)]=P[i*n+k+20];
      }
      for (k=n-((n-(0))%21); k<=n-1; k=k+1) 
        temp_row[k]=P[i*n+k];
    }
    for (k=0; k<=n-1; k++ ) 
      P[i*n+k]=P[ind_max*n+k];
    for (k=0; k<=n-1; k++ ) 
      P[ind_max*n+k]=temp_row[k];
    {
      int k;
      for (k=0; k<=n-21; k=k+21) {
        temp_row[k]=U[i*n+k];
        temp_row[(k+1)]=U[i*n+k+1];
        temp_row[(k+2)]=U[i*n+k+2];
        temp_row[(k+3)]=U[i*n+k+3];
        temp_row[(k+4)]=U[i*n+k+4];
        temp_row[(k+5)]=U[i*n+k+5];
        temp_row[(k+6)]=U[i*n+k+6];
        temp_row[(k+7)]=U[i*n+k+7];
        temp_row[(k+8)]=U[i*n+k+8];
        temp_row[(k+9)]=U[i*n+k+9];
        temp_row[(k+10)]=U[i*n+k+10];
        temp_row[(k+11)]=U[i*n+k+11];
        temp_row[(k+12)]=U[i*n+k+12];
        temp_row[(k+13)]=U[i*n+k+13];
        temp_row[(k+14)]=U[i*n+k+14];
        temp_row[(k+15)]=U[i*n+k+15];
        temp_row[(k+16)]=U[i*n+k+16];
        temp_row[(k+17)]=U[i*n+k+17];
        temp_row[(k+18)]=U[i*n+k+18];
        temp_row[(k+19)]=U[i*n+k+19];
        temp_row[(k+20)]=U[i*n+k+20];
      }
      for (k=n-((n-(0))%21); k<=n-1; k=k+1) 
        temp_row[k]=U[i*n+k];
    }
    for (k=0; k<=n-1; k++ ) 
      U[i*n+k]=U[ind_max*n+k];
    for (k=0; k<=n-1; k++ ) 
      U[ind_max*n+k]=temp_row[k];
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
    printf("{'[17, 0, 20, 11, 0, 0, 0, 0]' : %g}\n", orio_t);
    
    if (orio_i==0) {
      
    }
  }
  
  
  
  return 0;
}
