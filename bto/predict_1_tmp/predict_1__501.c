#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int __m580;
int A_ncols;
double *t13;
int A_nrows;
double *t14;
double *t15;
int __s579;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int __m580 = msg->__m580;
int A_ncols = msg->A_ncols;
double *t13 = msg->t13;
int A_nrows = msg->A_nrows;
double *t14 = msg->t14;
double *t15 = msg->t15;
int __s579 = msg->__s579;

for (j=0; j<xh_ncols; j+=__s579) {
// 2_2
int __m579 = j + __s579 > xh_ncols ? xh_ncols - j : __s579;
double *t22 = t15 + j;
double *t21 = t14 + j;
for (k=0; k<A_nrows; k+=1) {
// 2_3
double *t29 = t22 + k*__m579;
double *t28 = t13 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m579; ++__zr__) t29[__zr__] = 0.0;
for (l=0; l<__m580; l+=1) {
// 2_4
double *t36 = t21 + l*xh_ncols;
for (p=0; p<__m579; p+=1) {
// 2_5
t29[p] += (t28[l]*t36[p]);
}
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii,j,k;

int __s581 = 4;

int __s579 = 496;

int nparts__s580 = 4;
int __s580;
if (nparts__s580 > 1 && A_ncols > nparts__s580) {
__s580 = A_ncols/nparts__s580;
// this will fail if A_ncols%nparts__s580+__s580 > nparts__s580
// which primarily effects small sizes
if (A_ncols%nparts__s580)
++__s580;
}
else {
__s580 = A_ncols;
nparts__s580 = 1;
}

double *t16 = malloc(sizeof(double)*nparts__s580*xh_ncols*A_nrows);
double *t10 = t16;
double *t7 = t16;
double *t42 = t16;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s580);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s580);
disp = 0;
for (i=0,ii=0; i<A_ncols; i+=__s580,ii+=1) {
// 2_1
int __m580 = i + __s580 > A_ncols ? A_ncols - i : __s580;
double *t15 = t16 + ii*xh_ncols*A_nrows;
double *t13 = A + i;
double *t14 = xh + i*xh_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].__m580 = __m580;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t13 = t13;
predict1_0[disp].A_nrows = A_nrows;
predict1_0[disp].t14 = t14;
predict1_0[disp].t15 = t15;
predict1_0[disp].__s579 = __s579;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s580; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<A_ncols; i+=__s580,ii+=1) {
// 2_1
int __m580 = i + __s580 > A_ncols ? A_ncols - i : __s580;
if ((ii == 0)) {
for (__j = 0; __j < xh_ncols; __j+=__s579) {
int __m579 = __j + __s579 > xh_ncols ? xh_ncols - __j : __s579;
for (__k = 0; __k < A_nrows; __k+=1) {
for (__l = 0; __l < __m579; __l+=1) {
t42[__j+__k*xh_ncols+__l] = t16[ii*xh_ncols*A_nrows+__j+__k*__m579+__l];
}
}
}
} else {
for (__j = 0; __j < xh_ncols; __j+=__s579) {
int __m579 = __j + __s579 > xh_ncols ? xh_ncols - __j : __s579;
for (__k = 0; __k < A_nrows; __k+=1) {
for (__l = 0; __l < __m579; __l+=1) {
t42[__j+__k*xh_ncols+__l] += t16[ii*xh_ncols*A_nrows+__j+__k*__m579+__l];
}
}
}
}
}
}

for (i=0; i<xh_ncols; i+=__s581) {
// 4_1
int __m581 = i + __s581 > xh_ncols ? xh_ncols - i : __s581;
double *t19 = xhn + i;
double *t17 = t10 + i;
double *t18 = Y + i;
for (j=0; j<A_nrows; j+=1) {
// 4_2
double *t26 = t19 + j*xh_ncols;
double *t24 = t17 + j*xh_ncols;
double *t25 = t18 + j*xh_ncols;
for (k=0; k<__m581; k+=1) {
// 4_3
t26[k] = (t24[k]+t25[k]);
}
}
}
free(t16);
}
