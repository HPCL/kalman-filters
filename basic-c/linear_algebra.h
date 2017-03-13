/*
 * linear_algebra.h
 * simple header for matrix function code
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate or introductions to potential employers.

*/

#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <stdio.h>

#define TYPE double // in retrospect tis will probably always be double

void print_matrix(TYPE* mat_a, int rows_a, int cols_a);

void invert_matrix();

TYPE determinant_matrix(TYPE* mat_a, int n);

void add_matrix(TYPE* mat_a, int rows, int cols, TYPE* mat_b, TYPE* mat_c);

//@multiply matrices together
//@pre all matrices are initialized, c shouldn't have any important data in it
//     rows in b == cols in a
//     c is initialized to the same size as b
//@post mat_c has the result of multipling mat_a and mat_b
void multiply_matrix(TYPE* mat_a, int rows_a, int cols_a, TYPE* mat_b, int cols_b, TYPE* mat_c);

//@transpose a matrix
//@pre all matrices are initialized, c shouldn't have any important data in it
//     rows in c == cols in a
//@post mat_c has the transpose of mat_a
void transpose_matrix(TYPE* mat_a, int rows_a, int cols_a, TYPE* mat_c);

#endif
