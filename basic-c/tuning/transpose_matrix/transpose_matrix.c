#include "../../linear_algebra.h"


void transpose_matrix(TYPE* mat_a, int rows_a, int cols_a, TYPE* mat_c) {
 

/*@ begin PerfTuning (

 def build {
   arg build_command = 'gcc';
   #arg libs = '-lrt';  # Only needed on linux
 } 

 def performance_counter {
   arg repetitions = 5;
 }

 def performance_params {  
  param U_I[] = range(1,31);
  param U_J[] = range(1,31);

  param VEC[] = [False,True];

  param CFLAGS[] = ['-O0', '-O1', '-O2', '-O3'];
  constraint unroll_limit = ((U_I == 1) or (U_J == 1));

 }
 
 def input_params {
  let N = [10, 20];
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

  int i, j;
  int a_row;

/*@ begin Loop (  
  transform Composite(
    unrolljam = (['i','j'],[U_I,U_J]),
    vector = (VEC, ['ivdep','vector always'])
  )
  for (i = 0; i <= rows_a-1; i++) {
    a_row = cols_a * i;
    for (j = 0; j <= cols_a-1; j++) {
      mat_c[rows_a * j + i] = mat_a[a_row + j];
    }
  }
) @*/

  for (i = 0; i <= rows_a-1; i++) {
    a_row = cols_a * i;
    for (j = 0; j <= cols_a-1; j++) {
      mat_c[rows_a * j + i] = mat_a[a_row + j];
    }
  }


/*@ end @*/
/*@ end @*/

}
