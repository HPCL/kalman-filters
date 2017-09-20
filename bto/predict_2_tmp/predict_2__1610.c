#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s3817 = 2;

int __s3816 = 2;

double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t18;
double *t12 = A;
double *t9 = t15;
for (i=0; i<P_ncols; i+=__s3816) {
// 2_1
int __m3816 = i + __s3816 > P_ncols ? P_ncols - i : __s3816;
double *t14 = t15 + i;
double *t13 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t25 = t14 + j*P_ncols;
double *t24 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m3816; ++__zr__) t25[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t35 = t13 + k*P_ncols;
for (l=0; l<__m3816; l+=1) {
// 2_4
t25[l] += (t24[k]*t35[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s3817) {
// 4_1
int __m3817 = i + __s3817 > P_ncols ? P_ncols - i : __s3817;
double *t17 = t18 + i;
double *t23 = t12 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t28 = t17 + j*P_ncols;
double *t27 = t9 + j*P_ncols;
for (k=0; k<__m3817; k+=1) {
// 4_3
double *t41 = t23 + k*P_ncols;
t28[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t28[k] += (t27[l]*t41[l]);
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
