#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s3303 = 2;

double *t15 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t12 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t12;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s3303) {
// 2_1
int __m3303 = i + __s3303 > P_ncols ? P_ncols - i : __s3303;
double *t11 = t12 + i*P_ncols;
double *t10 = t8 + i*P_ncols;
for (j=0; j<__m3303; j+=1) {
// 2_2
double *t21 = t11 + j*P_ncols;
double *t20 = t10 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t21[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t32 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t21[l] += (t20[k]*t32[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t14 = t15 + i*P_ncols;
double *t13 = t9 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t30 = A + j*P_ncols;
t14[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t14[j] += (t13[k]*t30[k]);
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t18 = P + i*P_ncols;
double *t16 = t15 + i*P_ncols;
double *t17 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t18[j] = (t16[j]+t17[j]);
}
}
free(t15);
free(t12);
}
