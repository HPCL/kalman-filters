#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t16;
double *t24;
double *t18;
int __s1492;
int __m1493;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t16 = msg->t16;
double *t24 = msg->t24;
double *t18 = msg->t18;
int __s1492 = msg->__s1492;
int __m1493 = msg->__m1493;

for (j=0; j<__m1493; j+=__s1492) {
// 4_2
int __m1492 = j + __s1492 > __m1493 ? __m1493 - j : __s1492;
double *t30 = t18 + j;
double *t36 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t41 = t30 + k*P_ncols;
double *t40 = t16 + k*P_ncols;
for (l=0; l<__m1492; l+=1) {
// 4_4
double *t46 = t36 + l*P_ncols;
t41[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t41[l] += (t40[p]*t46[p]);
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

int __s1492 = 512;

int nparts__s1493 = 12;
int __s1493;
if (nparts__s1493 > 1 && P_ncols > nparts__s1493) {
__s1493 = P_ncols/nparts__s1493;
// this will fail if P_ncols%nparts__s1493+__s1493 > nparts__s1493
// which primarily effects small sizes
if (P_ncols%nparts__s1493)
++__s1493;
}
else {
__s1493 = P_ncols;
nparts__s1493 = 1;
}

double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t19;
double *t12 = t19;
double *t13 = A;
double *t10 = A;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t15 = t16 + i*P_ncols;
double *t14 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t15[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t26 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t15[k] += (t14[j]*t26[k]);
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1493);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1493);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1493,ii+=1) {
// 4_1
int __m1493 = i + __s1493 > P_ncols ? P_ncols - i : __s1493;
double *t18 = t19 + i;
double *t24 = t13 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t16 = t16;
predict_0[disp].t24 = t24;
predict_0[disp].t18 = t18;
predict_0[disp].__s1492 = __s1492;
predict_0[disp].__m1493 = __m1493;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1493; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t22 = P + i*P_ncols;
double *t20 = t9 + i*P_ncols;
double *t21 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t22[j] = (t20[j]+t21[j]);
}
}
free(t19);
free(t16);
}
