#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int __m489;
double *t20;
double *t21;
int __s490;
int A_ncols;
double *t16;
double *xh;
int __s488;
int __s489;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int __m489 = msg->__m489;
double *t20 = msg->t20;
double *t21 = msg->t21;
int __s490 = msg->__s490;
int A_ncols = msg->A_ncols;
double *t16 = msg->t16;
double *xh = msg->xh;
int __s488 = msg->__s488;
int __s489 = msg->__s489;

double *t17 = malloc(sizeof(double)*xh_ncols*__s489);
for (j=0; j<xh_ncols; j+=__s488) {
// 2_2
int __m488 = j + __s488 > xh_ncols ? xh_ncols - j : __s488;
double *t24 = t17 + j;
double *t23 = xh + j;
for (k=0; k<__m489; k+=1) {
// 2_3
double *t31 = t24 + k*xh_ncols;
double *t30 = t16 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m488; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = t23 + l*xh_ncols;
for (p=0; p<__m488; p+=1) {
// 2_5
t31[p] += (t30[l]*t38[p]);
}
}
}
}
for (j=0; j<xh_ncols; j+=__s490) {
// 4_2
int __m490 = j + __s490 > xh_ncols ? xh_ncols - j : __s490;
double *t28 = t21 + j;
double *t26 = t17 + j;
double *t27 = t20 + j;
for (k=0; k<__m489; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t26 + k*xh_ncols;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<__m490; l+=1) {
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

int __s490 = 512;

int __s488 = 504;

int nparts__s489 = 6;
int __s489;
if (nparts__s489 > 1 && A_nrows > nparts__s489) {
__s489 = A_nrows/nparts__s489;
// this will fail if A_nrows%nparts__s489+__s489 > nparts__s489
// which primarily effects small sizes
if (A_nrows%nparts__s489)
++__s489;
}
else {
__s489 = A_nrows;
nparts__s489 = 1;
}

predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s489);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s489);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s489,ii+=1) {
// 2_1
int __m489 = i + __s489 > A_nrows ? A_nrows - i : __s489;
double *t21 = xhn + i*xh_ncols;
double *t16 = A + i*A_ncols;
double *t20 = Y + i*xh_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].__m489 = __m489;
predict1_0[disp].t20 = t20;
predict1_0[disp].t21 = t21;
predict1_0[disp].__s490 = __s490;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t16 = t16;
predict1_0[disp].xh = xh;
predict1_0[disp].__s488 = __s488;
predict1_0[disp].__s489 = __s489;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s489; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
}
