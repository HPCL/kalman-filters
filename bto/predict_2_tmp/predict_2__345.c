#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s940 = 12;

int __s939 = 2;

int __s938 = 2;

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t22;
double *t10 = t18;
double *t9 = t18;
double *t8 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s938) {
// 2_1
int __m938 = i + __s938 > P_ncols ? P_ncols - i : __s938;
double *t17 = t18 + i*P_ncols;
double *t16 = t8 + i*P_ncols;
for (j=0; j<__m938; j+=1) {
// 2_2
double *t29 = t17 + j*P_ncols;
double *t28 = t16 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t29[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t39 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t29[l] += (t28[k]*t39[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s939) {
// 4_1
int __m939 = i + __s939 > P_ncols ? P_ncols - i : __s939;
double *t19 = t10 + i;
double *t27 = t12 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t32 = t22 + j*P_ncols;
double *t31 = t19 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t49 = t27 + k*P_ncols;
t32[k] = 0.0;
for (l=0; l<__m939; l+=1) {
// 4_4
t32[k] += (t31[l]*t49[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s940) {
// 6_1
int __m940 = i + __s940 > P_ncols ? P_ncols - i : __s940;
double *t25 = P + i*P_ncols;
double *t23 = t13 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<__m940; j+=1) {
// 6_2
double *t36 = t25 + j*P_ncols;
double *t34 = t23 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t36[k] = (t34[k]+t35[k]);
}
}
}
free(t22);
free(t18);
}
