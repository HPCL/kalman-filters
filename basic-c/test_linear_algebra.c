/*
 * test_linear_algebra.c
 * a small program to test the linear algebra code
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate or introductions to potential employers.

*/

 #include "linear_algebra.h"
 #include <stdio.h>

void test_multiply();
void test_add();

int main(int argc, char **argv) {
  
  test_add();
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
  printf("\nC <- A * B:\n");
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