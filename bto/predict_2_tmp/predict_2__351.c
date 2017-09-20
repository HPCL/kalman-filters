#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s958 = 2;

int __s957 = 2;

double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t19;
double *t9 = t19;
double *t10 = A;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t15 = t16 + i*P_ncols;
double *t14 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t15[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t26 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t15[k] += (t14[j]*t26[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s957) {
// 4_1
int __m957 = i + __s957 > P_ncols ? P_ncols - i : __s957;
double *t18 = t19 + i;
double *t24 = t10 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t30 = t18 + j*P_ncols;
double *t29 = t16 + j*P_ncols;
for (k=0; k<__m957; k+=1) {
// 4_3
double *t46 = t24 + k*P_ncols;
t30[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t30[k] += (t29[l]*t46[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s958) {
// 6_1
int __m958 = i + __s958 > P_ncols ? P_ncols - i : __s958;
double *t22 = P + i*P_ncols;
double *t20 = t11 + i*P_ncols;
double *t21 = Q + i*P_ncols;
for (j=0; j<__m958; j+=1) {
// 6_2
double *t34 = t22 + j*P_ncols;
double *t32 = t20 + j*P_ncols;
double *t33 = t21 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t34[k] = (t32[k]+t33[k]);
}
}
}
free(t19);
free(t16);
}
