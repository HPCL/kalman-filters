#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s980 = 2;

int __s979 = 2;

double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t19;
double *t8 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s979) {
// 2_1
int __m979 = i + __s979 > P_ncols ? P_ncols - i : __s979;
double *t13 = t8 + i;
double *t14 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t26 = t16 + j*P_ncols;
double *t25 = t13 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t26[__zr__] = 0.0;
for (k=0; k<__m979; k+=1) {
// 2_3
double *t36 = t14 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t26[l] += (t25[k]*t36[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s980) {
// 4_1
int __m980 = i + __s980 > P_ncols ? P_ncols - i : __s980;
double *t18 = t19 + i;
double *t24 = t12 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t29 = t18 + j*P_ncols;
double *t28 = t16 + j*P_ncols;
for (k=0; k<__m980; k+=1) {
// 4_3
double *t42 = t24 + k*P_ncols;
t29[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t29[k] += (t28[l]*t42[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t22 = P + i*P_ncols;
double *t20 = t11 + i*P_ncols;
double *t21 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t22[j] = (t20[j]+t21[j]);
}
}
free(t19);
free(t16);
}
