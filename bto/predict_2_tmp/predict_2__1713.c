#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s4035 = 10;

int __s4034 = 10;

double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t12 = A;
double *t10 = t15;
double *t9 = t15;
for (i=0; i<P_ncols; i+=__s4034) {
// 2_1
int __m4034 = i + __s4034 > P_ncols ? P_ncols - i : __s4034;
double *t14 = t15 + i;
double *t13 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t26 = t14 + j*P_ncols;
double *t25 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m4034; ++__zr__) t26[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t36 = t13 + k*P_ncols;
for (l=0; l<__m4034; l+=1) {
// 2_4
t26[l] += (t25[k]*t36[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s4035) {
// 4_1
int __m4035 = i + __s4035 > P_ncols ? P_ncols - i : __s4035;
double *t16 = t10 + i;
double *t24 = t12 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t29 = t19 + j*P_ncols;
double *t28 = t16 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t42 = t24 + k*P_ncols;
t29[k] = 0.0;
for (l=0; l<__m4035; l+=1) {
// 4_4
t29[k] += (t28[l]*t42[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t22 = P + i*P_ncols;
double *t20 = t19 + i*P_ncols;
double *t21 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t22[j] = (t20[j]+t21[j]);
}
}
free(t19);
free(t15);
}
