
void _multiply_matrix_batch(KALMAN_TYPE*** A, int rows_a, int cols_a,
                            KALMAN_TYPE*** B, int rows_b, int cols_b,
                            KALMAN_TYPE*** C,
                            int num_mats) {

/*@ begin PerfTuning (

    def build {
      arg build_command = 'icc';
      #arg libs = '-lrt';  # Only needed on linux
    } 

    def performance_counter {
      arg repetitions = 5;
    }

    def performance_params {  
      param U_I0[] = range(1,7);
      param U_J0[] = range(1,7);
      param U_L0[] = range(1,129);
      param U_I[] = range(1,7);
      param U_J[] = range(1,7);
      param U_K[] = range(1,7);
      param U_L[] = range(1,129);

      param VEC[] = [False,True];

      param RT0_L[] = [1,32];
      param RT1_L[] = [1,32];

      param T0_L[] = [1, 2048, 4096];
      param T1_L[] = [1, 2048, 4096];

      constraint tile1 = ((T0_L == 1) or (RT0_L == 1));
      constraint tile2 = ((T1_L == 1) or (RT1_L == 1));
    }

    def input_params {
      let N = [6, 60, 120];
      let M = [3000000, 3000, 300];
      param rows_a[] = N;
      param cols_a[] = N;
      param cols_b[] = N;
      param num_mats[] = M;
    }

    def input_vars {
      decl dynamic double A[rows_a][cols_a][num_mats] = random;
      decl dynamic double B[cols_a][cols_b][num_mats] = random;
      decl dynamic double C[rows_a][cols_b][num_mats] = 0;
    }

    def search {
      arg algorithm = 'Randomsearch';
      arg total_runs  = 100000;
    }

  ) @*/

  int i,j,k,l;
  int it,jt,kt,lt, ll;
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y)) 

/*@ begin Loop (  
    transform Composite(
      unrolljam = (['i','j','l'],[U_I0,U_J0,U_L0]),
      regtile = (['l'],[RT0_L]),
      tile = ([('l',T0_L,'ll')]),
      vector = (VEC, ['vector always'])
    )
  for (i = 0; i <= rows_a-1; i++) {
    for (j = 0; j <= cols_b-1; j++) {
      for (l = 0; l <= num_mats-1; l++) {
        C[i][j][l] = 0;
      }
    }
  } 

    transform Composite(
      unrolljam = (['i','j','k','l'],[U_I,U_J,U_K,U_L]),
      regtile = (['l'],[RT1_L]),
      tile = ([('l',T1_L,'ll')]),
      vector = (VEC, ['vector always'])
    )
  for (i = 0; i <= rows_a-1; i++) {
    for (j = 0; j <= cols_b-1; j++) {
      for (k = 0; k <= cols_a-1; k++) {
        for (l = 0; l <= num_mats-1; l++) {
          C[i][j][l] += A[i][k][l] * B[k][j][l];
        }
      }
    } 
  }
  ) @*/

  for (i = 0; i <= rows_a-1; i++) {
    for (j = 0; j <= cols_b-1; j++) {
      for (l = 0; l <= num_mats-1; l++) {
        C[i][j][l] = 0;
      }
    }
  } 

  for (i = 0; i <= rows_a-1; i++) {
    for (j = 0; j <= cols_b-1; j++) {
      for (k = 0; k <= cols_a-1; k++) {
        for (l = 0; l <= num_mats-1; l++) {
          C[i][j][l] += A[i][k][l] * B[k][j][l];
        }
      }
    } 
  }

/*@ end @*/
/*@ end @*/
} 