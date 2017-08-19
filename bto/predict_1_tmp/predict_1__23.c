#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,j,k;

double *t8 = malloc(sizeof(double)*A_nrows*xh_ncols);
for (i=0; i<A_nrows; i+=1) {
// 2_1
double *t7 = t8 + i*xh_ncols;
double *t6 = A + i*A_ncols;
for (__zr__ = 0; __zr__ < xh_ncols; ++__zr__) t7[__zr__] = 0.0;
for (j=0; j<A_ncols; j+=1) {
// 2_2
double *t14 = xh + j*xh_ncols;
for (k=0; k<xh_ncols; k+=1) {
// 2_3
t7[k] += (t6[j]*t14[k]);
}
}
}
for (i=0; i<A_nrows; i+=1) {
// 4_1
double *t11 = xhn + i*xh_ncols;
double *t9 = t8 + i*xh_ncols;
double *t10 = Y + i*xh_ncols;
for (j=0; j<xh_ncols; j+=1) {
// 4_2
t11[j] = (t9[j]+t10[j]);
}
}
free(t8);
}
