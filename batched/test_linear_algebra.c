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

 #include "matrix_batch.h"

 #include <stdio.h>
 #include <stdlib.h>

void test_inverse();
void test_cofactor();
void test_multiply();
void test_add();
void test_transpose();
void test_determinant();
void test_determinant_recur();
void test_zero_and_id();
void test_compute_LUP();

int main(int argc, char **argv) {

  char temp[16];
  printf("Enter 'c' to continue. Note it may require multiple entries.\n");
  // test_zero_and_id();
  // scanf("%s", temp);
  // test_inverse();
  // scanf("%s", temp);
  // test_cofactor();
  // scanf("%s", temp);
  // test_determinant();
  // scanf("%s", temp);
  // test_determinant_recur();
  // scanf("%s", temp);
  // test_transpose();
  // scanf("%s", temp);
  // test_add();
  scanf("%s", temp);
  test_multiply();
  scanf("%s", temp);
  // test_compute_LUP();
  // scanf("%s", temp);
  // test_compute_LUP_inline();
  // scanf("%s", temp);
  printf("Bye now!\n");

  return 0;
}

void test_add() {

}

void test_multiply() {
  struct batch A;
  struct batch B;
  struct batch C;

  int num_mats = 10;
  int n = 5; 
  int m = 5; 

  int i,j,k,l;

  init_batch(&A, num_mats, n, m);
  init_batch(&B, num_mats, n, m);
  init_batch(&C, num_mats, n, m);

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (l = 0; l < num_mats; l++) {
        A.mats[i][j][l] = 5;
        B.mats[i][j][l] = 5;
        C.mats[i][j][l] = 5;
      }
    }
  }

  for (l = 0; l < num_mats; l++) {
    print_matrix(&C, l);
  }

  batch_multiply(&A, &B, &C);

  for (l = 0; l < num_mats; l++) {
    print_matrix(&C, l);
  }

}

void test_transpose() {

}

void test_zero_and_id() {

}

void test_determinant() {

}


void test_determinant_recur() {


}

void test_cofactor() {

}


void test_inverse() {

}


void test_compute_LUP() {

}
