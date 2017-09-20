#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t15;
int __m3953;
double *P;
double *t16;
int __s3952;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t15 = msg->t15;
int __m3953 = msg->__m3953;
double *P = msg->P;
double *t16 = msg->t16;
int __s3952 = msg->__s3952;

for (j=0; j<P_ncols; j+=__s3952) {
// 2_2
int __m3952 = j + __s3952 > P_ncols ? P_ncols - j : __s3952;
double *t27 = t16 + j;
double *t26 = P + j;
for (k=0; k<__m3953; k+=1) {
// 2_3
double *t37 = t27 + k*P_ncols;
double *t36 = t15 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3952; ++__zr__) t37[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t44 = t26 + l*P_ncols;
for (p=0; p<__m3952; p+=1) {
// 2_5
t37[p] += (t36[l]*t44[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s3954 = 2;

int __s3952 = 512;

int nparts__s3953 = 10;
int __s3953;
if (nparts__s3953 > 1 && P_ncols > nparts__s3953) {
__s3953 = P_ncols/nparts__s3953;
// this will fail if P_ncols%nparts__s3953+__s3953 > nparts__s3953
// which primarily effects small sizes
if (P_ncols%nparts__s3953)
++__s3953;
}
else {
__s3953 = P_ncols;
nparts__s3953 = 1;
}

double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t20;
double *t9 = t17;
double *t11 = t17;
double *t10 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3953);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3953);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3953,ii+=1) {
// 2_1
int __m3953 = i + __s3953 > P_ncols ? P_ncols - i : __s3953;
double *t16 = t17 + i*P_ncols;
double *t15 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t15 = t15;
predict_0[disp].__m3953 = __m3953;
predict_0[disp].P = P;
predict_0[disp].t16 = t16;
predict_0[disp].__s3952 = __s3952;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3953; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s3954) {
// 4_1
int __m3954 = i + __s3954 > P_ncols ? P_ncols - i : __s3954;
double *t19 = t20 + i;
double *t25 = t14 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t30 = t19 + j*P_ncols;
double *t29 = t9 + j*P_ncols;
for (k=0; k<__m3954; k+=1) {
// 4_3
double *t42 = t25 + k*P_ncols;
t30[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t30[k] += (t29[l]*t42[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t23 = P + i*P_ncols;
double *t21 = t13 + i*P_ncols;
double *t22 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t23[j] = (t21[j]+t22[j]);
}
}
free(t20);
free(t17);
}
