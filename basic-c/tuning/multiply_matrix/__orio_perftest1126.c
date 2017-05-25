/*
U_K:5
U_J:20
U_I:1
VEC:False
CFLAGS:-O0
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define rows 100
#define cols 100
double *mat_a;
double *mat_b;
double *mat_c;
void malloc_arrays() {
  int i1;
  mat_a = (double*) malloc((rows *cols) * sizeof(double));
  mat_b = (double*) malloc((rows *cols) * sizeof(double));
  mat_c = (double*) malloc((rows *cols) * sizeof(double));
}
double orio_t_start, orio_t_end, orio_t = (double)LONG_MAX;

void init_input_vars() {
  int i1;
  for (i1=0; i1<rows *cols; i1++)
   mat_a[i1] = (i1) % 5 + 1;
  for (i1=0; i1<rows *cols; i1++)
   mat_b[i1] = (i1) % 5 + 1;
  for (i1=0; i1<rows *cols; i1++)
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
   Coordinate: [0, 19, 4, 0, 0] 
  */
  
  
  for (orio_i=0; orio_i<ORIO_REPS; orio_i++) {
    orio_t_start = getClock();
    
    

  int i, j, k;
  int c_ind, a_row, c_row;


  /*@ begin Loop (  
    transform Composite(
      unrolljam = (['i','j','k'],[U_I,U_J,U_K]),
      vector = (VEC, ['ivdep','vector always'])
    )
    for (i = 0; i <= rows_a-1; i++) {
      a_row = cols_a * i;
      c_row = cols_b * i;
      for (j = 0; j <= cols_b-1; j++) {
        c_ind = j + c_row;
        mat_c[c_ind] = 0;
        for (k = 0; k <= cols_a-1; k++) {
          mat_c[c_ind] += mat_a[a_row + k] * mat_b[cols_b * k + j];
        }
      } 
    }
  ) @*/
  for (i=0; i<=rows_a-1; i++ ) {
    a_row=cols_a*i;
    c_row=cols_b*i;
    {
      int j;
      for (j=0; j<=cols_b-20; j=j+20) {
        c_ind=j+c_row;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j];
        }
        c_ind=j+c_row+1;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+1];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+1];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+1];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+1];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+1];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+1];
        }
        c_ind=j+c_row+2;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+2];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+2];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+2];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+2];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+2];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+2];
        }
        c_ind=j+c_row+3;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+3];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+3];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+3];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+3];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+3];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+3];
        }
        c_ind=j+c_row+4;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+4];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+4];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+4];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+4];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+4];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+4];
        }
        c_ind=j+c_row+5;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+5];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+5];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+5];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+5];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+5];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+5];
        }
        c_ind=j+c_row+6;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+6];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+6];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+6];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+6];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+6];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+6];
        }
        c_ind=j+c_row+7;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+7];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+7];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+7];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+7];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+7];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+7];
        }
        c_ind=j+c_row+8;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+8];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+8];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+8];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+8];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+8];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+8];
        }
        c_ind=j+c_row+9;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+9];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+9];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+9];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+9];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+9];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+9];
        }
        c_ind=j+c_row+10;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+10];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+10];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+10];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+10];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+10];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+10];
        }
        c_ind=j+c_row+11;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+11];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+11];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+11];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+11];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+11];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+11];
        }
        c_ind=j+c_row+12;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+12];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+12];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+12];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+12];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+12];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+12];
        }
        c_ind=j+c_row+13;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+13];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+13];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+13];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+13];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+13];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+13];
        }
        c_ind=j+c_row+14;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+14];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+14];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+14];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+14];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+14];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+14];
        }
        c_ind=j+c_row+15;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+15];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+15];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+15];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+15];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+15];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+15];
        }
        c_ind=j+c_row+16;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+16];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+16];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+16];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+16];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+16];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+16];
        }
        c_ind=j+c_row+17;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+17];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+17];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+17];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+17];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+17];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+17];
        }
        c_ind=j+c_row+18;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+18];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+18];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+18];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+18];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+18];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+18];
        }
        c_ind=j+c_row+19;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+19];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j+19];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j+19];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j+19];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j+19];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j+19];
        }
      }
      for (j=cols_b-((cols_b-(0))%20); j<=cols_b-1; j=j+1) {
        c_ind=j+c_row;
        mat_c[c_ind]=0;
        {
          int k;
          for (k=0; k<=cols_a-5; k=k+5) {
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+1]*mat_b[cols_b*(k+1)+j];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+2]*mat_b[cols_b*(k+2)+j];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+3]*mat_b[cols_b*(k+3)+j];
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k+4]*mat_b[cols_b*(k+4)+j];
          }
          for (k=cols_a-((cols_a-(0))%5); k<=cols_a-1; k=k+1) 
            mat_c[c_ind]=mat_c[c_ind]+mat_a[a_row+k]*mat_b[cols_b*k+j];
        }
      }
    }
  }
/*@ end @*/


    
    orio_t_end = getClock();
    orio_t = orio_t_end - orio_t_start;
    printf("{'[0, 19, 4, 0, 0]' : %g}\n", orio_t);
    
    if (orio_i==0) {
      
    }
  }
  
  
  
  return 0;
}
