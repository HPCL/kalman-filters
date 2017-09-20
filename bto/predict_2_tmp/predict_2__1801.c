#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m4222;
double *t26;
double *t25;
double *t27;
int __s4221;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m4222 = msg->__m4222;
double *t26 = msg->t26;
double *t25 = msg->t25;
double *t27 = msg->t27;
int __s4221 = msg->__s4221;

for (j=0; j<P_ncols; j+=__s4221) {
// 6_2
int __m4221 = j + __s4221 > P_ncols ? P_ncols - j : __s4221;
double *t38 = t27 + j;
double *t36 = t25 + j;
double *t37 = t26 + j;
for (k=0; k<__m4222; k+=1) {
// 6_3
double *t49 = t38 + k*P_ncols;
double *t47 = t36 + k*P_ncols;
double *t48 = t37 + k*P_ncols;
for (l=0; l<__m4221; l+=1) {
// 6_4
t49[l] = (t47[l]+t48[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s4221 = 504;

int __s4220 = 10;

int __s4219 = 8;

int nparts__s4222 = 10;
int __s4222;
if (nparts__s4222 > 1 && P_ncols > nparts__s4222) {
__s4222 = P_ncols/nparts__s4222;
// this will fail if P_ncols%nparts__s4222+__s4222 > nparts__s4222
// which primarily effects small sizes
if (P_ncols%nparts__s4222)
++__s4222;
}
else {
__s4222 = P_ncols;
nparts__s4222 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t24;
double *t13 = t24;
double *t11 = t24;
double *t12 = A;
double *t9 = t21;
for (i=0; i<P_ncols; i+=__s4219) {
// 2_1
int __m4219 = i + __s4219 > P_ncols ? P_ncols - i : __s4219;
double *t20 = t21 + i;
double *t19 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t31 = t20 + j*P_ncols;
double *t30 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m4219; ++__zr__) t31[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t41 = t19 + k*P_ncols;
for (l=0; l<__m4219; l+=1) {
// 2_4
t31[l] += (t30[k]*t41[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s4220) {
// 4_1
int __m4220 = i + __s4220 > P_ncols ? P_ncols - i : __s4220;
double *t23 = t24 + i;
double *t29 = t12 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t34 = t23 + j*P_ncols;
double *t33 = t9 + j*P_ncols;
for (k=0; k<__m4220; k+=1) {
// 4_3
double *t51 = t29 + k*P_ncols;
t34[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t34[k] += (t33[l]*t51[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4222);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4222);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4222,ii+=1) {
// 6_1
int __m4222 = i + __s4222 > P_ncols ? P_ncols - i : __s4222;
double *t27 = P + i*P_ncols;
double *t25 = t16 + i*P_ncols;
double *t26 = Q + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m4222 = __m4222;
predict_0[disp].t26 = t26;
predict_0[disp].t25 = t25;
predict_0[disp].t27 = t27;
predict_0[disp].__s4221 = __s4221;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4222; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t24);
free(t21);
}
