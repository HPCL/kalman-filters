#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t25;
double *t24;
double *t26;
int __s1321;
int __m1322;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t25 = msg->t25;
double *t24 = msg->t24;
double *t26 = msg->t26;
int __s1321 = msg->__s1321;
int __m1322 = msg->__m1322;

for (j=0; j<__m1322; j+=__s1321) {
// 6_2
int __m1321 = j + __s1321 > __m1322 ? __m1322 - j : __s1321;
double *t36 = t26 + j;
double *t34 = t24 + j;
double *t35 = t25 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t47 = t36 + k*P_ncols;
double *t45 = t34 + k*P_ncols;
double *t46 = t35 + k*P_ncols;
for (l=0; l<__m1321; l+=1) {
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

int __s1321 = 512;

int __s1320 = 2;

int __s1319 = 2;

int nparts__s1322 = 12;
int __s1322;
if (nparts__s1322 > 1 && P_ncols > nparts__s1322) {
__s1322 = P_ncols/nparts__s1322;
// this will fail if P_ncols%nparts__s1322+__s1322 > nparts__s1322
// which primarily effects small sizes
if (P_ncols%nparts__s1322)
++__s1322;
}
else {
__s1322 = P_ncols;
nparts__s1322 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t23;
double *t12 = t23;
double *t11 = t23;
double *t10 = t20;
double *t9 = t20;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s1319) {
// 2_1
int __m1319 = i + __s1319 > P_ncols ? P_ncols - i : __s1319;
double *t19 = t20 + i*P_ncols;
double *t18 = t8 + i*P_ncols;
for (j=0; j<__m1319; j+=1) {
// 2_2
double *t29 = t19 + j*P_ncols;
double *t28 = t18 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t29[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t39 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t29[l] += (t28[k]*t39[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s1320) {
// 4_1
int __m1320 = i + __s1320 > P_ncols ? P_ncols - i : __s1320;
double *t22 = t23 + i*P_ncols;
double *t21 = t10 + i*P_ncols;
for (j=0; j<__m1320; j+=1) {
// 4_2
double *t32 = t22 + j*P_ncols;
double *t31 = t21 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t49 = A + k*P_ncols;
t32[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t32[k] += (t31[l]*t49[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1322);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1322);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1322,ii+=1) {
// 6_1
int __m1322 = i + __s1322 > P_ncols ? P_ncols - i : __s1322;
double *t26 = P + i;
double *t24 = t15 + i;
double *t25 = Q + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t25 = t25;
predict_0[disp].t24 = t24;
predict_0[disp].t26 = t26;
predict_0[disp].__s1321 = __s1321;
predict_0[disp].__m1322 = __m1322;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1322; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t23);
free(t20);
}
