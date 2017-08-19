#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,j,k,l;

int __s622 = 4;

int __s621 = 4;

double *t13 = malloc(sizeof(double)*xh_ncols*A_nrows);
double *t8 = t13;
double *t7 = t13;
for (i=0; i<xh_ncols; i+=__s621) {
// 2_1
int __m621 = i + __s621 > xh_ncols ? xh_ncols - i : __s621;
double *t12 = t13 + i;
double *t11 = xh + i;
for (j=0; j<A_nrows; j+=1) {
// 2_2
double *t19 = t12 + j*xh_ncols;
double *t18 = A + j*A_ncols;
for (__zr__ = 0; __zr__ < __m621; ++__zr__) t19[__zr__] = 0.0;
for (k=0; k<A_ncols; k+=1) {
// 2_3
double *t26 = t11 + k*xh_ncols;
for (l=0; l<__m621; l+=1) {
// 2_4
t19[l] += (t18[k]*t26[l]);
}
}
}
}
for (i=0; i<xh_ncols; i+=__s622) {
// 4_1
int __m622 = i + __s622 > xh_ncols ? xh_ncols - i : __s622;
double *t16 = xhn + i;
double *t14 = t8 + i;
double *t15 = Y + i;
for (j=0; j<A_nrows; j+=1) {
// 4_2
double *t23 = t16 + j*xh_ncols;
double *t21 = t14 + j*xh_ncols;
double *t22 = t15 + j*xh_ncols;
for (k=0; k<__m622; k+=1) {
// 4_3
t23[k] = (t21[k]+t22[k]);
}
}
}
free(t13);
}
