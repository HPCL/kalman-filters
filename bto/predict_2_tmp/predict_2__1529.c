#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t24;
double *t23;
double *t25;
int __s3562;
int __m3563;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t24 = msg->t24;
double *t23 = msg->t23;
double *t25 = msg->t25;
int __s3562 = msg->__s3562;
int __m3563 = msg->__m3563;

for (j=0; j<__m3563; j+=__s3562) {
// 6_2
int __m3562 = j + __s3562 > __m3563 ? __m3563 - j : __s3562;
double *t37 = t25 + j;
double *t35 = t23 + j;
double *t36 = t24 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t47 = t37 + k*P_ncols;
double *t45 = t35 + k*P_ncols;
double *t46 = t36 + k*P_ncols;
for (l=0; l<__m3562; l+=1) {
// 6_4
t47[l] = (t45[l]+t46[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s3562 = 496;

int __s3561 = 2;

int nparts__s3563 = 12;
int __s3563;
if (nparts__s3563 > 1 && P_ncols > nparts__s3563) {
__s3563 = P_ncols/nparts__s3563;
// this will fail if P_ncols%nparts__s3563+__s3563 > nparts__s3563
// which primarily effects small sizes
if (P_ncols%nparts__s3563)
++__s3563;
}
else {
__s3563 = P_ncols;
nparts__s3563 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t22;
double *t11 = t22;
double *t9 = t22;
double *t10 = A;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t18 = t19 + i*P_ncols;
double *t17 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t18[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t29 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t18[k] += (t17[j]*t29[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s3561) {
// 4_1
int __m3561 = i + __s3561 > P_ncols ? P_ncols - i : __s3561;
double *t21 = t22 + i;
double *t27 = t10 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t33 = t21 + j*P_ncols;
double *t32 = t19 + j*P_ncols;
for (k=0; k<__m3561; k+=1) {
// 4_3
double *t49 = t27 + k*P_ncols;
t33[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t33[k] += (t32[l]*t49[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3563);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3563);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3563,ii+=1) {
// 6_1
int __m3563 = i + __s3563 > P_ncols ? P_ncols - i : __s3563;
double *t25 = P + i;
double *t23 = t14 + i;
double *t24 = Q + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t24 = t24;
predict_0[disp].t23 = t23;
predict_0[disp].t25 = t25;
predict_0[disp].__s3562 = __s3562;
predict_0[disp].__m3563 = __m3563;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3563; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t22);
free(t19);
}
