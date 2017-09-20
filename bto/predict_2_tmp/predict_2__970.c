#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s2488 = 2;

int __s2487 = 2;

double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t18;
double *t10 = t15;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s2487) {
// 2_1
int __m2487 = i + __s2487 > P_ncols ? P_ncols - i : __s2487;
double *t12 = t8 + i;
double *t13 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t24 = t15 + j*P_ncols;
double *t23 = t12 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t24[__zr__] = 0.0;
for (k=0; k<__m2487; k+=1) {
// 2_3
double *t34 = t13 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t24[l] += (t23[k]*t34[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s2488) {
// 4_1
int __m2488 = i + __s2488 > P_ncols ? P_ncols - i : __s2488;
double *t17 = t18 + i*P_ncols;
double *t16 = t10 + i*P_ncols;
for (j=0; j<__m2488; j+=1) {
// 4_2
double *t27 = t17 + j*P_ncols;
double *t26 = t16 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t40 = A + k*P_ncols;
t27[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t27[k] += (t26[l]*t40[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t21 = P + i*P_ncols;
double *t19 = t11 + i*P_ncols;
double *t20 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t21[j] = (t19[j]+t20[j]);
}
}
free(t18);
free(t15);
}
