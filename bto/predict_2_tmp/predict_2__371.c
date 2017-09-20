#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s1002 = 2;

int __s1001 = 2;

double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t17;
double *t10 = t14;
double *t9 = t14;
for (i=0; i<P_ncols; i+=__s1001) {
// 2_1
int __m1001 = i + __s1001 > P_ncols ? P_ncols - i : __s1001;
double *t13 = t14 + i;
double *t12 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t23 = t13 + j*P_ncols;
double *t22 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m1001; ++__zr__) t23[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t33 = t12 + k*P_ncols;
for (l=0; l<__m1001; l+=1) {
// 2_4
t23[l] += (t22[k]*t33[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s1002) {
// 4_1
int __m1002 = i + __s1002 > P_ncols ? P_ncols - i : __s1002;
double *t16 = t17 + i*P_ncols;
double *t15 = t10 + i*P_ncols;
for (j=0; j<__m1002; j+=1) {
// 4_2
double *t26 = t16 + j*P_ncols;
double *t25 = t15 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t39 = A + k*P_ncols;
t26[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t26[k] += (t25[l]*t39[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t20 = P + i*P_ncols;
double *t18 = t11 + i*P_ncols;
double *t19 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t20[j] = (t18[j]+t19[j]);
}
}
free(t17);
free(t14);
}
