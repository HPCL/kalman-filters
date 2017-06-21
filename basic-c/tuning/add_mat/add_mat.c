#include "../../linear_algebra.h"

void add_matrix(TYPE* mat_a, int rows, int cols, TYPE* mat_b, TYPE* mat_c)  {

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
  param rows[] = N;
  param cols[] = N;
 }
 
 def input_vars {
   decl dynamic double mat_a[rows*cols] = random;
   decl dynamic double mat_b[rows*cols] = random;
   decl dynamic double mat_c[rows*cols] = 0;
 }
 
 def search {
   arg algorithm = 'Exhaustive';
 }

) @*/

int i, j;

/*@ begin Loop (  
  transform Composite(
    unrolljam = (['i','j'],[U_I,U_J]),
    vector = (VEC, ['ivdep','vector always'])
)
  for (i = 0; i <= rows-1; i++) {
    for (j = 0; j <= cols-1; j++) {
      mat_c[ cols * i + j] = mat_a[ cols * i + j] + mat_b[ cols * i + j];
    }
  }
) @*/
  for (i = 0; i <= rows-1; i++) {
    for (j = 0; j <= cols-1; j++) {
      mat_c[ cols * i + j] = mat_a[ cols * i + j] + mat_b[ cols * i + j];
    }
  }

/*@ end @*/
/*@ end @*/

}