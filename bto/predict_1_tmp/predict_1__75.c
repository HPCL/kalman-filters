#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,j,k,l;

int __s108 = 8;

double *t19 = malloc(sizeof(double)*xh_ncols);
for (i=0; i<A_nrows; i+=__s108) {
// 2_1
int __m108 = i + __s108 > A_nrows ? A_nrows - i : __s108;
double *t16 = xhn + i*xh_ncols;
double *t11 = A + i*A_ncols;
double *t15 = Y + i*xh_ncols;
for (j=0; j<__m108; j+=1) {
// 2_2
double *t23 = t16 + j*xh_ncols;
double *t18 = t11 + j*A_ncols;
double *t22 = t15 + j*xh_ncols;
for (__zr__ = 0; __zr__ < xh_ncols; ++__zr__) t19[__zr__] = 0.0;
for (k=0; k<A_ncols; k+=1) {
// 2_3
double *t26 = xh + k*xh_ncols;
for (l=0; l<xh_ncols; l+=1) {
// 2_4
t19[l] += (t18[k]*t26[l]);
}
}
for (k=0; k<xh_ncols; k+=1) {
// 4_3
t23[k] = (t19[k]+t22[k]);
}
}
}
free(t19);
}
