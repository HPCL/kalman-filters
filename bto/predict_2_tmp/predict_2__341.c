#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s929 = 2;

int __s928 = 2;

int __s927 = 10;

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t23;
double *t10 = t19;
double *t8 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s927) {
// 2_1
int __m927 = i + __s927 > P_ncols ? P_ncols - i : __s927;
double *t16 = t8 + i;
double *t17 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t30 = t19 + j*P_ncols;
double *t29 = t16 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t30[__zr__] = 0.0;
for (k=0; k<__m927; k+=1) {
// 2_3
double *t40 = t17 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t30[l] += (t29[k]*t40[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s928) {
// 4_1
int __m928 = i + __s928 > P_ncols ? P_ncols - i : __s928;
double *t20 = t10 + i;
double *t28 = t12 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t33 = t23 + j*P_ncols;
double *t32 = t20 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t50 = t28 + k*P_ncols;
t33[k] = 0.0;
for (l=0; l<__m928; l+=1) {
// 4_4
t33[k] += (t32[l]*t50[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s929) {
// 6_1
int __m929 = i + __s929 > P_ncols ? P_ncols - i : __s929;
double *t26 = P + i*P_ncols;
double *t24 = t13 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<__m929; j+=1) {
// 6_2
double *t37 = t26 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t23);
free(t19);
}
