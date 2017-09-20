#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s816 = 2;

int __s815 = 2;

double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t10 = t18;
double *t9 = t15;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s815) {
// 2_1
int __m815 = i + __s815 > P_ncols ? P_ncols - i : __s815;
double *t14 = t15 + i*P_ncols;
double *t13 = t8 + i*P_ncols;
for (j=0; j<__m815; j+=1) {
// 2_2
double *t24 = t14 + j*P_ncols;
double *t23 = t13 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t24[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t35 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t24[l] += (t23[k]*t35[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t17 = t18 + i*P_ncols;
double *t16 = t9 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t33 = A + j*P_ncols;
t17[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t17[j] += (t16[k]*t33[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s816) {
// 6_1
int __m816 = i + __s816 > P_ncols ? P_ncols - i : __s816;
double *t21 = P + i*P_ncols;
double *t19 = t10 + i*P_ncols;
double *t20 = Q + i*P_ncols;
for (j=0; j<__m816; j+=1) {
// 6_2
double *t31 = t21 + j*P_ncols;
double *t29 = t19 + j*P_ncols;
double *t30 = t20 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t31[k] = (t29[k]+t30[k]);
}
}
}
free(t18);
free(t15);
}
