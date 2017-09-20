#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m458;
int P_ncols;
double *t24;
double *t23;
double *t25;
int __s457;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m458 = msg->__m458;
int P_ncols = msg->P_ncols;
double *t24 = msg->t24;
double *t23 = msg->t23;
double *t25 = msg->t25;
int __s457 = msg->__s457;

for (j=0; j<P_ncols; j+=__s457) {
// 6_2
int __m457 = j + __s457 > P_ncols ? P_ncols - j : __s457;
double *t35 = t25 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
double *t34 = t24 + j*P_ncols;
for (k=0; k<__m457; k+=1) {
// 6_3
double *t48 = t35 + k*P_ncols;
double *t46 = t33 + k*P_ncols;
double *t47 = t34 + k*P_ncols;
for (l=0; l<__m458; l+=1) {
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

int __s457 = 512;

int __s456 = 2;

int nparts__s458 = 12;
int __s458;
if (nparts__s458 > 1 && P_ncols > nparts__s458) {
__s458 = P_ncols/nparts__s458;
// this will fail if P_ncols%nparts__s458+__s458 > nparts__s458
// which primarily effects small sizes
if (P_ncols%nparts__s458)
++__s458;
}
else {
__s458 = P_ncols;
nparts__s458 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t22;
double *t10 = t22;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s456) {
// 2_1
int __m456 = i + __s456 > P_ncols ? P_ncols - i : __s456;
double *t16 = t8 + i;
double *t17 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t28 = t19 + j*P_ncols;
double *t27 = t16 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t28[__zr__] = 0.0;
for (k=0; k<__m456; k+=1) {
// 2_3
double *t39 = t17 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t28[l] += (t27[k]*t39[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t21 = t22 + i*P_ncols;
double *t20 = t19 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t37 = A + j*P_ncols;
t21[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t21[j] += (t20[k]*t37[k]);
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s458);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s458);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s458,ii+=1) {
// 6_1
int __m458 = i + __s458 > P_ncols ? P_ncols - i : __s458;
double *t25 = P + i;
double *t23 = t13 + i;
double *t24 = Q + i;
predict_0[disp].__m458 = __m458;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t24 = t24;
predict_0[disp].t23 = t23;
predict_0[disp].t25 = t25;
predict_0[disp].__s457 = __s457;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s458; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t22);
free(t19);
}
