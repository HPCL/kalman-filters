/*
U_K:1
U_J:1
U_I:1
VEC:False
CFLAGS:-O0
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define n 100
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
   Coordinate: [0, 0, 0, 0, 0] 
  */
  
  
  for (orio_i=0; orio_i<ORIO_REPS; orio_i++) {
    orio_t_start = getClock();
    
    


  int i, j, k, ind_max, curr_row, next_row, row;

  int ii, jj, kk;
  int iii, jjj, kkk;

  int cnt_pivots = 0;
  int size_a;
  double tolerance = 5E-300;
  double max_a, abs_a, coeff;
  double temp_row[n];


  /*@ begin Loop (  

  size_a = n*n;

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
    unrolljam = (['i','j','k'],[U_I,U_J,U_K])
  )
  for(i = 0; i <= n-1; i++) {
    curr_row = i * n;
    max_a = (((U[curr_row + i] < 0) * -2) + 1) * U[curr_row + i];
    ind_max = i;

    for (j = i+1; j <= n-1; j++) {
      abs_a = (((U[j * n + i] < 0) * -2) + 1) * U[j * n + i];
      if (abs_a > max_a) {
        max_a = abs_a;
        ind_max = j;
      }
    }
    
    if (max_a <= tolerance)
      return -1;


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



  return cnt_pivots;

) @*/
  size_a=n*n;
  for (i=0; i<=n-1; i++ ) {
    row=n*i;
    for (j=0; j<=n-1; j++ ) {
      if (i==j) 
        P[row+j]=1;
      else 
        P[row+j]=0;
    }
  }
  for (i=0; i<=n-1; i++ ) {
    row=n*i;
    for (j=0; j<=n-1; j++ ) {
      if (i==j) 
        L[row+j]=1;
      else 
        L[row+j]=0;
    }
  }
  for (i=0; i<=size_a-1; i++ ) 
    U[i]=mat_a[i];
  for (i=0; i<=n-1; i++ ) {
    curr_row=i*n;
    max_a=(((U[curr_row+i]<0)*-2)+1)*U[curr_row+i];
    ind_max=i;
    for (j=i+1; j<=n-1; j++ ) {
      abs_a=(((U[j*n+i]<0)*-2)+1)*U[j*n+i];
      if (abs_a>max_a) {
        max_a=abs_a;
        ind_max=j;
      }
    }
    if (max_a<=tolerance) 
      return-1;
    cnt_pivots++ ;
    ind_max=ind_max*n;
    for (k=0; k<=n-1; k++ ) 
      temp_row[k]=P[curr_row+k];
    for (k=0; k<=n-1; k++ ) 
      P[curr_row+k]=P[ind_max+k];
    for (k=0; k<=n-1; k++ ) 
      P[ind_max+k]=temp_row[k];
    for (k=0; k<=n-1; k++ ) 
      temp_row[k]=U[curr_row+k];
    for (k=0; k<=n-1; k++ ) 
      U[curr_row+k]=U[ind_max+k];
    for (k=0; k<=n-1; k++ ) 
      U[ind_max+k]=temp_row[k];
    for (j=i+1; j<=n-1; j++ ) {
      next_row=j*n;
      coeff=(U[next_row+i]/U[curr_row+i]);
      L[next_row+i]=coeff;
      for (k=i; k<=n-1; k++ ) {
        U[next_row+k]=U[next_row+k]-coeff*U[curr_row+k];
      }
    }
  }
  /*//end main for*/
    return cnt_pivots;
;
/*@ end @*/


    
    orio_t_end = getClock();
    orio_t = orio_t_end - orio_t_start;
    printf("{'[0, 0, 0, 0, 0]' : %g}\n", orio_t);
    
    if (orio_i==0) {
      
    }
  }
  
  
  
  return 0;
}
