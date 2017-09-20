#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s1306 = 2;

double *t15 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t12 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t15;
double *t8 = t12;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t11 = t12 + i*P_ncols;
double *t10 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t11[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t21 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t11[k] += (t10[j]*t21[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s1306) {
// 4_1
int __m1306 = i + __s1306 > P_ncols ? P_ncols - i : __s1306;
double *t14 = t15 + i*P_ncols;
double *t13 = t8 + i*P_ncols;
for (j=0; j<__m1306; j+=1) {
// 4_2
double *t25 = t14 + j*P_ncols;
double *t24 = t13 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t37 = A + k*P_ncols;
t25[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t25[k] += (t24[l]*t37[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t18 = P + i*P_ncols;
double *t16 = t9 + i*P_ncols;
double *t17 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t18[j] = (t16[j]+t17[j]);
}
}
free(t15);
free(t12);
}
