#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k;

int __s394 = 2;

double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t8 = t16;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t12 = t13 + i*P_ncols;
double *t11 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t12[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t22 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t12[k] += (t11[j]*t22[k]);
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t15 = t16 + i*P_ncols;
double *t14 = t13 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t32 = A + j*P_ncols;
t15[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t15[j] += (t14[k]*t32[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s394) {
// 6_1
int __m394 = i + __s394 > P_ncols ? P_ncols - i : __s394;
double *t19 = P + i*P_ncols;
double *t17 = t8 + i*P_ncols;
double *t18 = Q + i*P_ncols;
for (j=0; j<__m394; j+=1) {
// 6_2
double *t30 = t19 + j*P_ncols;
double *t28 = t17 + j*P_ncols;
double *t29 = t18 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t30[k] = (t28[k]+t29[k]);
}
}
}
free(t16);
free(t13);
}
