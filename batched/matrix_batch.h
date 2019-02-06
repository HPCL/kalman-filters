/*
 * matrix_batch.h
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * this is code for batched matrix operations
 * the key is that the matrices are held in a 3D array
 *   - the 3rd dimension is which matrix it belongs to
 *   - this allows the operations to be SIMDized 

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#ifndef MATRIX_BATCH_H
#define MATRIX_BATCH_H

#include <stdio.h>

#ifndef KALMAN_TYPE
#define KALMAN_TYPE double // in retrospect this will probably always be double
#endif

struct batch
{
  int num_mats;  // number of matrices
  int n;         // number of rows
  int m;         // number of columns
  KALMAN_TYPE*** mats; //will be n X m X num_mats
};




#endif
