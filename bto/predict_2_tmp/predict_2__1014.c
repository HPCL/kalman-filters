#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2584;
int P_ncols;
double *t18;
double *t8;
double *t19;
int __s2583;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2584 = msg->__m2584;
int P_ncols = msg->P_ncols;
double *t18 = msg->t18;
double *t8 = msg->t8;
double *t19 = msg->t19;
int __s2583 = msg->__s2583;

for (j=0; j<P_ncols; j+=__s2583) {
// 2_2
int __m2583 = j + __s2583 > P_ncols ? P_ncols - j : __s2583;
double *t31 = t19 + j*P_ncols;
double *t30 = t8 + j*P_ncols;
for (k=0; k<__m2583; k+=1) {
// 2_3
double *t41 = t31 + k*P_ncols;
double *t40 = t30 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2584; ++__zr__) t41[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t52 = t18 + l*P_ncols;
for (p=0; p<__m2584; p+=1) {
// 2_5
t41[p] += (t40[l]*t52[p]);
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

int __s2586 = 10;

int __s2585 = 10;

int __s2583 = 512;

int nparts__s2584 = 10;
int __s2584;
if (nparts__s2584 > 1 && P_ncols > nparts__s2584) {
__s2584 = P_ncols/nparts__s2584;
// this will fail if P_ncols%nparts__s2584+__s2584 > nparts__s2584
// which primarily effects small sizes
if (P_ncols%nparts__s2584)
++__s2584;
}
else {
__s2584 = P_ncols;
nparts__s2584 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t24;
double *t12 = t20;
double *t9 = t20;
double *t11 = t20;
double *t8 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2584);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2584);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2584,ii+=1) {
// 2_1
int __m2584 = i + __s2584 > P_ncols ? P_ncols - i : __s2584;
double *t19 = t20 + i;
double *t18 = P + i;
predict_0[disp].__m2584 = __m2584;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t18 = t18;
predict_0[disp].t8 = t8;
predict_0[disp].t19 = t19;
predict_0[disp].__s2583 = __s2583;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2584; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s2585) {
// 4_1
int __m2585 = i + __s2585 > P_ncols ? P_ncols - i : __s2585;
double *t21 = t12 + i;
double *t29 = t14 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t34 = t24 + j*P_ncols;
double *t33 = t21 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t50 = t29 + k*P_ncols;
t34[k] = 0.0;
for (l=0; l<__m2585; l+=1) {
// 4_4
t34[k] += (t33[l]*t50[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s2586) {
// 6_1
int __m2586 = i + __s2586 > P_ncols ? P_ncols - i : __s2586;
double *t27 = P + i*P_ncols;
double *t25 = t15 + i*P_ncols;
double *t26 = Q + i*P_ncols;
for (j=0; j<__m2586; j+=1) {
// 6_2
double *t38 = t27 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
double *t37 = t26 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t38[k] = (t36[k]+t37[k]);
}
}
}
free(t24);
free(t20);
}
