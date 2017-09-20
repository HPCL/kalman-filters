#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s60 = 12;

double *t29 = malloc(sizeof(double)*P_ncols);
double *t26 = malloc(sizeof(double)*P_ncols);
double *t8 = A;
for (i=0; i<P_ncols; i+=__s60) {
// 2_1
int __m60 = i + __s60 > P_ncols ? P_ncols - i : __s60;
double *t23 = P + i*P_ncols;
double *t15 = t8 + i*P_ncols;
double *t22 = Q + i*P_ncols;
for (j=0; j<__m60; j+=1) {
// 2_2
double *t33 = t23 + j*P_ncols;
double *t25 = t15 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t26[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t36 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t26[l] += (t25[k]*t36[l]);
}
}
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t46 = A + k*P_ncols;
t29[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t29[k] += (t26[l]*t46[l]);
}
}
for (k=0; k<P_ncols; k+=1) {
// 6_3
t33[k] = (t29[k]+t32[k]);
}
}
}
free(t29);
free(t26);
}
