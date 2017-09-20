#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void correct3b
(int C_nrows, int C_ncols, double* C, int P_nrows, int P_ncols, double* P, int temp_nrows, int temp_ncols, double* temp, int K_nrows, int K_ncols, double* K)
{
int disp, __zr__,i,j,k;

double *t9 = malloc(sizeof(double)*K_nrows*C_nrows);
for (i=0; i<K_nrows; i+=1) {
// 3_1
double *t8 = t9 + i*C_nrows;
double *t7 = P + i*P_ncols;
for (j=0; j<C_nrows; j+=1) {
// 3_2
double *t20 = C + j*P_ncols;
t8[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 3_3
t8[j] += (t7[k]*t20[k]);
}
}
}
for (i=0; i<K_nrows; i+=1) {
// 5_1
double *t11 = K + i*temp_ncols;
double *t10 = t9 + i*C_nrows;
for (__zr__ = 0; __zr__ < temp_ncols; ++__zr__) t11[__zr__] = 0.0;
for (j=0; j<C_nrows; j+=1) {
// 5_2
double *t17 = temp + j*temp_ncols;
for (k=0; k<temp_ncols; k+=1) {
// 5_3
t11[k] += (t10[j]*t17[k]);
}
}
}
free(t9);
}
