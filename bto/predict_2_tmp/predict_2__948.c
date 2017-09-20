#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2419;
int P_ncols;
double *t15;
double *t14;
double *t8;
int __s2418;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2419 = msg->__m2419;
int P_ncols = msg->P_ncols;
double *t15 = msg->t15;
double *t14 = msg->t14;
double *t8 = msg->t8;
int __s2418 = msg->__s2418;

for (j=0; j<P_ncols; j+=__s2418) {
// 2_2
int __m2418 = j + __s2418 > P_ncols ? P_ncols - j : __s2418;
double *t24 = t8 + j;
double *t25 = t14 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t36 = t15 + k*P_ncols;
double *t35 = t24 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2419; ++__zr__) t36[__zr__] = 0.0;
for (l=0; l<__m2418; l+=1) {
// 2_4
double *t43 = t25 + l*P_ncols;
for (p=0; p<__m2419; p+=1) {
// 2_5
t36[p] += (t35[l]*t43[p]);
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

int __s2420 = 2;

int __s2418 = 512;

int nparts__s2419 = 12;
int __s2419;
if (nparts__s2419 > 1 && P_ncols > nparts__s2419) {
__s2419 = P_ncols/nparts__s2419;
// this will fail if P_ncols%nparts__s2419+__s2419 > nparts__s2419
// which primarily effects small sizes
if (P_ncols%nparts__s2419)
++__s2419;
}
else {
__s2419 = P_ncols;
nparts__s2419 = 1;
}

double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t19;
double *t12 = t16;
double *t11 = t16;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2419);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2419);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2419,ii+=1) {
// 2_1
int __m2419 = i + __s2419 > P_ncols ? P_ncols - i : __s2419;
double *t15 = t16 + i;
double *t14 = P + i;
predict_0[disp].__m2419 = __m2419;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t15 = t15;
predict_0[disp].t14 = t14;
predict_0[disp].t8 = t8;
predict_0[disp].__s2418 = __s2418;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2419; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s2420) {
// 4_1
int __m2420 = i + __s2420 > P_ncols ? P_ncols - i : __s2420;
double *t18 = t19 + i*P_ncols;
double *t17 = t12 + i*P_ncols;
for (j=0; j<__m2420; j+=1) {
// 4_2
double *t29 = t18 + j*P_ncols;
double *t28 = t17 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t41 = A + k*P_ncols;
t29[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t29[k] += (t28[l]*t41[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t22 = P + i*P_ncols;
double *t20 = t13 + i*P_ncols;
double *t21 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t22[j] = (t20[j]+t21[j]);
}
}
free(t19);
free(t16);
}
