#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m410;
int xh_ncols;
double *t20;
double *t21;
int __s411;
int A_nrows;
double *t16;
int A_ncols;
double *A;
int __s409;
int __s410;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int __m410 = msg->__m410;
int xh_ncols = msg->xh_ncols;
double *t20 = msg->t20;
double *t21 = msg->t21;
int __s411 = msg->__s411;
int A_nrows = msg->A_nrows;
double *t16 = msg->t16;
int A_ncols = msg->A_ncols;
double *A = msg->A;
int __s409 = msg->__s409;
int __s410 = msg->__s410;

double *t17 = malloc(sizeof(double)*A_nrows*__s410);
for (j=0; j<A_nrows; j+=__s409) {
// 2_2
int __m409 = j + __s409 > A_nrows ? A_nrows - j : __s409;
double *t24 = t17 + j*__m410;
double *t23 = A + j*A_ncols;
for (k=0; k<__m409; k+=1) {
// 2_3
double *t31 = t24 + k*__m410;
double *t30 = t23 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m410; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = t16 + l*xh_ncols;
for (p=0; p<__m410; p+=1) {
// 2_5
t31[p] += (t30[l]*t38[p]);
}
}
}
}
for (j=0; j<A_nrows; j+=__s411) {
// 4_2
int __m411 = j + __s411 > A_nrows ? A_nrows - j : __s411;
double *t28 = t21 + j*xh_ncols;
double *t26 = t17 + j*__m410;
double *t27 = t20 + j*xh_ncols;
for (k=0; k<__m411; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t26 + k*__m410;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<__m410; l+=1) {
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

int __s411 = 512;

int __s409 = 512;

int nparts__s410 = 6;
int __s410;
if (nparts__s410 > 1 && xh_ncols > nparts__s410) {
__s410 = xh_ncols/nparts__s410;
// this will fail if xh_ncols%nparts__s410+__s410 > nparts__s410
// which primarily effects small sizes
if (xh_ncols%nparts__s410)
++__s410;
}
else {
__s410 = xh_ncols;
nparts__s410 = 1;
}

predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s410);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s410);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s410,ii+=1) {
// 2_1
int __m410 = i + __s410 > xh_ncols ? xh_ncols - i : __s410;
double *t21 = xhn + i;
double *t16 = xh + i;
double *t20 = Y + i;
predict1_0[disp].__m410 = __m410;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].t20 = t20;
predict1_0[disp].t21 = t21;
predict1_0[disp].__s411 = __s411;
predict1_0[disp].A_nrows = A_nrows;
predict1_0[disp].t16 = t16;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].A = A;
predict1_0[disp].__s409 = __s409;
predict1_0[disp].__s410 = __s410;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s410; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
}
