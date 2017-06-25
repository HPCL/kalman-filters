#include "../../linear_algebra.h"


void transpose_matrix(TYPE* mat_a, int rows_a, int cols_a, TYPE* mat_c) {
 

/*@ begin PerfTuning (

 def build {
   arg build_command = 'icc';
   #arg libs = '-lrt';  # Only needed on linux
 } 

 def performance_counter {
   arg repetitions = 5;
 }

 def performance_params {  
  param U_I[] = range(1,6);
  param U_J[] = range(1,6);

  param RT1_I[] = [1,2,6];
  param RT1_J[] = [1,2,6];

  param VEC[] = [False,True];

  param CFLAGS[] = ['-O1', '-O2', '-O3'];
  constraint unroll_limit = ((U_I == 1) or (U_J == 1));
  constraint reg_capacity_1 = (RT1_I*RT1_J <= 150);

 }
 
 def input_params {
      let N = [6];
  param rows_a[] = N;
  param cols_a[] = N;
 }
 
 def input_vars {
   decl dynamic double mat_a[rows_a*cols_a] = random;
   decl dynamic double mat_c[rows_a*cols_a] = 0;
 }
 
 def search {
   arg algorithm = 'Exhaustive';
 }

) @*/
/**-- (Generated by Orio) 
Best performance cost: 
  [1.119e-06, 2.35e-07, 1.85e-07, 1.83e-07, 1.82e-07] 
Tuned for specific problem sizes: 
  cols_a = 6 
  rows_a = 6 
Best performance parameters: 
  CFLAGS = -O1 
  RT1_I = 6 
  RT1_J = 1 
  U_I = 4 
  U_J = 1 
  VEC = False 
--**/


  int i, j;
  int it,jt;
  int a_row;

/*@ begin Loop (  
  transform Composite(
    unrolljam = (['i','j'],[U_I,U_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT1_I,RT1_J])
  )
  for (i = 0; i <= rows_a-1; i++) {
    for (j = 0; j <= cols_a-1; j++) {
      mat_c[rows_a * j + i] = mat_a[cols_a * i + j];
    }
  }
) @*/
{
  for (it=0; it<=rows_a-6; it=it+6) {
    for (j=0; j<=cols_a-1; j++ ) {
      mat_c[rows_a*j+it]=mat_a[cols_a*it+j];
      mat_c[rows_a*j+(it+1)]=mat_a[cols_a*(it+1)+j];
      mat_c[rows_a*j+(it+2)]=mat_a[cols_a*(it+2)+j];
      mat_c[rows_a*j+(it+3)]=mat_a[cols_a*(it+3)+j];
      mat_c[rows_a*j+(it+4)]=mat_a[cols_a*(it+4)+j];
      mat_c[rows_a*j+(it+5)]=mat_a[cols_a*(it+5)+j];
    }
  }
  {
    int i;
    for (i=it; i<=rows_a-4; i=i+4) {
      for (j=0; j<=cols_a-1; j++ ) {
        mat_c[rows_a*j+i]=mat_a[cols_a*i+j];
        mat_c[rows_a*j+i+1]=mat_a[cols_a*(i+1)+j];
        mat_c[rows_a*j+i+2]=mat_a[cols_a*(i+2)+j];
        mat_c[rows_a*j+i+3]=mat_a[cols_a*(i+3)+j];
      }
    }
    for (i=rows_a-((rows_a-(it))%4); i<=rows_a-1; i=i+1) 
      for (j=0; j<=cols_a-1; j++ ) {
        mat_c[rows_a*j+i]=mat_a[cols_a*i+j];
      }
  }
}
/*@ end @*/
/*@ end @*/

}
