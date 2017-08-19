
#include <stdio.h>

void stupid(int A_nrows, int A_ncols, double* A, int B_nrows, int B_ncols, double* B, int Y_nrows, int Y_ncols, double* Y, int C_nrows, int C_ncols, double* C);
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

  int A_ncols = 2, A_nrows = 3;
  double A[] = {2,2,
                2,2,
                2,2};
                
  int B_ncols = 3, B_nrows = 2;
  double B[] = {3,3,3,
                3,3,3};
                
  int Y_ncols = 3, Y_nrows = 3;
  double Y[] = {1,1,1,
                1,1,1,
                1,1,1};
                
  int C_ncols = 3, C_nrows = 3;
  double C[] = {1,1,1,
                1,1,1,
                1,1,1};


  printf("\nA:\n");
  print_matrix(A, A_nrows, A_ncols);
  printf("\nB:\n");
  print_matrix(B, B_nrows, B_ncols);
  printf("\nY:\n");
  print_matrix(Y, Y_nrows, Y_ncols);
  printf("\nC:\n");
  print_matrix(C, C_nrows, C_ncols);
  printf("\n");

  stupid(A_nrows, A_ncols, A, B_nrows, B_ncols, B, Y_nrows, Y_ncols, Y, C_nrows, C_ncols, C);
  printf("\nC <- A * B + Y:\n");
  print_matrix(C, C_nrows, C_ncols);
  printf("\n");

}