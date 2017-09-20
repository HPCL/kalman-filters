#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *P;
double *t15;
double *t16;
int __s453;
int __m454;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t15 = msg->t15;
double *t16 = msg->t16;
int __s453 = msg->__s453;
int __m454 = msg->__m454;

for (j=0; j<__m454; j+=__s453) {
// 2_2
int __m453 = j + __s453 > __m454 ? __m454 - j : __s453;
double *t26 = t16 + j*P_ncols;
double *t25 = t15 + j*P_ncols;
for (k=0; k<__m453; k+=1) {
// 2_3
double *t37 = t26 + k*P_ncols;
double *t36 = t25 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t37[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t48 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t37[p] += (t36[l]*t48[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k;

int __s455 = 2;

int __s453 = 512;

int nparts__s454 = 10;
int __s454;
if (nparts__s454 > 1 && P_ncols > nparts__s454) {
__s454 = P_ncols/nparts__s454;
// this will fail if P_ncols%nparts__s454+__s454 > nparts__s454
// which primarily effects small sizes
if (P_ncols%nparts__s454)
++__s454;
}
else {
__s454 = P_ncols;
nparts__s454 = 1;
}

double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t12 = t20;
double *t9 = t17;
double *t11 = t17;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s454);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s454);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s454,ii+=1) {
// 2_1
int __m454 = i + __s454 > P_ncols ? P_ncols - i : __s454;
double *t16 = t17 + i*P_ncols;
double *t15 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t15 = t15;
predict_0[disp].t16 = t16;
predict_0[disp].__s453 = __s453;
predict_0[disp].__m454 = __m454;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s454; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t19 = t20 + i*P_ncols;
double *t18 = t9 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t35 = A + j*P_ncols;
t19[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t19[j] += (t18[k]*t35[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s455) {
// 6_1
int __m455 = i + __s455 > P_ncols ? P_ncols - i : __s455;
double *t23 = P + i*P_ncols;
double *t21 = t12 + i*P_ncols;
double *t22 = Q + i*P_ncols;
for (j=0; j<__m455; j+=1) {
// 6_2
double *t33 = t23 + j*P_ncols;
double *t31 = t21 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t33[k] = (t31[k]+t32[k]);
}
}
}
free(t20);
free(t17);
}
