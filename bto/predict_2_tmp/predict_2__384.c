#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s1025 = 12;

int __s1024 = 2;

double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t10 = t19;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s1024) {
// 2_1
int __m1024 = i + __s1024 > P_ncols ? P_ncols - i : __s1024;
double *t13 = t8 + i;
double *t14 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t25 = t16 + j*P_ncols;
double *t24 = t13 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t25[__zr__] = 0.0;
for (k=0; k<__m1024; k+=1) {
// 2_3
double *t36 = t14 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t25[l] += (t24[k]*t36[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t18 = t19 + i*P_ncols;
double *t17 = t16 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t34 = A + j*P_ncols;
t18[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t18[j] += (t17[k]*t34[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s1025) {
// 6_1
int __m1025 = i + __s1025 > P_ncols ? P_ncols - i : __s1025;
double *t22 = P + i*P_ncols;
double *t20 = t10 + i*P_ncols;
double *t21 = Q + i*P_ncols;
for (j=0; j<__m1025; j+=1) {
// 6_2
double *t32 = t22 + j*P_ncols;
double *t30 = t20 + j*P_ncols;
double *t31 = t21 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t32[k] = (t30[k]+t31[k]);
}
}
}
free(t19);
free(t16);
}
