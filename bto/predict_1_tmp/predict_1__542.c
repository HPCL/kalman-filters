#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,j,k,l;

int __s628 = 2;

double *t10 = malloc(sizeof(double)*xh_ncols*A_nrows);
double *t7 = t10;
for (i=0; i<xh_ncols; i+=__s628) {
// 2_1
int __m628 = i + __s628 > xh_ncols ? xh_ncols - i : __s628;
double *t9 = t10 + i;
double *t8 = xh + i;
for (j=0; j<A_nrows; j+=1) {
// 2_2
double *t16 = t9 + j*xh_ncols;
double *t15 = A + j*A_ncols;
for (__zr__ = 0; __zr__ < __m628; ++__zr__) t16[__zr__] = 0.0;
for (k=0; k<A_ncols; k+=1) {
// 2_3
double *t23 = t8 + k*xh_ncols;
for (l=0; l<__m628; l+=1) {
// 2_4
t16[l] += (t15[k]*t23[l]);
}
}
}
}
for (i=0; i<A_nrows; i+=1) {
// 4_1
double *t13 = xhn + i*xh_ncols;
double *t11 = t7 + i*xh_ncols;
double *t12 = Y + i*xh_ncols;
for (j=0; j<xh_ncols; j+=1) {
// 4_2
t13[j] = (t11[j]+t12[j]);
}
}
free(t10);
}
