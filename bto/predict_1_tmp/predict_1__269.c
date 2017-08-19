#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int A_ncols;
double *A;
int A_nrows;
double *t13;
double *t14;
int __s315;
int __m316;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *A = msg->A;
int A_nrows = msg->A_nrows;
double *t13 = msg->t13;
double *t14 = msg->t14;
int __s315 = msg->__s315;
int __m316 = msg->__m316;

for (j=0; j<__m316; j+=__s315) {
// 2_2
int __m315 = j + __s315 > __m316 ? __m316 - j : __s315;
double *t21 = t14 + j;
double *t20 = t13 + j;
for (k=0; k<A_nrows; k+=1) {
// 2_3
double *t28 = t21 + k*xh_ncols;
double *t27 = A + k*A_ncols;
for (__zr__ = 0; __zr__ < __m315; ++__zr__) t28[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t35 = t20 + l*xh_ncols;
for (p=0; p<__m315; p+=1) {
// 2_5
t28[p] += (t27[l]*t35[p]);
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

int __s317 = 8;

int __s315 = 512;

int nparts__s316 = 10;
int __s316;
if (nparts__s316 > 1 && xh_ncols > nparts__s316) {
__s316 = xh_ncols/nparts__s316;
// this will fail if xh_ncols%nparts__s316+__s316 > nparts__s316
// which primarily effects small sizes
if (xh_ncols%nparts__s316)
++__s316;
}
else {
__s316 = xh_ncols;
nparts__s316 = 1;
}

double *t15 = malloc(sizeof(double)*xh_ncols*A_nrows);
double *t10 = t15;
double *t7 = t15;
double *t9 = t15;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s316);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s316);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s316,ii+=1) {
// 2_1
int __m316 = i + __s316 > xh_ncols ? xh_ncols - i : __s316;
double *t14 = t15 + i;
double *t13 = xh + i;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].A = A;
predict1_0[disp].A_nrows = A_nrows;
predict1_0[disp].t13 = t13;
predict1_0[disp].t14 = t14;
predict1_0[disp].__s315 = __s315;
predict1_0[disp].__m316 = __m316;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s316; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
for (i=0; i<A_nrows; i+=__s317) {
// 4_1
int __m317 = i + __s317 > A_nrows ? A_nrows - i : __s317;
double *t18 = xhn + i*xh_ncols;
double *t16 = t10 + i*xh_ncols;
double *t17 = Y + i*xh_ncols;
for (j=0; j<__m317; j+=1) {
// 4_2
double *t25 = t18 + j*xh_ncols;
double *t23 = t16 + j*xh_ncols;
double *t24 = t17 + j*xh_ncols;
for (k=0; k<xh_ncols; k+=1) {
// 4_3
t25[k] = (t23[k]+t24[k]);
}
}
}
free(t15);
}
