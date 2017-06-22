/*
RT1_K:1
RT1_J:1
RT1_I:1
U_K:4
U_J:2
U_I:1
VEC:False
CFLAGS:-O0
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define rows_a 6
#define cols_a 6
#define cols_b 6
double *mat_a;
double *mat_b;
double *mat_c;
void malloc_arrays() {
  int i1;
  mat_a = (double*) malloc((rows_a *cols_a) * sizeof(double));
  mat_b = (double*) malloc((cols_b *cols_b) * sizeof(double));
  mat_c = (double*) malloc((rows_a *cols_b) * sizeof(double));
}
double orio_t_start, orio_t_end, orio_t = (double)LONG_MAX;

void init_input_vars() {
  int i1;
  for (i1=0; i1<rows_a *cols_a; i1++)
   mat_a[i1] = (i1) % 5 + 1;
  for (i1=0; i1<cols_b *cols_b; i1++)
   mat_b[i1] = (i1) % 5 + 1;
  for (i1=0; i1<rows_a *cols_b; i1++)
   mat_c[i1] = 0;
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
   Coordinate: [0, 1, 3, 0, 0, 0, 0, 0] 
  */
  
  
  for (orio_i=0; orio_i<ORIO_REPS; orio_i++) {
    orio_t_start = getClock();
    
    

  int i, j, k;  
  int it,jt, kt;
  int c_ind, a_row, c_row;


  /*@ begin Loop (  
    transform Composite(
      unrolljam = (['i','j','k'],[U_I,U_J,U_K]),
      vector = (VEC, ['ivdep','vector always']),
      regtile = (['i','j','k'],[RT1_I,RT1_J,RT1_K])
    )
    for (i = 0; i <= rows_a-1; i++) {
      for (j = 0; j <= cols_b-1; j++) {
        mat_c[j + cols_b * i] = 0;
        for (k = 0; k <= cols_a-1; k++) {
          mat_c[j + cols_b * i] += mat_a[cols_a * i + k] * mat_b[cols_b * k + j];
        }
      } 
    }
  ) @*/
  for (i=0; i<=rows_a-1; i++ ) {
    {
      int j;
      for (j=0; j<=cols_b-2; j=j+2) {
        mat_c[j+cols_b*i]=0;
        {
          int k;
          for (k=0; k<=cols_a-4; k=k+4) {
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k]*mat_b[cols_b*k+j];
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k+1]*mat_b[cols_b*(k+1)+j];
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k+2]*mat_b[cols_b*(k+2)+j];
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k+3]*mat_b[cols_b*(k+3)+j];
          }
          for (k=cols_a-((cols_a-(0))%4); k<=cols_a-1; k=k+1) 
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k]*mat_b[cols_b*k+j];
        }
        mat_c[j+cols_b*i+1]=0;
        {
          int k;
          for (k=0; k<=cols_a-4; k=k+4) {
            mat_c[j+cols_b*i+1]=mat_c[j+cols_b*i+1]+mat_a[cols_a*i+k]*mat_b[cols_b*k+j+1];
            mat_c[j+cols_b*i+1]=mat_c[j+cols_b*i+1]+mat_a[cols_a*i+k+1]*mat_b[cols_b*(k+1)+j+1];
            mat_c[j+cols_b*i+1]=mat_c[j+cols_b*i+1]+mat_a[cols_a*i+k+2]*mat_b[cols_b*(k+2)+j+1];
            mat_c[j+cols_b*i+1]=mat_c[j+cols_b*i+1]+mat_a[cols_a*i+k+3]*mat_b[cols_b*(k+3)+j+1];
          }
          for (k=cols_a-((cols_a-(0))%4); k<=cols_a-1; k=k+1) 
            mat_c[j+cols_b*i+1]=mat_c[j+cols_b*i+1]+mat_a[cols_a*i+k]*mat_b[cols_b*k+j+1];
        }
      }
      for (j=cols_b-((cols_b-(0))%2); j<=cols_b-1; j=j+1) {
        mat_c[j+cols_b*i]=0;
        {
          int k;
          for (k=0; k<=cols_a-4; k=k+4) {
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k]*mat_b[cols_b*k+j];
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k+1]*mat_b[cols_b*(k+1)+j];
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k+2]*mat_b[cols_b*(k+2)+j];
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k+3]*mat_b[cols_b*(k+3)+j];
          }
          for (k=cols_a-((cols_a-(0))%4); k<=cols_a-1; k=k+1) 
            mat_c[j+cols_b*i]=mat_c[j+cols_b*i]+mat_a[cols_a*i+k]*mat_b[cols_b*k+j];
        }
      }
    }
  }
/*@ end @*/


    
    orio_t_end = getClock();
    orio_t = orio_t_end - orio_t_start;
    printf("{'[0, 1, 3, 0, 0, 0, 0, 0]' : %g}\n", orio_t);
    
    if (orio_i==0) {
      
    }
  }
  
  
  
  return 0;
}
