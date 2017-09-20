#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s972 = 2;

int __s971 = 2;

double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t10 = t16;
double *t8 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s971) {
// 2_1
int __m971 = i + __s971 > P_ncols ? P_ncols - i : __s971;
double *t13 = t8 + i;
double *t14 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t27 = t16 + j*P_ncols;
double *t26 = t13 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t27[__zr__] = 0.0;
for (k=0; k<__m971; k+=1) {
// 2_3
double *t37 = t14 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t27[l] += (t26[k]*t37[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s972) {
// 4_1
int __m972 = i + __s972 > P_ncols ? P_ncols - i : __s972;
double *t17 = t10 + i;
double *t25 = t12 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t30 = t20 + j*P_ncols;
double *t29 = t17 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t43 = t25 + k*P_ncols;
t30[k] = 0.0;
for (l=0; l<__m972; l+=1) {
// 4_4
t30[k] += (t29[l]*t43[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t23 = P + i*P_ncols;
double *t21 = t20 + i*P_ncols;
double *t22 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t23[j] = (t21[j]+t22[j]);
}
}
free(t20);
free(t16);
}
