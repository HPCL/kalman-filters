#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m389;
int xh_ncols;
int A_ncols;
double *t14;
int A_nrows;
double *t13;
double *A;
int __s388;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int __m389 = msg->__m389;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *t14 = msg->t14;
int A_nrows = msg->A_nrows;
double *t13 = msg->t13;
double *A = msg->A;
int __s388 = msg->__s388;

for (j=0; j<A_ncols; j+=__s388) {
// 2_2
int __m388 = j + __s388 > A_ncols ? A_ncols - j : __s388;
double *t20 = A + j;
double *t21 = t13 + j*xh_ncols;
for (k=0; k<A_nrows; k+=1) {
// 2_3
double *t29 = t14 + k*xh_ncols;
double *t28 = t20 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m389; ++__zr__) t29[__zr__] = 0.0;
for (l=0; l<__m388; l+=1) {
// 2_4
double *t36 = t21 + l*xh_ncols;
for (p=0; p<__m389; p+=1) {
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

int __s390 = 8;

int __s388 = 504;

int nparts__s389 = 10;
int __s389;
if (nparts__s389 > 1 && xh_ncols > nparts__s389) {
__s389 = xh_ncols/nparts__s389;
// this will fail if xh_ncols%nparts__s389+__s389 > nparts__s389
// which primarily effects small sizes
if (xh_ncols%nparts__s389)
++__s389;
}
else {
__s389 = xh_ncols;
nparts__s389 = 1;
}

double *t15 = malloc(sizeof(double)*xh_ncols*A_nrows);
double *t10 = t15;
double *t9 = t15;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s389);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s389);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s389,ii+=1) {
// 2_1
int __m389 = i + __s389 > xh_ncols ? xh_ncols - i : __s389;
double *t14 = t15 + i;
double *t13 = xh + i;
predict1_0[disp].__m389 = __m389;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t14 = t14;
predict1_0[disp].A_nrows = A_nrows;
predict1_0[disp].t13 = t13;
predict1_0[disp].A = A;
predict1_0[disp].__s388 = __s388;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s389; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
for (i=0; i<A_nrows; i+=__s390) {
// 4_1
int __m390 = i + __s390 > A_nrows ? A_nrows - i : __s390;
double *t18 = xhn + i*xh_ncols;
double *t16 = t10 + i*xh_ncols;
double *t17 = Y + i*xh_ncols;
for (j=0; j<__m390; j+=1) {
// 4_2
double *t26 = t18 + j*xh_ncols;
double *t24 = t16 + j*xh_ncols;
double *t25 = t17 + j*xh_ncols;
for (k=0; k<xh_ncols; k+=1) {
// 4_3
t26[k] = (t24[k]+t25[k]);
}
}
}
free(t15);
}
