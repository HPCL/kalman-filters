#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,j,k,l;

int __s394 = 8;

int __s393 = 10;

double *t14 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t8 = t14;
for (i=0; i<A_ncols; i+=__s393) {
// 2_1
int __m393 = i + __s393 > A_ncols ? A_ncols - i : __s393;
double *t11 = A + i;
double *t12 = xh + i*xh_ncols;
for (j=0; j<A_nrows; j+=1) {
// 2_2
double *t20 = t14 + j*xh_ncols;
double *t19 = t11 + j*A_ncols;
for (__zr__ = 0; __zr__ < xh_ncols; ++__zr__) t20[__zr__] = 0.0;
for (k=0; k<__m393; k+=1) {
// 2_3
double *t27 = t12 + k*xh_ncols;
for (l=0; l<xh_ncols; l+=1) {
// 2_4
t20[l] += (t19[k]*t27[l]);
}
}
}
}
for (i=0; i<A_nrows; i+=__s394) {
// 4_1
int __m394 = i + __s394 > A_nrows ? A_nrows - i : __s394;
double *t17 = xhn + i*xh_ncols;
double *t15 = t8 + i*xh_ncols;
double *t16 = Y + i*xh_ncols;
for (j=0; j<__m394; j+=1) {
// 4_2
double *t24 = t17 + j*xh_ncols;
double *t22 = t15 + j*xh_ncols;
double *t23 = t16 + j*xh_ncols;
for (k=0; k<xh_ncols; k+=1) {
// 4_3
t24[k] = (t22[k]+t23[k]);
}
}
}
free(t14);
}
