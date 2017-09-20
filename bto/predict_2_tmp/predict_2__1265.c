#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s3213 = 12;

double *t17 = malloc(sizeof(double)*__s3213*P_ncols);
double *t15 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t8 = t15;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t14 = t15 + i*P_ncols;
double *t13 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t14[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t24 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t14[k] += (t13[j]*t24[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s3213) {
// 4_1
int __m3213 = i + __s3213 > P_ncols ? P_ncols - i : __s3213;
double *t21 = P + i*P_ncols;
double *t16 = t8 + i*P_ncols;
double *t20 = Q + i*P_ncols;
for (j=0; j<__m3213; j+=1) {
// 4_2
double *t28 = t17 + j*P_ncols;
double *t27 = t16 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t44 = A + k*P_ncols;
t28[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t28[k] += (t27[l]*t44[l]);
}
}
}
for (j=0; j<__m3213; j+=1) {
// 6_2
double *t32 = t21 + j*P_ncols;
double *t30 = t17 + j*P_ncols;
double *t31 = t20 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t32[k] = (t30[k]+t31[k]);
}
}
}
free(t17);
free(t15);
}
