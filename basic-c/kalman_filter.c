/*
 * kalman_filter.c
 * super basic Kalman filter implementation
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate or introductions to potential employers.

*/

#define TYPE double
#define N 4

//TODO these aren't always square
void setup_matrices(TYPE* &F, TYPE* &Q, TYPE* &H, TYPE* &R) {

  int size = N * N;

  TYPE* &F = malloc(size*sizeof(TYPE));
  TYPE* &Q = malloc(size*sizeof(TYPE));
  TYPE* &H = malloc(size*sizeof(TYPE));
  TYPE* &R = malloc(size*sizeof(TYPE));

}

void destroy_matrices(TYPE* &F, TYPE* &Q, TYPE* &H, TYPE* &R) {
  free F;
  free Q;
  free H;
  free R;
}

void prediction() {

}

void update() {

}
