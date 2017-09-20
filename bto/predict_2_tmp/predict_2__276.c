#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,j,k,l;

int __s799 = 2;

int __s798 = 2;

int __s797 = 2;

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t21;
double *t11 = t21;
double *t9 = t18;
double *t8 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s797) {
// 2_1
int __m797 = i + __s797 > P_ncols ? P_ncols - i : __s797;
double *t17 = t18 + i*P_ncols;
double *t16 = t8 + i*P_ncols;
for (j=0; j<__m797; j+=1) {
// 2_2
double *t28 = t17 + j*P_ncols;
double *t27 = t16 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t28[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t38 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t28[l] += (t27[k]*t38[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s798) {
// 4_1
int __m798 = i + __s798 > P_ncols ? P_ncols - i : __s798;
double *t20 = t21 + i;
double *t26 = t12 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t31 = t20 + j*P_ncols;
double *t30 = t9 + j*P_ncols;
for (k=0; k<__m798; k+=1) {
// 4_3
double *t48 = t26 + k*P_ncols;
t31[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t31[k] += (t30[l]*t48[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s799) {
// 6_1
int __m799 = i + __s799 > P_ncols ? P_ncols - i : __s799;
double *t24 = P + i*P_ncols;
double *t22 = t13 + i*P_ncols;
double *t23 = Q + i*P_ncols;
for (j=0; j<__m799; j+=1) {
// 6_2
double *t35 = t24 + j*P_ncols;
double *t33 = t22 + j*P_ncols;
double *t34 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t35[k] = (t33[k]+t34[k]);
}
}
}
free(t21);
free(t18);
}
