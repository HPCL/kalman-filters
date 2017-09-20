#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2023;
int P_ncols;
double *t29;
double *t28;
double *t30;
int __s2022;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t26;
int __s2020;
int __m2019;
double *P;
double *t22;
int __s2018;
int __s2019;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t26 = msg->t26;
int __s2020 = msg->__s2020;
int __m2019 = msg->__m2019;
double *P = msg->P;
double *t22 = msg->t22;
int __s2018 = msg->__s2018;
int __s2019 = msg->__s2019;

double *t23 = malloc(sizeof(double)*__s2019*P_ncols);
for (j=0; j<__m2019; j+=__s2018) {
// 2_2
int __m2018 = j + __s2018 > __m2019 ? __m2019 - j : __s2018;
double *t33 = t23 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<__m2018; k+=1) {
// 2_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t53 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t43[p] += (t42[l]*t53[p]);
}
}
}
}
for (j=0; j<__m2019; j+=__s2020) {
// 4_2
int __m2020 = j + __s2020 > __m2019 ? __m2019 - j : __s2020;
double *t36 = t26 + j*P_ncols;
double *t35 = t23 + j*P_ncols;
for (k=0; k<__m2020; k+=1) {
// 4_3
double *t46 = t36 + k*P_ncols;
double *t45 = t35 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t63 = A + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t46[l] += (t45[p]*t63[p]);
}
}
}
}
free(t23);
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m2023 = msg->__m2023;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t28 = msg->t28;
double *t30 = msg->t30;
int __s2022 = msg->__s2022;

for (j=0; j<P_ncols; j+=__s2022) {
// 6_2
int __m2022 = j + __s2022 > P_ncols ? P_ncols - j : __s2022;
double *t40 = t30 + j*P_ncols;
double *t38 = t28 + j*P_ncols;
double *t39 = t29 + j*P_ncols;
for (k=0; k<__m2022; k+=1) {
// 6_3
double *t50 = t40 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<__m2023; l+=1) {
// 6_4
t50[l] = (t48[l]+t49[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s2022 = 512;

int __s2020 = 504;

int __s2018 = 504;

int nparts__s2019 = 12;
int __s2019;
if (nparts__s2019 > 1 && P_ncols > nparts__s2019) {
__s2019 = P_ncols/nparts__s2019;
// this will fail if P_ncols%nparts__s2019+__s2019 > nparts__s2019
// which primarily effects small sizes
if (P_ncols%nparts__s2019)
++__s2019;
}
else {
__s2019 = P_ncols;
nparts__s2019 = 1;
}

int nparts__s2023 = 12;
int __s2023;
if (nparts__s2023 > 1 && P_ncols > nparts__s2023) {
__s2023 = P_ncols/nparts__s2023;
// this will fail if P_ncols%nparts__s2023+__s2023 > nparts__s2023
// which primarily effects small sizes
if (P_ncols%nparts__s2023)
++__s2023;
}
else {
__s2023 = P_ncols;
nparts__s2023 = 1;
}

double *t27 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = t27;
double *t16 = t27;
double *t13 = t27;
double *t15 = t27;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2019);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2019);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2019,ii+=1) {
// 2_1
int __m2019 = i + __s2019 > P_ncols ? P_ncols - i : __s2019;
double *t26 = t27 + i*P_ncols;
double *t22 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t26 = t26;
predict_0[disp].__s2020 = __s2020;
predict_0[disp].__m2019 = __m2019;
predict_0[disp].P = P;
predict_0[disp].t22 = t22;
predict_0[disp].__s2018 = __s2018;
predict_0[disp].__s2019 = __s2019;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2019; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2023);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2023);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2023,ii+=1) {
// 6_1
int __m2023 = i + __s2023 > P_ncols ? P_ncols - i : __s2023;
double *t30 = P + i;
double *t28 = t19 + i;
double *t29 = Q + i;
predict_1[disp].__m2023 = __m2023;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t29 = t29;
predict_1[disp].t28 = t28;
predict_1[disp].t30 = t30;
predict_1[disp].__s2022 = __s2022;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2023; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t27);
}
