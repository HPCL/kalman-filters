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
void test_multiply();
void test_add();
void test_transpose();
void test_determinant();
void test_zero_and_id();

int main(int argc, char **argv) {
  
  test_zero_and_id();
  // test_inverse();
  // test_cofactor();
  // test_determinant();
  // test_transpose();
  // test_add();
  // test_multiply();

  return 0;
}

void test_add() {
  int col_A = 3, row_A = 3;
  double A[] = {2,2,2,
                2,2,2,
                2,2,2};
                
  int col_B = 2, row_B = 3;
  double B[] = {2,2,
                2,2,
                2,2};
                
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

  add_matrix(A, row_A, col_A, B, C);
  printf("\nC <- A + B:\n");
  print_matrix(C, row_C, col_C);
  printf("\n");
}

void test_multiply() {
  int col_A = 3, row_A = 3;
  double A[] = {2,2,2,
                2,2,2,
                2,2,2};
                
  int col_B = 2, row_B = 3;
  double B[] = {2,2,
                2,2,
                2,2};
                
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

void test_transpose() {
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

void test_determinant() {
  int col_A = 2, row_A = 2; // -6
  double A[] = {6,-3,
                2, 0};
                
  int col_B = 3, row_B = 3; //12
  double B[] = {3,2,-1,
                1,0,-2,
                4,6,-3};
                
  int col_C = 4, row_C = 4; //20
  double C[] = {3,0,2,-1,
                1,2,0,-2,
                4,0,6,-3,
                5,0,2, 0};


  printf("\nA, expected det = -6:\n");
  print_matrix(A, row_A, col_A);
  printf("%f\n", determinant_matrix(A, row_A));
  printf("\nB, expected det = 12:\n");
  print_matrix(B, row_B, col_B);
  printf("%f\n", determinant_matrix(B, row_B));
  printf("\nC, expected det = 20:\n");
  print_matrix(C, row_C, col_C);
  printf("%f\n", determinant_matrix(C, row_C));
  printf("\n");

}

void test_cofactor() {

  int col_A = 4, row_A = 4;
  double A[] = {3,0,2,-1,
                1,2,0,-2,
                4,0,6,-3,
                5,0,2, 0};

  double expected[] = {12,-50,-30,-44,
                0,10,0,0,
                -4,10,10,8,
                0,20,10,20};

  double result[] = {3,0,2,-1,
                1,2,0,-2,
                4,0,6,-3,
                5,0,2, 0};


  printf("\nA:\n");
  print_matrix(A, row_A, col_A);
  printf("\nExpected cofactor:\n");
  print_matrix(expected, row_A, col_A);
  cofactor_matrix(A, row_A, result);
  printf("\nCalculated cofactor:\n");
  print_matrix(result, row_A, col_A);
  printf("\n");

}


void test_inverse() {

  int col_A = 4, row_A = 4;
  double A[] = {3,0,2,-1,
                1,2,0,-2,
                4,0,6,-3,
                5,0,2, 0};

  double expected[] = {0.6,0,-0.2,0,
                      -2.5,0.5,0.5,1,
                      -1.5,0,0.5,0.5,
                      -2.2,0,0.4,1};

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
