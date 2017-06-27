void add_matrix(TYPE* mat_a, int rows, int cols, TYPE* mat_b, TYPE* mat_c) {


  /*@ begin PerfTuning (

   def build {
      arg build_command = 'mpicc';
      arg libs = '-lrt';  # Only needed on linux
      arg batch_command = 'sh oreo.sh';
      arg status_command = 'qstat';
      arg num_procs = 12;
    }

   def performance_counter {
     arg repetitions = 5;
   }
   def performance_params {  
     param UF[] = range(1,11);
     param CFLAGS[] = ['-O0', '-O1', '-O2', '-O3'];
     #constraint divisible_by_two = (UF % 2 == 0);
   }
   def input_params {
    let R = [100];
    let C = [100];
    param rows[] = R;
    param cols[] = C;
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
  int ind, row;


  /*@ begin Loop ( 
    transform Unroll(ufactor=UF) 
    for (i = 0; i <= rows-1; i++) {
      row = cols * i;
      for (j = 0; j <= cols-1; j++) {
        ind = row + j;
        mat_c[ind] = mat_a[ind] + mat_b[ind];
      }
    }
  ) @*/

  for (i = 0; i <= rows-1; i++) {
    row = cols * i;
    for (j = 0; j <= cols-1; j++) {
      ind = row + j;
      mat_c[ind] = mat_a[ind] + mat_b[ind];
    }
  }

  /*@ end @*/
  /*@ end @*/

}