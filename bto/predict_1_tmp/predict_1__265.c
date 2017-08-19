#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m309;
int xh_ncols;
double *t18;
double *t17;
double *t19;
int __s308;
int A_nrows;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int __m309 = msg->__m309;
int xh_ncols = msg->xh_ncols;
double *t18 = msg->t18;
double *t17 = msg->t17;
double *t19 = msg->t19;
int __s308 = msg->__s308;
int A_nrows = msg->A_nrows;

for (j=0; j<A_nrows; j+=__s308) {
// 4_2
int __m308 = j + __s308 > A_nrows ? A_nrows - j : __s308;
double *t26 = t19 + j*xh_ncols;
double *t24 = t17 + j*xh_ncols;
double *t25 = t18 + j*xh_ncols;
for (k=0; k<__m308; k+=1) {
// 4_3
double *t34 = t26 + k*xh_ncols;
double *t32 = t24 + k*xh_ncols;
double *t33 = t25 + k*xh_ncols;
for (l=0; l<__m309; l+=1) {
// 4_4
t34[l] = (t32[l]+t33[l]);
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii,j,k,l;

int __s308 = 512;

int __s307 = 10;

int nparts__s309 = 8;
int __s309;
if (nparts__s309 > 1 && xh_ncols > nparts__s309) {
__s309 = xh_ncols/nparts__s309;
// this will fail if xh_ncols%nparts__s309+__s309 > nparts__s309
// which primarily effects small sizes
if (xh_ncols%nparts__s309)
++__s309;
}
else {
__s309 = xh_ncols;
nparts__s309 = 1;
}

double *t16 = malloc(sizeof(double)*xh_ncols*A_nrows);
double *t11 = t16;
double *t8 = t16;
double *t7 = t16;
for (i=0; i<xh_ncols; i+=__s307) {
// 2_1
int __m307 = i + __s307 > xh_ncols ? xh_ncols - i : __s307;
double *t15 = t16 + i;
double *t14 = xh + i;
for (j=0; j<A_nrows; j+=1) {
// 2_2
double *t22 = t15 + j*xh_ncols;
double *t21 = A + j*A_ncols;
for (__zr__ = 0; __zr__ < __m307; ++__zr__) t22[__zr__] = 0.0;
for (k=0; k<A_ncols; k+=1) {
// 2_3
double *t29 = t14 + k*xh_ncols;
for (l=0; l<__m307; l+=1) {
// 2_4
t22[l] += (t21[k]*t29[l]);
}
}
}
}
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s309);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s309);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s309,ii+=1) {
// 4_1
int __m309 = i + __s309 > xh_ncols ? xh_ncols - i : __s309;
double *t19 = xhn + i;
double *t17 = t11 + i;
double *t18 = Y + i;
predict1_0[disp].__m309 = __m309;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].t18 = t18;
predict1_0[disp].t17 = t17;
predict1_0[disp].t19 = t19;
predict1_0[disp].__s308 = __s308;
predict1_0[disp].A_nrows = A_nrows;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s309; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
free(t16);
}
