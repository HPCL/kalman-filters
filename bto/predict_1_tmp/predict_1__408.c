#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int __m474;
int A_nrows;
double *t20;
double *t21;
int __s475;
int A_ncols;
double *A;
double *t16;
int __s473;
int __s474;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int __m474 = msg->__m474;
int A_nrows = msg->A_nrows;
double *t20 = msg->t20;
double *t21 = msg->t21;
int __s475 = msg->__s475;
int A_ncols = msg->A_ncols;
double *A = msg->A;
double *t16 = msg->t16;
int __s473 = msg->__s473;
int __s474 = msg->__s474;

double *t17 = malloc(sizeof(double)*__s474*A_nrows);
for (j=0; j<__m474; j+=__s473) {
// 2_2
int __m473 = j + __s473 > __m474 ? __m474 - j : __s473;
double *t24 = t17 + j;
double *t23 = t16 + j;
for (k=0; k<A_nrows; k+=1) {
// 2_3
double *t31 = t24 + k*__m474;
double *t30 = A + k*A_ncols;
for (__zr__ = 0; __zr__ < __m473; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = t23 + l*xh_ncols;
for (p=0; p<__m473; p+=1) {
// 2_5
t31[p] += (t30[l]*t38[p]);
}
}
}
}
for (j=0; j<__m474; j+=__s475) {
// 4_2
int __m475 = j + __s475 > __m474 ? __m474 - j : __s475;
double *t28 = t21 + j;
double *t26 = t17 + j;
double *t27 = t20 + j;
for (k=0; k<A_nrows; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t26 + k*__m474;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<__m475; l+=1) {
// 4_4
t35[l] = (t33[l]+t34[l]);
}
}
}
free(t17);
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii;

int __s475 = 512;

int __s473 = 512;

int nparts__s474 = 6;
int __s474;
if (nparts__s474 > 1 && xh_ncols > nparts__s474) {
__s474 = xh_ncols/nparts__s474;
// this will fail if xh_ncols%nparts__s474+__s474 > nparts__s474
// which primarily effects small sizes
if (xh_ncols%nparts__s474)
++__s474;
}
else {
__s474 = xh_ncols;
nparts__s474 = 1;
}

predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s474);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s474);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s474,ii+=1) {
// 2_1
int __m474 = i + __s474 > xh_ncols ? xh_ncols - i : __s474;
double *t21 = xhn + i;
double *t16 = xh + i;
double *t20 = Y + i;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].__m474 = __m474;
predict1_0[disp].A_nrows = A_nrows;
predict1_0[disp].t20 = t20;
predict1_0[disp].t21 = t21;
predict1_0[disp].__s475 = __s475;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].A = A;
predict1_0[disp].t16 = t16;
predict1_0[disp].__s473 = __s473;
predict1_0[disp].__s474 = __s474;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s474; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
}
