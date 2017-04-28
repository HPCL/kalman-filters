/*
 * test_linear_algebra.c
 * a small program to test the linear algebra code
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate or introductions to potential employers.

*/

 #include "linear_algebra.h"
 #include <stdio.h>

void test_inverse();
void test_cofactor();
void test_matrix_multiply();
void test_vector_multiply();
void test_add();
void test_transpose();
void test_determinant();
void test_zero_and_id();

int main(int argc, char **argv) {
  
  // test_zero_and_id();
  test_inverse();
  // test_cofactor();
  // test_determinant();
  // test_transpose();
  // test_add();
  // test_multiply();

  return 0;
}

void test_vector_multiply() {
  int col_A = 3, row_A = 3;
  double A[] = {1,2,3,
                4,5,6,
                7,8,9};
                
  int col_B = 2, row_B = 3;
  double B[] = {1,2,
                3,4,
                5,6};
                
  int col_C = 2, row_C = 3;
  double C[] = {2,2,
                2,2,
                2,2};


  printf("\nA:\n");
  print_matrix(A, row_A, col_A);
  printf("\nB:\n");
  print_matrix(B, row_B, col_B);
  printf("\nC:\n");
  print_matrix(C, row_C, col_C);
  printf("\n");

  multiply_matrix(A, row_A, col_A, B, col_B, C);
  printf("\nC <- A * B:\n");
  print_matrix(C, row_C, col_C);
  printf("\n");
}

void test_matrix_multiply() {
  int col_A = 3, row_A = 3;
  double A[] = {1,2,3,
                4,5,6,
                7,8,9};
                
  int col_B = 2, row_B = 3;
  double B[] = {1,2,
                3,4,
                5,6};
                
  int col_C = 2, row_C = 3;
  double C[] = {2,2,
                2,2,
                2,2};


  printf("\nA:\n");
  print_matrix(A, row_A, col_A);
  printf("\nB:\n");
  print_matrix(B, row_B, col_B);
  printf("\nC:\n");
  print_matrix(C, row_C, col_C);
  printf("\n");

  multiply_matrix(A, row_A, col_A, B, col_B, C);
  printf("\nC <- A * B:\n");
  print_matrix(C, row_C, col_C);
  printf("\n");
}

void test_transpose_ multiply() {
  int col_A = 3, row_A = 4;
  double A[] = {1, 2, 3,
                4, 5, 6,
                7, 8, 9,
                10,11,12};
                                
  int col_C = 4, row_C = 3;
  double C[] = {2,2,2,2,
                2,2,2,2,
                2,2,2,2};


  printf("\nA:\n");
  print_matrix(A, row_A, col_A);
  printf("\nC:\n");
  print_matrix(C, row_C, col_C);
  printf("\n");

  transpose_matrix(A, row_A, col_A, C);
  printf("\nC <- A^T:\n");
  print_matrix(C, row_C, col_C);
  printf("\n");
}

void test_zero_and_id() {
  int col_A = 3, row_A = 3;
  double A[] = {1, 2, 3,
                4, 5, 6,
                7, 8, 9};


  printf("\nA:\n");
  print_matrix(A, row_A, col_A);
  printf("\n");

  set_zero(A, row_A, col_A);
  printf("\nzero:\n");
  print_matrix(A, row_A, col_A);
  printf("\n");
  set_identity(A, row_A, col_A);
  printf("\nidentity:\n");
  print_matrix(A, row_A, col_A);
  printf("\n");
}

void test_inverse() {

  int col_A = 4, row_A = 4;
  double A[] = {458.1233,0,-1,0,
                0,458.1233,0,0,
                0,0,1.63,0,
                0,0,0,1.63};

  double expected[] = {0.00218,0,0.00134,0,
                      0.0,0.00218,0.0,0,
                      0.0,0,0.613,0.0,
                      0.0,0,0.0,0.613};

  double result[] = {3,0,2,-1,
                1,2,0,-2,
                4,0,6,-3,
                5,0,2, 0};


  printf("\nA:\n");
  print_matrix(A, row_A, col_A);
  printf("\nExpected inverse:\n");
  print_matrix(expected, row_A, col_A);
  invert_matrix(A, row_A, result);
  printf("\nCalculated inverse:\n");
  print_matrix(result, row_A, col_A);
  printf("\n");

}
