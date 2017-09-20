
#include <stdio.h>

void print_matrix(double* mat_a, int rows_a, int cols_a) {

  int i, j;

  for (i = 0; i < rows_a; i++) {
    for (j = 0; j < cols_a; j++) {
      printf("%.4f ", mat_a[i * cols_a + j]);
    }
    printf("\n\n");
  }
}

int main(int argc, char **argv) {

  int m = 2, n = 6;

  double C[] = {1, 0, 0, 0, 0, 0, 
                0, 0, 0, 1, 0, 0};


  double C_T[] = {1,0,
                  0,0,
                  0,0,
                  0,1,
                  0,0,
                  0,0};
              
  double id[] = {1,0,0,0,0,0,
                 0,1,0,0,0,0,
                 0,0,1,0,0,0,
                 0,0,0,1,0,0,
                 0,0,0,0,1,0,
                 0,0,0,0,0,1};
                
  double K[] = {1,1,
                1,1,
                1,1,
                1,1,
                1,1,
                1,1};

  double R[] = {1,1,
                1,1};

  double x_hat_new[] = {1,1,1,1,1,1};
  double x_hat[]     = {1,1,1,1,1,1};
  double y[]         = {1,1};


  double P[] = {2,2,0,0,0,0,
                0,2,2,0,0,0,
                0,0,2,0,0,0,
                0,0,0,2,2,0,
                0,0,0,0,2,2,
                0,0,0,0,0,2};


  double temp_1[] = {2,2,0,0,0,0,
                0,2,2,0,0,0,
                0,0,2,2,0,0,
                0,0,0,2,2,0,
                0,0,0,0,2,2,
                0,0,0,0,0,2};

  double temp_2[] = {2,2,0,0,0,0,
                0,2,2,0,0,0,
                0,0,2,2,0,0,
                0,0,0,2,2,0,
                0,0,0,0,2,2,
                0,0,0,0,0,2};

  double temp_3[] = {2,2,0,0,0,0,
                0,2,2,0,0,0,
                0,0,2,2,0,0,
                0,0,0,2,2,0,
                0,0,0,0,2,2,
                0,0,0,0,0,2};

  double temp_4[] = {2,2,0,0,0,0,
                0,2,2,0,0,0,
                0,0,2,0,0,0,
                0,0,0,2,2,0,
                0,0,0,0,2,2,
                0,0,0,0,0,2};

  int C_nrows   = m;
  int C_ncols   = n; 
  int I_nrows   = n;
  int I_ncols   = n; 
  int K_nrows   = n;
  int K_ncols   = m; 
  int xhn_nrows = n;
  int xhn_ncols = 1; 
  int y_nrows   = m;
  int y_ncols   = 1; 
  int P_nrows   = n;
  int P_ncols   = n; 
  int xh_nrows   = n;
  int xh_ncols   = 1;

  correct4(C_nrows,   C_ncols,   C, 
           I_nrows,   I_ncols,   id, 
           K_nrows,   K_ncols,   K, 
           xhn_nrows, xhn_ncols, x_hat_new, 
           y_nrows,   y_ncols,   y, 
           P_nrows,   P_ncols,   P, 
           xh_nrows,  xh_ncols,  x_hat);
  // correct(y, x_hat, 
  //         n, m,
  //         C, R, P, K,
  //         x_hat_new, C_T, id,
  //         temp_1, temp_2, temp_3, temp_4);
  print_matrix(P, P_nrows, P_ncols);
  printf("\n");

}