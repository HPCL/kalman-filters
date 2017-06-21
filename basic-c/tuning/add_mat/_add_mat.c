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
if ((rows<=10) && (cols<=10)) {

/**-- (Generated by Orio) 
Best performance cost: 
  [1.838e-06, 9.28e-07, 7.83e-07, 7.66e-07, 7.71e-07] 
Tuned for specific problem sizes: 
  cols = 10 
  rows = 10 
Best performance parameters: 
  CFLAGS = -O2 
  U_I = 10 
  U_J = 1 
  VEC = False 
--**/


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
{
  int i;
  for (i=0; i<=rows-10; i=i+10) {
    for (j=0; j<=cols-1; j++ ) {
      mat_c[cols*i+j]=mat_a[cols*i+j]+mat_b[cols*i+j];
      mat_c[cols*(i+1)+j]=mat_a[cols*(i+1)+j]+mat_b[cols*(i+1)+j];
      mat_c[cols*(i+2)+j]=mat_a[cols*(i+2)+j]+mat_b[cols*(i+2)+j];
      mat_c[cols*(i+3)+j]=mat_a[cols*(i+3)+j]+mat_b[cols*(i+3)+j];
      mat_c[cols*(i+4)+j]=mat_a[cols*(i+4)+j]+mat_b[cols*(i+4)+j];
      mat_c[cols*(i+5)+j]=mat_a[cols*(i+5)+j]+mat_b[cols*(i+5)+j];
      mat_c[cols*(i+6)+j]=mat_a[cols*(i+6)+j]+mat_b[cols*(i+6)+j];
      mat_c[cols*(i+7)+j]=mat_a[cols*(i+7)+j]+mat_b[cols*(i+7)+j];
      mat_c[cols*(i+8)+j]=mat_a[cols*(i+8)+j]+mat_b[cols*(i+8)+j];
      mat_c[cols*(i+9)+j]=mat_a[cols*(i+9)+j]+mat_b[cols*(i+9)+j];
    }
  }
  for (i=rows-((rows-(0))%10); i<=rows-1; i=i+1) 
    for (j=0; j<=cols-1; j++ ) {
      mat_c[cols*i+j]=mat_a[cols*i+j]+mat_b[cols*i+j];
    }
}
/*@ end @*/
} else if ((rows<=10) && (cols<=20)) {

/**-- (Generated by Orio) 
Best performance cost: 
  [2.553e-06, 1.535e-06, 1.412e-06, 1.406e-06, 1.387e-06] 
Tuned for specific problem sizes: 
  cols = 20 
  rows = 10 
Best performance parameters: 
  CFLAGS = -O1 
  U_I = 10 
  U_J = 1 
  VEC = False 
--**/


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
{
  int i;
  for (i=0; i<=rows-10; i=i+10) {
    for (j=0; j<=cols-1; j++ ) {
      mat_c[cols*i+j]=mat_a[cols*i+j]+mat_b[cols*i+j];
      mat_c[cols*(i+1)+j]=mat_a[cols*(i+1)+j]+mat_b[cols*(i+1)+j];
      mat_c[cols*(i+2)+j]=mat_a[cols*(i+2)+j]+mat_b[cols*(i+2)+j];
      mat_c[cols*(i+3)+j]=mat_a[cols*(i+3)+j]+mat_b[cols*(i+3)+j];
      mat_c[cols*(i+4)+j]=mat_a[cols*(i+4)+j]+mat_b[cols*(i+4)+j];
      mat_c[cols*(i+5)+j]=mat_a[cols*(i+5)+j]+mat_b[cols*(i+5)+j];
      mat_c[cols*(i+6)+j]=mat_a[cols*(i+6)+j]+mat_b[cols*(i+6)+j];
      mat_c[cols*(i+7)+j]=mat_a[cols*(i+7)+j]+mat_b[cols*(i+7)+j];
      mat_c[cols*(i+8)+j]=mat_a[cols*(i+8)+j]+mat_b[cols*(i+8)+j];
      mat_c[cols*(i+9)+j]=mat_a[cols*(i+9)+j]+mat_b[cols*(i+9)+j];
    }
  }
  for (i=rows-((rows-(0))%10); i<=rows-1; i=i+1) 
    for (j=0; j<=cols-1; j++ ) {
      mat_c[cols*i+j]=mat_a[cols*i+j]+mat_b[cols*i+j];
    }
}
/*@ end @*/
} else if ((rows<=20) && (cols<=10)) {

/**-- (Generated by Orio) 
Best performance cost: 
  [2.553e-06, 1.602e-06, 1.427e-06, 1.419e-06, 1.422e-06] 
Tuned for specific problem sizes: 
  cols = 10 
  rows = 20 
Best performance parameters: 
  CFLAGS = -O1 
  U_I = 10 
  U_J = 1 
  VEC = False 
--**/


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
{
  int i;
  for (i=0; i<=rows-10; i=i+10) {
    for (j=0; j<=cols-1; j++ ) {
      mat_c[cols*i+j]=mat_a[cols*i+j]+mat_b[cols*i+j];
      mat_c[cols*(i+1)+j]=mat_a[cols*(i+1)+j]+mat_b[cols*(i+1)+j];
      mat_c[cols*(i+2)+j]=mat_a[cols*(i+2)+j]+mat_b[cols*(i+2)+j];
      mat_c[cols*(i+3)+j]=mat_a[cols*(i+3)+j]+mat_b[cols*(i+3)+j];
      mat_c[cols*(i+4)+j]=mat_a[cols*(i+4)+j]+mat_b[cols*(i+4)+j];
      mat_c[cols*(i+5)+j]=mat_a[cols*(i+5)+j]+mat_b[cols*(i+5)+j];
      mat_c[cols*(i+6)+j]=mat_a[cols*(i+6)+j]+mat_b[cols*(i+6)+j];
      mat_c[cols*(i+7)+j]=mat_a[cols*(i+7)+j]+mat_b[cols*(i+7)+j];
      mat_c[cols*(i+8)+j]=mat_a[cols*(i+8)+j]+mat_b[cols*(i+8)+j];
      mat_c[cols*(i+9)+j]=mat_a[cols*(i+9)+j]+mat_b[cols*(i+9)+j];
    }
  }
  for (i=rows-((rows-(0))%10); i<=rows-1; i=i+1) 
    for (j=0; j<=cols-1; j++ ) {
      mat_c[cols*i+j]=mat_a[cols*i+j]+mat_b[cols*i+j];
    }
}
/*@ end @*/
} else if ((rows<=20) && (cols<=20)) {

/**-- (Generated by Orio) 
Best performance cost: 
  [3.437e-06, 2.861e-06, 2.59e-06, 2.598e-06, 2.551e-06] 
Tuned for specific problem sizes: 
  cols = 20 
  rows = 20 
Best performance parameters: 
  CFLAGS = -O3 
  U_I = 20 
  U_J = 1 
  VEC = False 
--**/


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
{
  int i;
  for (i=0; i<=rows-20; i=i+20) {
    for (j=0; j<=cols-1; j++ ) {
      mat_c[cols*i+j]=mat_a[cols*i+j]+mat_b[cols*i+j];
      mat_c[cols*(i+1)+j]=mat_a[cols*(i+1)+j]+mat_b[cols*(i+1)+j];
      mat_c[cols*(i+2)+j]=mat_a[cols*(i+2)+j]+mat_b[cols*(i+2)+j];
      mat_c[cols*(i+3)+j]=mat_a[cols*(i+3)+j]+mat_b[cols*(i+3)+j];
      mat_c[cols*(i+4)+j]=mat_a[cols*(i+4)+j]+mat_b[cols*(i+4)+j];
      mat_c[cols*(i+5)+j]=mat_a[cols*(i+5)+j]+mat_b[cols*(i+5)+j];
      mat_c[cols*(i+6)+j]=mat_a[cols*(i+6)+j]+mat_b[cols*(i+6)+j];
      mat_c[cols*(i+7)+j]=mat_a[cols*(i+7)+j]+mat_b[cols*(i+7)+j];
      mat_c[cols*(i+8)+j]=mat_a[cols*(i+8)+j]+mat_b[cols*(i+8)+j];
      mat_c[cols*(i+9)+j]=mat_a[cols*(i+9)+j]+mat_b[cols*(i+9)+j];
      mat_c[cols*(i+10)+j]=mat_a[cols*(i+10)+j]+mat_b[cols*(i+10)+j];
      mat_c[cols*(i+11)+j]=mat_a[cols*(i+11)+j]+mat_b[cols*(i+11)+j];
      mat_c[cols*(i+12)+j]=mat_a[cols*(i+12)+j]+mat_b[cols*(i+12)+j];
      mat_c[cols*(i+13)+j]=mat_a[cols*(i+13)+j]+mat_b[cols*(i+13)+j];
      mat_c[cols*(i+14)+j]=mat_a[cols*(i+14)+j]+mat_b[cols*(i+14)+j];
      mat_c[cols*(i+15)+j]=mat_a[cols*(i+15)+j]+mat_b[cols*(i+15)+j];
      mat_c[cols*(i+16)+j]=mat_a[cols*(i+16)+j]+mat_b[cols*(i+16)+j];
      mat_c[cols*(i+17)+j]=mat_a[cols*(i+17)+j]+mat_b[cols*(i+17)+j];
      mat_c[cols*(i+18)+j]=mat_a[cols*(i+18)+j]+mat_b[cols*(i+18)+j];
      mat_c[cols*(i+19)+j]=mat_a[cols*(i+19)+j]+mat_b[cols*(i+19)+j];
    }
  }
  for (i=rows-((rows-(0))%20); i<=rows-1; i=i+1) 
    for (j=0; j<=cols-1; j++ ) {
      mat_c[cols*i+j]=mat_a[cols*i+j]+mat_b[cols*i+j];
    }
}
/*@ end @*/
}
/*@ end @*/

}