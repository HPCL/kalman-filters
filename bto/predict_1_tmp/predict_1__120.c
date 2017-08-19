#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int A_ncols;
double *A;
int A_nrows;
double *t20;
double *t16;
double *t21;
int __s142;
int __m143;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *A = msg->A;
int A_nrows = msg->A_nrows;
double *t20 = msg->t20;
double *t16 = msg->t16;
double *t21 = msg->t21;
int __s142 = msg->__s142;
int __m143 = msg->__m143;

for (j=0; j<__m143; j+=__s142) {
// 2_2
int __m142 = j + __s142 > __m143 ? __m143 - j : __s142;
double *t31 = malloc(sizeof(double)*__s142);
double *t28 = t21 + j;
double *t23 = t16 + j;
double *t27 = t20 + j;
for (k=0; k<A_nrows; k+=1) {
// 2_3
double *t35 = t28 + k*xh_ncols;
double *t30 = A + k*A_ncols;
double *t34 = t27 + k*xh_ncols;
for (__zr__ = 0; __zr__ < __m142; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = t23 + l*xh_ncols;
for (p=0; p<__m142; p+=1) {
// 2_5
t31[p] += (t30[l]*t38[p]);
}
}
for (l=0; l<__m142; l+=1) {
// 4_4
t35[l] = (t31[l]+t34[l]);
}
}
free(t31);
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii;

int __s142 = 512;

int nparts__s143 = 8;
int __s143;
if (nparts__s143 > 1 && xh_ncols > nparts__s143) {
__s143 = xh_ncols/nparts__s143;
// this will fail if xh_ncols%nparts__s143+__s143 > nparts__s143
// which primarily effects small sizes
if (xh_ncols%nparts__s143)
++__s143;
}
else {
__s143 = xh_ncols;
nparts__s143 = 1;
}

predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s143);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s143);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s143,ii+=1) {
// 2_1
int __m143 = i + __s143 > xh_ncols ? xh_ncols - i : __s143;
double *t21 = xhn + i;
double *t16 = xh + i;
double *t20 = Y + i;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].A = A;
predict1_0[disp].A_nrows = A_nrows;
predict1_0[disp].t20 = t20;
predict1_0[disp].t16 = t16;
predict1_0[disp].t21 = t21;
predict1_0[disp].__s142 = __s142;
predict1_0[disp].__m143 = __m143;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s143; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
}
