#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m404;
int xh_ncols;
double *t20;
double *t19;
double *t21;
int __s403;
int A_nrows;
} predict1_1_msg_t;

typedef struct { 
int __m402;
int xh_ncols;
int A_ncols;
double *t17;
int A_nrows;
double *t16;
double *A;
int __s401;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int __m402 = msg->__m402;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *t17 = msg->t17;
int A_nrows = msg->A_nrows;
double *t16 = msg->t16;
double *A = msg->A;
int __s401 = msg->__s401;

for (j=0; j<A_ncols; j+=__s401) {
// 2_2
int __m401 = j + __s401 > A_ncols ? A_ncols - j : __s401;
double *t23 = A + j;
double *t24 = t16 + j*xh_ncols;
for (k=0; k<A_nrows; k+=1) {
// 2_3
double *t32 = t17 + k*xh_ncols;
double *t31 = t23 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m402; ++__zr__) t32[__zr__] = 0.0;
for (l=0; l<__m401; l+=1) {
// 2_4
double *t39 = t24 + l*xh_ncols;
for (p=0; p<__m402; p+=1) {
// 2_5
t32[p] += (t31[l]*t39[p]);
}
}
}
}
return NULL;
}


void *predict1_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict1_1_msg_t *msg = (predict1_1_msg_t*)mesg;
int __m404 = msg->__m404;
int xh_ncols = msg->xh_ncols;
double *t20 = msg->t20;
double *t19 = msg->t19;
double *t21 = msg->t21;
int __s403 = msg->__s403;
int A_nrows = msg->A_nrows;

for (j=0; j<A_nrows; j+=__s403) {
// 4_2
int __m403 = j + __s403 > A_nrows ? A_nrows - j : __s403;
double *t29 = t21 + j*xh_ncols;
double *t27 = t19 + j*xh_ncols;
double *t28 = t20 + j*xh_ncols;
for (k=0; k<__m403; k+=1) {
// 4_3
double *t36 = t29 + k*xh_ncols;
double *t34 = t27 + k*xh_ncols;
double *t35 = t28 + k*xh_ncols;
for (l=0; l<__m404; l+=1) {
// 4_4
t36[l] = (t34[l]+t35[l]);
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii;

int __s403 = 512;

int __s401 = 512;

int nparts__s402 = 10;
int __s402;
if (nparts__s402 > 1 && xh_ncols > nparts__s402) {
__s402 = xh_ncols/nparts__s402;
// this will fail if xh_ncols%nparts__s402+__s402 > nparts__s402
// which primarily effects small sizes
if (xh_ncols%nparts__s402)
++__s402;
}
else {
__s402 = xh_ncols;
nparts__s402 = 1;
}

int nparts__s404 = 8;
int __s404;
if (nparts__s404 > 1 && xh_ncols > nparts__s404) {
__s404 = xh_ncols/nparts__s404;
// this will fail if xh_ncols%nparts__s404+__s404 > nparts__s404
// which primarily effects small sizes
if (xh_ncols%nparts__s404)
++__s404;
}
else {
__s404 = xh_ncols;
nparts__s404 = 1;
}

double *t18 = malloc(sizeof(double)*xh_ncols*A_nrows);
double *t13 = t18;
double *t10 = t18;
double *t9 = t18;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s402);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s402);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s402,ii+=1) {
// 2_1
int __m402 = i + __s402 > xh_ncols ? xh_ncols - i : __s402;
double *t17 = t18 + i;
double *t16 = xh + i;
predict1_0[disp].__m402 = __m402;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t17 = t17;
predict1_0[disp].A_nrows = A_nrows;
predict1_0[disp].t16 = t16;
predict1_0[disp].A = A;
predict1_0[disp].__s401 = __s401;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s402; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
predict1_1_msg_t *predict1_1 = malloc(sizeof(predict1_1_msg_t)*nparts__s404);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s404);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s404,ii+=1) {
// 4_1
int __m404 = i + __s404 > xh_ncols ? xh_ncols - i : __s404;
double *t21 = xhn + i;
double *t19 = t13 + i;
double *t20 = Y + i;
predict1_1[disp].__m404 = __m404;
predict1_1[disp].xh_ncols = xh_ncols;
predict1_1[disp].t20 = t20;
predict1_1[disp].t19 = t19;
predict1_1[disp].t21 = t21;
predict1_1[disp].__s403 = __s403;
predict1_1[disp].A_nrows = A_nrows;

pthread_create(&threads_1[disp], NULL, predict1_body_1, (void *)(predict1_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s404; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict1_1);
free(t18);
}
