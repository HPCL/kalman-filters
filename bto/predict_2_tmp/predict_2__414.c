#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m1095;
int P_ncols;
double *t26;
double *t25;
double *t27;
int __s1094;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m1095 = msg->__m1095;
int P_ncols = msg->P_ncols;
double *t26 = msg->t26;
double *t25 = msg->t25;
double *t27 = msg->t27;
int __s1094 = msg->__s1094;

for (j=0; j<P_ncols; j+=__s1094) {
// 6_2
int __m1094 = j + __s1094 > P_ncols ? P_ncols - j : __s1094;
double *t38 = t27 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
double *t37 = t26 + j*P_ncols;
for (k=0; k<__m1094; k+=1) {
// 6_3
double *t49 = t38 + k*P_ncols;
double *t47 = t36 + k*P_ncols;
double *t48 = t37 + k*P_ncols;
for (l=0; l<__m1095; l+=1) {
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

int __s1094 = 504;

int __s1093 = 2;

int __s1092 = 2;

int nparts__s1095 = 12;
int __s1095;
if (nparts__s1095 > 1 && P_ncols > nparts__s1095) {
__s1095 = P_ncols/nparts__s1095;
// this will fail if P_ncols%nparts__s1095+__s1095 > nparts__s1095
// which primarily effects small sizes
if (P_ncols%nparts__s1095)
++__s1095;
}
else {
__s1095 = P_ncols;
nparts__s1095 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t24;
double *t13 = t24;
double *t11 = t24;
double *t9 = t21;
double *t8 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s1092) {
// 2_1
int __m1092 = i + __s1092 > P_ncols ? P_ncols - i : __s1092;
double *t20 = t21 + i*P_ncols;
double *t19 = t8 + i*P_ncols;
for (j=0; j<__m1092; j+=1) {
// 2_2
double *t31 = t20 + j*P_ncols;
double *t30 = t19 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t31[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t41 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t31[l] += (t30[k]*t41[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s1093) {
// 4_1
int __m1093 = i + __s1093 > P_ncols ? P_ncols - i : __s1093;
double *t23 = t24 + i;
double *t29 = t12 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t34 = t23 + j*P_ncols;
double *t33 = t9 + j*P_ncols;
for (k=0; k<__m1093; k+=1) {
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1095);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1095);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1095,ii+=1) {
// 6_1
int __m1095 = i + __s1095 > P_ncols ? P_ncols - i : __s1095;
double *t27 = P + i;
double *t25 = t16 + i;
double *t26 = Q + i;
predict_0[disp].__m1095 = __m1095;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t26 = t26;
predict_0[disp].t25 = t25;
predict_0[disp].t27 = t27;
predict_0[disp].__s1094 = __s1094;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1095; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t24);
free(t21);
}
