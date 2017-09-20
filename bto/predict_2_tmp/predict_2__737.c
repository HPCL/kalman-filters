#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s1699 = 2;

int __s1698 = 2;

int __s1697 = 2;

double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t12 = t20;
double *t11 = t20;
double *t10 = t17;
double *t9 = t17;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s1697) {
// 2_1
int __m1697 = i + __s1697 > P_ncols ? P_ncols - i : __s1697;
double *t16 = t17 + i*P_ncols;
double *t15 = t8 + i*P_ncols;
for (j=0; j<__m1697; j+=1) {
// 2_2
double *t26 = t16 + j*P_ncols;
double *t25 = t15 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t26[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t36 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t26[l] += (t25[k]*t36[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s1698) {
// 4_1
int __m1698 = i + __s1698 > P_ncols ? P_ncols - i : __s1698;
double *t19 = t20 + i*P_ncols;
double *t18 = t10 + i*P_ncols;
for (j=0; j<__m1698; j+=1) {
// 4_2
double *t29 = t19 + j*P_ncols;
double *t28 = t18 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t46 = A + k*P_ncols;
t29[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t29[k] += (t28[l]*t46[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s1699) {
// 6_1
int __m1699 = i + __s1699 > P_ncols ? P_ncols - i : __s1699;
double *t23 = P + i*P_ncols;
double *t21 = t12 + i*P_ncols;
double *t22 = Q + i*P_ncols;
for (j=0; j<__m1699; j+=1) {
// 6_2
double *t33 = t23 + j*P_ncols;
double *t31 = t21 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t33[k] = (t31[k]+t32[k]);
}
}
}
free(t20);
free(t17);
}
