#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int A_nrows;
double *t18;
double *t17;
double *t19;
int __s425;
int __m426;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_nrows = msg->A_nrows;
double *t18 = msg->t18;
double *t17 = msg->t17;
double *t19 = msg->t19;
int __s425 = msg->__s425;
int __m426 = msg->__m426;

for (j=0; j<__m426; j+=__s425) {
// 4_2
int __m425 = j + __s425 > __m426 ? __m426 - j : __s425;
double *t26 = t19 + j;
double *t24 = t17 + j;
double *t25 = t18 + j;
for (k=0; k<A_nrows; k+=1) {
// 4_3
double *t34 = t26 + k*xh_ncols;
double *t32 = t24 + k*xh_ncols;
double *t33 = t25 + k*xh_ncols;
for (l=0; l<__m425; l+=1) {
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

int __s425 = 504;

int __s424 = 8;

int nparts__s426 = 8;
int __s426;
if (nparts__s426 > 1 && xh_ncols > nparts__s426) {
__s426 = xh_ncols/nparts__s426;
// this will fail if xh_ncols%nparts__s426+__s426 > nparts__s426
// which primarily effects small sizes
if (xh_ncols%nparts__s426)
++__s426;
}
else {
__s426 = xh_ncols;
nparts__s426 = 1;
}

double *t16 = malloc(sizeof(double)*xh_ncols*A_nrows);
double *t11 = t16;
double *t8 = t16;
double *t7 = t16;
for (i=0; i<xh_ncols; i+=__s424) {
// 2_1
int __m424 = i + __s424 > xh_ncols ? xh_ncols - i : __s424;
double *t15 = t16 + i;
double *t14 = xh + i;
for (j=0; j<A_nrows; j+=1) {
// 2_2
double *t22 = t15 + j*xh_ncols;
double *t21 = A + j*A_ncols;
for (__zr__ = 0; __zr__ < __m424; ++__zr__) t22[__zr__] = 0.0;
for (k=0; k<A_ncols; k+=1) {
// 2_3
double *t29 = t14 + k*xh_ncols;
for (l=0; l<__m424; l+=1) {
// 2_4
t22[l] += (t21[k]*t29[l]);
}
}
}
}
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s426);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s426);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s426,ii+=1) {
// 4_1
int __m426 = i + __s426 > xh_ncols ? xh_ncols - i : __s426;
double *t19 = xhn + i;
double *t17 = t11 + i;
double *t18 = Y + i;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_nrows = A_nrows;
predict1_0[disp].t18 = t18;
predict1_0[disp].t17 = t17;
predict1_0[disp].t19 = t19;
predict1_0[disp].__s425 = __s425;
predict1_0[disp].__m426 = __m426;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s426; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
free(t16);
}
