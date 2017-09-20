#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t15;
double *t16;
int __s4317;
int __m4318;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t15 = msg->t15;
double *t16 = msg->t16;
int __s4317 = msg->__s4317;
int __m4318 = msg->__m4318;

for (j=0; j<__m4318; j+=__s4317) {
// 2_2
int __m4317 = j + __s4317 > __m4318 ? __m4318 - j : __s4317;
double *t27 = t16 + j;
double *t26 = t15 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t37 = t27 + k*P_ncols;
double *t36 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m4317; ++__zr__) t37[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t44 = t26 + l*P_ncols;
for (p=0; p<__m4317; p+=1) {
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

int __s4319 = 10;

int __s4317 = 488;

int nparts__s4318 = 6;
int __s4318;
if (nparts__s4318 > 1 && P_ncols > nparts__s4318) {
__s4318 = P_ncols/nparts__s4318;
// this will fail if P_ncols%nparts__s4318+__s4318 > nparts__s4318
// which primarily effects small sizes
if (P_ncols%nparts__s4318)
++__s4318;
}
else {
__s4318 = P_ncols;
nparts__s4318 = 1;
}

double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t20;
double *t14 = A;
double *t9 = t17;
double *t11 = t17;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4318);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4318);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4318,ii+=1) {
// 2_1
int __m4318 = i + __s4318 > P_ncols ? P_ncols - i : __s4318;
double *t16 = t17 + i;
double *t15 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t15 = t15;
predict_0[disp].t16 = t16;
predict_0[disp].__s4317 = __s4317;
predict_0[disp].__m4318 = __m4318;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4318; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s4319) {
// 4_1
int __m4319 = i + __s4319 > P_ncols ? P_ncols - i : __s4319;
double *t19 = t20 + i;
double *t25 = t14 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t30 = t19 + j*P_ncols;
double *t29 = t9 + j*P_ncols;
for (k=0; k<__m4319; k+=1) {
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
