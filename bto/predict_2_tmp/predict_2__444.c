#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t30;
int __m1166;
double *t12;
double *t24;
int __s1165;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *P;
double *t20;
double *t21;
int __s1163;
int __m1164;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t20 = msg->t20;
double *t21 = msg->t21;
int __s1163 = msg->__s1163;
int __m1164 = msg->__m1164;

for (j=0; j<__m1164; j+=__s1163) {
// 2_2
int __m1163 = j + __s1163 > __m1164 ? __m1164 - j : __s1163;
double *t32 = t21 + j*P_ncols;
double *t31 = t20 + j*P_ncols;
for (k=0; k<__m1163; k+=1) {
// 2_3
double *t42 = t32 + k*P_ncols;
double *t41 = t31 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t42[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t52 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t42[p] += (t41[l]*t52[p]);
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
double *t30 = msg->t30;
int __m1166 = msg->__m1166;
double *t12 = msg->t12;
double *t24 = msg->t24;
int __s1165 = msg->__s1165;

for (j=0; j<P_ncols; j+=__s1165) {
// 4_2
int __m1165 = j + __s1165 > P_ncols ? P_ncols - j : __s1165;
double *t35 = t24 + j*P_ncols;
double *t34 = t12 + j*P_ncols;
for (k=0; k<__m1165; k+=1) {
// 4_3
double *t45 = t35 + k*P_ncols;
double *t44 = t34 + k*P_ncols;
for (l=0; l<__m1166; l+=1) {
// 4_4
double *t58 = t30 + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t45[l] += (t44[p]*t58[p]);
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

int __s1167 = 12;

int __s1165 = 512;

int __s1163 = 512;

int nparts__s1164 = 12;
int __s1164;
if (nparts__s1164 > 1 && P_ncols > nparts__s1164) {
__s1164 = P_ncols/nparts__s1164;
// this will fail if P_ncols%nparts__s1164+__s1164 > nparts__s1164
// which primarily effects small sizes
if (P_ncols%nparts__s1164)
++__s1164;
}
else {
__s1164 = P_ncols;
nparts__s1164 = 1;
}

int nparts__s1166 = 12;
int __s1166;
if (nparts__s1166 > 1 && P_ncols > nparts__s1166) {
__s1166 = P_ncols/nparts__s1166;
// this will fail if P_ncols%nparts__s1166+__s1166 > nparts__s1166
// which primarily effects small sizes
if (P_ncols%nparts__s1166)
++__s1166;
}
else {
__s1166 = P_ncols;
nparts__s1166 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = t25;
double *t13 = t25;
double *t15 = t25;
double *t12 = t22;
double *t9 = t22;
double *t11 = t22;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1164);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1164);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1164,ii+=1) {
// 2_1
int __m1164 = i + __s1164 > P_ncols ? P_ncols - i : __s1164;
double *t21 = t22 + i*P_ncols;
double *t20 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t20 = t20;
predict_0[disp].t21 = t21;
predict_0[disp].__s1163 = __s1163;
predict_0[disp].__m1164 = __m1164;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1164; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1166);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1166);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1166,ii+=1) {
// 4_1
int __m1166 = i + __s1166 > P_ncols ? P_ncols - i : __s1166;
double *t24 = t25 + i;
double *t30 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t30 = t30;
predict_1[disp].__m1166 = __m1166;
predict_1[disp].t12 = t12;
predict_1[disp].t24 = t24;
predict_1[disp].__s1165 = __s1165;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1166; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s1167) {
// 6_1
int __m1167 = i + __s1167 > P_ncols ? P_ncols - i : __s1167;
double *t28 = P + i*P_ncols;
double *t26 = t17 + i*P_ncols;
double *t27 = Q + i*P_ncols;
for (j=0; j<__m1167; j+=1) {
// 6_2
double *t39 = t28 + j*P_ncols;
double *t37 = t26 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t39[k] = (t37[k]+t38[k]);
}
}
}
free(t25);
free(t22);
}
