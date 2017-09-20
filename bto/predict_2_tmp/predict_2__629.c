#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s1514 = 12;

double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t10 = A;
double *t8 = t13;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t12 = t13 + i*P_ncols;
double *t11 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t12[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t24 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t12[k] += (t11[j]*t24[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s1514) {
// 4_1
int __m1514 = i + __s1514 > P_ncols ? P_ncols - i : __s1514;
double *t14 = t8 + i;
double *t22 = t10 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t28 = t17 + j*P_ncols;
double *t27 = t14 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t40 = t22 + k*P_ncols;
t28[k] = 0.0;
for (l=0; l<__m1514; l+=1) {
// 4_4
t28[k] += (t27[l]*t40[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t20 = P + i*P_ncols;
double *t18 = t17 + i*P_ncols;
double *t19 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t20[j] = (t18[j]+t19[j]);
}
}
free(t17);
free(t13);
}
