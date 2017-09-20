#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s1567 = 2;

int __s1566 = 12;

double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t20;
double *t10 = A;
double *t8 = t16;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t15 = t16 + i*P_ncols;
double *t14 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t15[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t27 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t15[k] += (t14[j]*t27[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s1566) {
// 4_1
int __m1566 = i + __s1566 > P_ncols ? P_ncols - i : __s1566;
double *t17 = t8 + i;
double *t25 = t10 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t31 = t20 + j*P_ncols;
double *t30 = t17 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t47 = t25 + k*P_ncols;
t31[k] = 0.0;
for (l=0; l<__m1566; l+=1) {
// 4_4
t31[k] += (t30[l]*t47[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s1567) {
// 6_1
int __m1567 = i + __s1567 > P_ncols ? P_ncols - i : __s1567;
double *t23 = P + i;
double *t21 = t11 + i;
double *t22 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t35 = t23 + j*P_ncols;
double *t33 = t21 + j*P_ncols;
double *t34 = t22 + j*P_ncols;
for (k=0; k<__m1567; k+=1) {
// 6_3
t35[k] = (t33[k]+t34[k]);
}
}
}
free(t20);
free(t16);
}
