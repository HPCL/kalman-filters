#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s461 = 2;

int __s460 = 2;

int __s459 = 10;

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t12 = t21;
double *t11 = t21;
double *t10 = t18;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s459) {
// 2_1
int __m459 = i + __s459 > P_ncols ? P_ncols - i : __s459;
double *t15 = t8 + i;
double *t16 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t27 = t18 + j*P_ncols;
double *t26 = t15 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t27[__zr__] = 0.0;
for (k=0; k<__m459; k+=1) {
// 2_3
double *t37 = t16 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t27[l] += (t26[k]*t37[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s460) {
// 4_1
int __m460 = i + __s460 > P_ncols ? P_ncols - i : __s460;
double *t20 = t21 + i*P_ncols;
double *t19 = t10 + i*P_ncols;
for (j=0; j<__m460; j+=1) {
// 4_2
double *t30 = t20 + j*P_ncols;
double *t29 = t19 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t47 = A + k*P_ncols;
t30[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t30[k] += (t29[l]*t47[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s461) {
// 6_1
int __m461 = i + __s461 > P_ncols ? P_ncols - i : __s461;
double *t24 = P + i*P_ncols;
double *t22 = t12 + i*P_ncols;
double *t23 = Q + i*P_ncols;
for (j=0; j<__m461; j+=1) {
// 6_2
double *t34 = t24 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t34[k] = (t32[k]+t33[k]);
}
}
}
free(t21);
free(t18);
}
