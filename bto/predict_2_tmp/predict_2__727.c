#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *P;
double *t14;
double *t15;
int __s1675;
int __m1676;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t14 = msg->t14;
double *t15 = msg->t15;
int __s1675 = msg->__s1675;
int __m1676 = msg->__m1676;

for (j=0; j<__m1676; j+=__s1675) {
// 2_2
int __m1675 = j + __s1675 > __m1676 ? __m1676 - j : __s1675;
double *t25 = t15 + j*P_ncols;
double *t24 = t14 + j*P_ncols;
for (k=0; k<__m1675; k+=1) {
// 2_3
double *t35 = t25 + k*P_ncols;
double *t34 = t24 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t35[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t42 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t35[p] += (t34[l]*t42[p]);
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

int __s1677 = 2;

int __s1675 = 512;

int nparts__s1676 = 12;
int __s1676;
if (nparts__s1676 > 1 && P_ncols > nparts__s1676) {
__s1676 = P_ncols/nparts__s1676;
// this will fail if P_ncols%nparts__s1676+__s1676 > nparts__s1676
// which primarily effects small sizes
if (P_ncols%nparts__s1676)
++__s1676;
}
else {
__s1676 = P_ncols;
nparts__s1676 = 1;
}

double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t19;
double *t12 = t16;
double *t9 = t16;
double *t11 = t16;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1676);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1676);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1676,ii+=1) {
// 2_1
int __m1676 = i + __s1676 > P_ncols ? P_ncols - i : __s1676;
double *t15 = t16 + i*P_ncols;
double *t14 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t14 = t14;
predict_0[disp].t15 = t15;
predict_0[disp].__s1675 = __s1675;
predict_0[disp].__m1676 = __m1676;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1676; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s1677) {
// 4_1
int __m1677 = i + __s1677 > P_ncols ? P_ncols - i : __s1677;
double *t18 = t19 + i*P_ncols;
double *t17 = t12 + i*P_ncols;
for (j=0; j<__m1677; j+=1) {
// 4_2
double *t28 = t18 + j*P_ncols;
double *t27 = t17 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t40 = A + k*P_ncols;
t28[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t28[k] += (t27[l]*t40[l]);
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
