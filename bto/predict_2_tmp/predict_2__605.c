#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s1486 = 12;

double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t16;
double *t10 = A;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t12 = t13 + i*P_ncols;
double *t11 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t12[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t23 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t12[k] += (t11[j]*t23[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s1486) {
// 4_1
int __m1486 = i + __s1486 > P_ncols ? P_ncols - i : __s1486;
double *t15 = t16 + i;
double *t21 = t10 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t27 = t15 + j*P_ncols;
double *t26 = t13 + j*P_ncols;
for (k=0; k<__m1486; k+=1) {
// 4_3
double *t39 = t21 + k*P_ncols;
t27[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t27[k] += (t26[l]*t39[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t19 = P + i*P_ncols;
double *t17 = t9 + i*P_ncols;
double *t18 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t19[j] = (t17[j]+t18[j]);
}
}
free(t16);
free(t13);
}
