#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t27;
double *t26;
double *t28;
int __s3434;
int __m3435;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *P;
double *t20;
double *t21;
int __s3431;
int __m3432;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t20 = msg->t20;
double *t21 = msg->t21;
int __s3431 = msg->__s3431;
int __m3432 = msg->__m3432;

for (j=0; j<__m3432; j+=__s3431) {
// 2_2
int __m3431 = j + __s3431 > __m3432 ? __m3432 - j : __s3431;
double *t31 = t21 + j*P_ncols;
double *t30 = t20 + j*P_ncols;
for (k=0; k<__m3431; k+=1) {
// 2_3
double *t41 = t31 + k*P_ncols;
double *t40 = t30 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t41[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t52 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t41[p] += (t40[l]*t52[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t27 = msg->t27;
double *t26 = msg->t26;
double *t28 = msg->t28;
int __s3434 = msg->__s3434;
int __m3435 = msg->__m3435;

for (j=0; j<__m3435; j+=__s3434) {
// 6_2
int __m3434 = j + __s3434 > __m3435 ? __m3435 - j : __s3434;
double *t38 = t28 + j*P_ncols;
double *t36 = t26 + j*P_ncols;
double *t37 = t27 + j*P_ncols;
for (k=0; k<__m3434; k+=1) {
// 6_3
double *t48 = t38 + k*P_ncols;
double *t46 = t36 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 6_4
t48[l] = (t46[l]+t47[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s3434 = 496;

int __s3433 = 10;

int __s3431 = 512;

int nparts__s3435 = 12;
int __s3435;
if (nparts__s3435 > 1 && P_ncols > nparts__s3435) {
__s3435 = P_ncols/nparts__s3435;
// this will fail if P_ncols%nparts__s3435+__s3435 > nparts__s3435
// which primarily effects small sizes
if (P_ncols%nparts__s3435)
++__s3435;
}
else {
__s3435 = P_ncols;
nparts__s3435 = 1;
}

int nparts__s3432 = 10;
int __s3432;
if (nparts__s3432 > 1 && P_ncols > nparts__s3432) {
__s3432 = P_ncols/nparts__s3432;
// this will fail if P_ncols%nparts__s3432+__s3432 > nparts__s3432
// which primarily effects small sizes
if (P_ncols%nparts__s3432)
++__s3432;
}
else {
__s3432 = P_ncols;
nparts__s3432 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = t25;
double *t14 = t25;
double *t13 = t25;
double *t12 = t22;
double *t9 = t22;
double *t11 = t22;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3432);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3432);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3432,ii+=1) {
// 2_1
int __m3432 = i + __s3432 > P_ncols ? P_ncols - i : __s3432;
double *t21 = t22 + i*P_ncols;
double *t20 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t20 = t20;
predict_0[disp].t21 = t21;
predict_0[disp].__s3431 = __s3431;
predict_0[disp].__m3432 = __m3432;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3432; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s3433) {
// 4_1
int __m3433 = i + __s3433 > P_ncols ? P_ncols - i : __s3433;
double *t24 = t25 + i*P_ncols;
double *t23 = t12 + i*P_ncols;
for (j=0; j<__m3433; j+=1) {
// 4_2
double *t34 = t24 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t50 = A + k*P_ncols;
t34[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t34[k] += (t33[l]*t50[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3435);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3435);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3435,ii+=1) {
// 6_1
int __m3435 = i + __s3435 > P_ncols ? P_ncols - i : __s3435;
double *t28 = P + i*P_ncols;
double *t26 = t17 + i*P_ncols;
double *t27 = Q + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t27 = t27;
predict_1[disp].t26 = t26;
predict_1[disp].t28 = t28;
predict_1[disp].__s3434 = __s3434;
predict_1[disp].__m3435 = __m3435;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3435; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t25);
free(t22);
}
