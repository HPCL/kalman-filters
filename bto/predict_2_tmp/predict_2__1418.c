#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *P;
double *t12;
double *t13;
int __s3379;
int __m3380;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t12 = msg->t12;
double *t13 = msg->t13;
int __s3379 = msg->__s3379;
int __m3380 = msg->__m3380;

for (j=0; j<__m3380; j+=__s3379) {
// 2_2
int __m3379 = j + __s3379 > __m3380 ? __m3380 - j : __s3379;
double *t23 = t13 + j*P_ncols;
double *t22 = t12 + j*P_ncols;
for (k=0; k<__m3379; k+=1) {
// 2_3
double *t34 = t23 + k*P_ncols;
double *t33 = t22 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t34[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t41 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t34[p] += (t33[l]*t41[p]);
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

int __s3379 = 512;

int nparts__s3380 = 12;
int __s3380;
if (nparts__s3380 > 1 && P_ncols > nparts__s3380) {
__s3380 = P_ncols/nparts__s3380;
// this will fail if P_ncols%nparts__s3380+__s3380 > nparts__s3380
// which primarily effects small sizes
if (P_ncols%nparts__s3380)
++__s3380;
}
else {
__s3380 = P_ncols;
nparts__s3380 = 1;
}

double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t14;
double *t11 = t14;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3380);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3380);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3380,ii+=1) {
// 2_1
int __m3380 = i + __s3380 > P_ncols ? P_ncols - i : __s3380;
double *t13 = t14 + i*P_ncols;
double *t12 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t12 = t12;
predict_0[disp].t13 = t13;
predict_0[disp].__s3379 = __s3379;
predict_0[disp].__m3380 = __m3380;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3380; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t16 = t17 + i*P_ncols;
double *t15 = t9 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t32 = A + j*P_ncols;
t16[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t16[j] += (t15[k]*t32[k]);
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t20 = P + i*P_ncols;
double *t18 = t17 + i*P_ncols;
double *t19 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t20[j] = (t18[j]+t19[j]);
}
}
free(t17);
free(t14);
}
