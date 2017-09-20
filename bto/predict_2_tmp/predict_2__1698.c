#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t28;
double *t27;
double *t29;
int __s4022;
int __m4023;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t22;
int __m4020;
double *P;
double *t21;
int __s4019;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t22 = msg->t22;
int __m4020 = msg->__m4020;
double *P = msg->P;
double *t21 = msg->t21;
int __s4019 = msg->__s4019;

for (j=0; j<P_ncols; j+=__s4019) {
// 2_2
int __m4019 = j + __s4019 > P_ncols ? P_ncols - j : __s4019;
double *t32 = t21 + j;
double *t33 = P + j*P_ncols;
for (k=0; k<__m4020; k+=1) {
// 2_3
double *t44 = t22 + k*P_ncols;
double *t43 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t44[__zr__] = 0.0;
for (l=0; l<__m4019; l+=1) {
// 2_4
double *t55 = t33 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t44[p] += (t43[l]*t55[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s4022 = msg->__s4022;
int __m4023 = msg->__m4023;

for (j=0; j<__m4023; j+=__s4022) {
// 6_2
int __m4022 = j + __s4022 > __m4023 ? __m4023 - j : __s4022;
double *t41 = t29 + j;
double *t39 = t27 + j;
double *t40 = t28 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t51 = t41 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
double *t50 = t40 + k*P_ncols;
for (l=0; l<__m4022; l+=1) {
// 6_4
t51[l] = (t49[l]+t50[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s4022 = 496;

int __s4021 = 10;

int __s4019 = 512;

int nparts__s4023 = 10;
int __s4023;
if (nparts__s4023 > 1 && P_ncols > nparts__s4023) {
__s4023 = P_ncols/nparts__s4023;
// this will fail if P_ncols%nparts__s4023+__s4023 > nparts__s4023
// which primarily effects small sizes
if (P_ncols%nparts__s4023)
++__s4023;
}
else {
__s4023 = P_ncols;
nparts__s4023 = 1;
}

int nparts__s4020 = 8;
int __s4020;
if (nparts__s4020 > 1 && P_ncols > nparts__s4020) {
__s4020 = P_ncols/nparts__s4020;
// this will fail if P_ncols%nparts__s4020+__s4020 > nparts__s4020
// which primarily effects small sizes
if (P_ncols%nparts__s4020)
++__s4020;
}
else {
__s4020 = P_ncols;
nparts__s4020 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t26;
double *t15 = t26;
double *t13 = t26;
double *t11 = t23;
double *t10 = A;
double *t8 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4020);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4020);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4020,ii+=1) {
// 2_1
int __m4020 = i + __s4020 > P_ncols ? P_ncols - i : __s4020;
double *t22 = t23 + i*P_ncols;
double *t21 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t22 = t22;
predict_0[disp].__m4020 = __m4020;
predict_0[disp].P = P;
predict_0[disp].t21 = t21;
predict_0[disp].__s4019 = __s4019;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4020; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s4021) {
// 4_1
int __m4021 = i + __s4021 > P_ncols ? P_ncols - i : __s4021;
double *t25 = t26 + i;
double *t31 = t14 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t37 = t25 + j*P_ncols;
double *t36 = t11 + j*P_ncols;
for (k=0; k<__m4021; k+=1) {
// 4_3
double *t53 = t31 + k*P_ncols;
t37[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t37[k] += (t36[l]*t53[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s4023);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s4023);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4023,ii+=1) {
// 6_1
int __m4023 = i + __s4023 > P_ncols ? P_ncols - i : __s4023;
double *t29 = P + i;
double *t27 = t18 + i;
double *t28 = Q + i;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s4022 = __s4022;
predict_1[disp].__m4023 = __m4023;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s4023; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t26);
free(t23);
}
