#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t20;
int __m3935;
double *t14;
double *t21;
int __s3934;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t17;
int __m3933;
double *P;
double *t18;
int __s3932;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t17 = msg->t17;
int __m3933 = msg->__m3933;
double *P = msg->P;
double *t18 = msg->t18;
int __s3932 = msg->__s3932;

for (j=0; j<P_ncols; j+=__s3932) {
// 2_2
int __m3932 = j + __s3932 > P_ncols ? P_ncols - j : __s3932;
double *t28 = t18 + j;
double *t27 = P + j;
for (k=0; k<__m3933; k+=1) {
// 2_3
double *t39 = t28 + k*P_ncols;
double *t38 = t17 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3932; ++__zr__) t39[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t45 = t27 + l*P_ncols;
for (p=0; p<__m3932; p+=1) {
// 2_5
t39[p] += (t38[l]*t45[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t20 = msg->t20;
int __m3935 = msg->__m3935;
double *t14 = msg->t14;
double *t21 = msg->t21;
int __s3934 = msg->__s3934;

for (j=0; j<P_ncols; j+=__s3934) {
// 4_2
int __m3934 = j + __s3934 > P_ncols ? P_ncols - j : __s3934;
double *t31 = t21 + j;
double *t37 = t14 + j*P_ncols;
for (k=0; k<__m3935; k+=1) {
// 4_3
double *t42 = t31 + k*P_ncols;
double *t41 = t20 + k*P_ncols;
for (l=0; l<__m3934; l+=1) {
// 4_4
double *t51 = t37 + l*P_ncols;
t42[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t42[l] += (t41[p]*t51[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j;

int __s3934 = 512;

int __s3932 = 512;

int nparts__s3933 = 12;
int __s3933;
if (nparts__s3933 > 1 && P_ncols > nparts__s3933) {
__s3933 = P_ncols/nparts__s3933;
// this will fail if P_ncols%nparts__s3933+__s3933 > nparts__s3933
// which primarily effects small sizes
if (P_ncols%nparts__s3933)
++__s3933;
}
else {
__s3933 = P_ncols;
nparts__s3933 = 1;
}

int nparts__s3935 = 12;
int __s3935;
if (nparts__s3935 > 1 && P_ncols > nparts__s3935) {
__s3935 = P_ncols/nparts__s3935;
// this will fail if P_ncols%nparts__s3935+__s3935 > nparts__s3935
// which primarily effects small sizes
if (P_ncols%nparts__s3935)
++__s3935;
}
else {
__s3935 = P_ncols;
nparts__s3935 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t22;
double *t16 = t22;
double *t15 = t19;
double *t9 = t19;
double *t11 = t19;
double *t10 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3933);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3933);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3933,ii+=1) {
// 2_1
int __m3933 = i + __s3933 > P_ncols ? P_ncols - i : __s3933;
double *t18 = t19 + i*P_ncols;
double *t17 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t17 = t17;
predict_0[disp].__m3933 = __m3933;
predict_0[disp].P = P;
predict_0[disp].t18 = t18;
predict_0[disp].__s3932 = __s3932;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3933; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3935);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3935);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3935,ii+=1) {
// 4_1
int __m3935 = i + __s3935 > P_ncols ? P_ncols - i : __s3935;
double *t21 = t22 + i*P_ncols;
double *t20 = t15 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t20 = t20;
predict_1[disp].__m3935 = __m3935;
predict_1[disp].t14 = t14;
predict_1[disp].t21 = t21;
predict_1[disp].__s3934 = __s3934;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3935; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t25 = P + i*P_ncols;
double *t23 = t13 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t25[j] = (t23[j]+t24[j]);
}
}
free(t22);
free(t19);
}
