#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s981 = 2;

double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t8 = A;
for (i=0; i<P_ncols; i+=__s981) {
// 2_1
int __m981 = i + __s981 > P_ncols ? P_ncols - i : __s981;
double *t10 = t8 + i;
double *t11 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t22 = t13 + j*P_ncols;
double *t21 = t10 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t22[__zr__] = 0.0;
for (k=0; k<__m981; k+=1) {
// 2_3
double *t33 = t11 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t22[l] += (t21[k]*t33[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t15 = t16 + i*P_ncols;
double *t14 = t13 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t31 = A + j*P_ncols;
t15[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t15[j] += (t14[k]*t31[k]);
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t19 = P + i*P_ncols;
double *t17 = t16 + i*P_ncols;
double *t18 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t19[j] = (t17[j]+t18[j]);
}
}
free(t16);
free(t13);
}
