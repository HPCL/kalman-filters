#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,j,k;

int __s684 = 12;

double *t11 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t6 = t11;
for (i=0; i<A_nrows; i+=1) {
// 2_1
double *t10 = t11 + i*xh_ncols;
double *t9 = A + i*A_ncols;
for (__zr__ = 0; __zr__ < xh_ncols; ++__zr__) t10[__zr__] = 0.0;
for (j=0; j<A_ncols; j+=1) {
// 2_2
double *t17 = xh + j*xh_ncols;
for (k=0; k<xh_ncols; k+=1) {
// 2_3
t10[k] += (t9[j]*t17[k]);
}
}
}
for (i=0; i<A_nrows; i+=__s684) {
// 4_1
int __m684 = i + __s684 > A_nrows ? A_nrows - i : __s684;
double *t14 = xhn + i*xh_ncols;
double *t12 = t6 + i*xh_ncols;
double *t13 = Y + i*xh_ncols;
for (j=0; j<__m684; j+=1) {
// 4_2
double *t22 = t14 + j*xh_ncols;
double *t20 = t12 + j*xh_ncols;
double *t21 = t13 + j*xh_ncols;
for (k=0; k<xh_ncols; k+=1) {
// 4_3
t22[k] = (t20[k]+t21[k]);
}
}
}
free(t11);
}
