#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k;

double *t12 = malloc(sizeof(double)*P_ncols);
double *t9 = malloc(sizeof(double)*P_ncols);
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t16 = P + i*P_ncols;
double *t8 = A + i*P_ncols;
double *t15 = Q + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t9[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t19 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t9[k] += (t8[j]*t19[k]);
}
}
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t29 = A + j*P_ncols;
t12[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t12[j] += (t9[k]*t29[k]);
}
}
for (j=0; j<P_ncols; j+=1) {
// 6_2
t16[j] = (t12[j]+t15[j]);
}
}
free(t12);
free(t9);
}
