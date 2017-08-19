#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m220;
int xh_ncols;
double *t10;
int A_ncols;
double *A;
double *t11;
int __s219;
int A_nrows;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int __m220 = msg->__m220;
int xh_ncols = msg->xh_ncols;
double *t10 = msg->t10;
int A_ncols = msg->A_ncols;
double *A = msg->A;
double *t11 = msg->t11;
int __s219 = msg->__s219;
int A_nrows = msg->A_nrows;

for (j=0; j<A_nrows; j+=__s219) {
// 2_2
int __m219 = j + __s219 > A_nrows ? A_nrows - j : __s219;
double *t18 = t11 + j*xh_ncols;
double *t17 = A + j*A_ncols;
for (k=0; k<__m219; k+=1) {
// 2_3
double *t25 = t18 + k*xh_ncols;
double *t24 = t17 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m220; ++__zr__) t25[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t28 = t10 + l*xh_ncols;
for (p=0; p<__m220; p+=1) {
// 2_5
t25[p] += (t24[l]*t28[p]);
}
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii,j;

int __s219 = 512;

int nparts__s220 = 8;
int __s220;
if (nparts__s220 > 1 && xh_ncols > nparts__s220) {
__s220 = xh_ncols/nparts__s220;
// this will fail if xh_ncols%nparts__s220+__s220 > nparts__s220
// which primarily effects small sizes
if (xh_ncols%nparts__s220)
++__s220;
}
else {
__s220 = xh_ncols;
nparts__s220 = 1;
}

double *t12 = malloc(sizeof(double)*xh_ncols*A_nrows);
double *t7 = t12;
double *t9 = t12;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s220);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s220);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s220,ii+=1) {
// 2_1
int __m220 = i + __s220 > xh_ncols ? xh_ncols - i : __s220;
double *t11 = t12 + i;
double *t10 = xh + i;
predict1_0[disp].__m220 = __m220;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].t10 = t10;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].A = A;
predict1_0[disp].t11 = t11;
predict1_0[disp].__s219 = __s219;
predict1_0[disp].A_nrows = A_nrows;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s220; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
for (i=0; i<A_nrows; i+=1) {
// 4_1
double *t15 = xhn + i*xh_ncols;
double *t13 = t7 + i*xh_ncols;
double *t14 = Y + i*xh_ncols;
for (j=0; j<xh_ncols; j+=1) {
// 4_2
t15[j] = (t13[j]+t14[j]);
}
}
free(t12);
}
