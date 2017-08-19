#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int A_nrows;
double *t20;
double *t19;
double *t21;
int __s382;
int __m383;
} predict1_1_msg_t;

typedef struct { 
int xh_ncols;
int A_ncols;
double *A;
int A_nrows;
double *t16;
double *t17;
int __s380;
int __m381;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *A = msg->A;
int A_nrows = msg->A_nrows;
double *t16 = msg->t16;
double *t17 = msg->t17;
int __s380 = msg->__s380;
int __m381 = msg->__m381;

for (j=0; j<__m381; j+=__s380) {
// 2_2
int __m380 = j + __s380 > __m381 ? __m381 - j : __s380;
double *t24 = t17 + j;
double *t23 = t16 + j;
for (k=0; k<A_nrows; k+=1) {
// 2_3
double *t31 = t24 + k*xh_ncols;
double *t30 = A + k*A_ncols;
for (__zr__ = 0; __zr__ < __m380; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = t23 + l*xh_ncols;
for (p=0; p<__m380; p+=1) {
// 2_5
t31[p] += (t30[l]*t38[p]);
}
}
}
}
return NULL;
}


void *predict1_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict1_1_msg_t *msg = (predict1_1_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_nrows = msg->A_nrows;
double *t20 = msg->t20;
double *t19 = msg->t19;
double *t21 = msg->t21;
int __s382 = msg->__s382;
int __m383 = msg->__m383;

for (j=0; j<__m383; j+=__s382) {
// 4_2
int __m382 = j + __s382 > __m383 ? __m383 - j : __s382;
double *t28 = t21 + j;
double *t26 = t19 + j;
double *t27 = t20 + j;
for (k=0; k<A_nrows; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t26 + k*xh_ncols;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<__m382; l+=1) {
// 4_4
t35[l] = (t33[l]+t34[l]);
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii;

int __s382 = 512;

int __s380 = 512;

int nparts__s383 = 8;
int __s383;
if (nparts__s383 > 1 && xh_ncols > nparts__s383) {
__s383 = xh_ncols/nparts__s383;
// this will fail if xh_ncols%nparts__s383+__s383 > nparts__s383
// which primarily effects small sizes
if (xh_ncols%nparts__s383)
++__s383;
}
else {
__s383 = xh_ncols;
nparts__s383 = 1;
}

int nparts__s381 = 8;
int __s381;
if (nparts__s381 > 1 && xh_ncols > nparts__s381) {
__s381 = xh_ncols/nparts__s381;
// this will fail if xh_ncols%nparts__s381+__s381 > nparts__s381
// which primarily effects small sizes
if (xh_ncols%nparts__s381)
++__s381;
}
else {
__s381 = xh_ncols;
nparts__s381 = 1;
}

double *t18 = malloc(sizeof(double)*xh_ncols*A_nrows);
double *t13 = t18;
double *t10 = t18;
double *t7 = t18;
double *t9 = t18;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s381);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s381);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s381,ii+=1) {
// 2_1
int __m381 = i + __s381 > xh_ncols ? xh_ncols - i : __s381;
double *t17 = t18 + i;
double *t16 = xh + i;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].A = A;
predict1_0[disp].A_nrows = A_nrows;
predict1_0[disp].t16 = t16;
predict1_0[disp].t17 = t17;
predict1_0[disp].__s380 = __s380;
predict1_0[disp].__m381 = __m381;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s381; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
predict1_1_msg_t *predict1_1 = malloc(sizeof(predict1_1_msg_t)*nparts__s383);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s383);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s383,ii+=1) {
// 4_1
int __m383 = i + __s383 > xh_ncols ? xh_ncols - i : __s383;
double *t21 = xhn + i;
double *t19 = t13 + i;
double *t20 = Y + i;
predict1_1[disp].xh_ncols = xh_ncols;
predict1_1[disp].A_nrows = A_nrows;
predict1_1[disp].t20 = t20;
predict1_1[disp].t19 = t19;
predict1_1[disp].t21 = t21;
predict1_1[disp].__s382 = __s382;
predict1_1[disp].__m383 = __m383;

pthread_create(&threads_1[disp], NULL, predict1_body_1, (void *)(predict1_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s383; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict1_1);
free(t18);
}
