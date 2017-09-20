#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t22;
double *t23;
int __s214;
int __m215;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *P;
double *t19;
double *t20;
int __s212;
int __m213;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t19 = msg->t19;
double *t20 = msg->t20;
int __s212 = msg->__s212;
int __m213 = msg->__m213;

for (j=0; j<__m213; j+=__s212) {
// 2_2
int __m212 = j + __s212 > __m213 ? __m213 - j : __s212;
double *t30 = t20 + j*P_ncols;
double *t29 = t19 + j*P_ncols;
for (k=0; k<__m212; k+=1) {
// 2_3
double *t40 = t30 + k*P_ncols;
double *t39 = t29 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t40[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t50 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t40[p] += (t39[l]*t50[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t22 = msg->t22;
double *t23 = msg->t23;
int __s214 = msg->__s214;
int __m215 = msg->__m215;

for (j=0; j<__m215; j+=__s214) {
// 4_2
int __m214 = j + __s214 > __m215 ? __m215 - j : __s214;
double *t33 = t23 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<__m214; k+=1) {
// 4_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t56 = A + l*P_ncols;
t43[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t43[l] += (t42[p]*t56[p]);
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

int __s216 = 12;

int __s214 = 512;

int __s212 = 512;

int nparts__s215 = 12;
int __s215;
if (nparts__s215 > 1 && P_ncols > nparts__s215) {
__s215 = P_ncols/nparts__s215;
// this will fail if P_ncols%nparts__s215+__s215 > nparts__s215
// which primarily effects small sizes
if (P_ncols%nparts__s215)
++__s215;
}
else {
__s215 = P_ncols;
nparts__s215 = 1;
}

int nparts__s213 = 12;
int __s213;
if (nparts__s213 > 1 && P_ncols > nparts__s213) {
__s213 = P_ncols/nparts__s213;
// this will fail if P_ncols%nparts__s213+__s213 > nparts__s213
// which primarily effects small sizes
if (P_ncols%nparts__s213)
++__s213;
}
else {
__s213 = P_ncols;
nparts__s213 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t24;
double *t13 = t24;
double *t15 = t24;
double *t14 = t21;
double *t12 = t21;
double *t9 = t21;
double *t11 = t21;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s213);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s213);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s213,ii+=1) {
// 2_1
int __m213 = i + __s213 > P_ncols ? P_ncols - i : __s213;
double *t20 = t21 + i*P_ncols;
double *t19 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t19 = t19;
predict_0[disp].t20 = t20;
predict_0[disp].__s212 = __s212;
predict_0[disp].__m213 = __m213;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s213; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s215);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s215);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s215,ii+=1) {
// 4_1
int __m215 = i + __s215 > P_ncols ? P_ncols - i : __s215;
double *t23 = t24 + i*P_ncols;
double *t22 = t14 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].A = A;
predict_1[disp].t22 = t22;
predict_1[disp].t23 = t23;
predict_1[disp].__s214 = __s214;
predict_1[disp].__m215 = __m215;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s215; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s216) {
// 6_1
int __m216 = i + __s216 > P_ncols ? P_ncols - i : __s216;
double *t27 = P + i*P_ncols;
double *t25 = t16 + i*P_ncols;
double *t26 = Q + i*P_ncols;
for (j=0; j<__m216; j+=1) {
// 6_2
double *t37 = t27 + j*P_ncols;
double *t35 = t25 + j*P_ncols;
double *t36 = t26 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t24);
free(t21);
}
