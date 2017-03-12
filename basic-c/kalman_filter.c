/*
 * kalman_filter.c
 * super basic Kalman filter implementation
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate or introductions to potential employers.

*/

#define TYPE
#define N

void setup_matrices(TYPE** &F, TYPE** &Q, TYPE** &H, TYPE** &R) {
  TYPE** &F = malloc(N*sizeof(TYPE*));
  TYPE** &Q = malloc(N*sizeof(TYPE*));
  TYPE** &H = malloc(N*sizeof(TYPE*));
  TYPE** &R = malloc(N*sizeof(TYPE*));

  for(int i = 0; i < N; i++){
    F = malloc(N*sizeof(TYPE));
    Q = malloc(N*sizeof(TYPE));
    H = malloc(N*sizeof(TYPE));
    R = malloc(N*sizeof(TYPE));
  }

}

void destroy_matrices(TYPE** &F, TYPE** &Q, TYPE** &H, TYPE** &R) {
  for(int i = 0; i < N; i++){
    free F;
    free Q;
    free H;
    free R;
  }
  
  free F;
  free Q;
  free H;
  free R;
}

void prediction() {

}

void update() {

}