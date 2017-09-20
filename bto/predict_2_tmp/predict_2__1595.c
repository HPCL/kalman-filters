#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t28;
double *t22;
int __s3775;
int __m3776;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t18;
int __m3774;
double *P;
double *t19;
int __s3773;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t18 = msg->t18;
int __m3774 = msg->__m3774;
double *P = msg->P;
double *t19 = msg->t19;
int __s3773 = msg->__s3773;

for (j=0; j<P_ncols; j+=__s3773) {
// 2_2
int __m3773 = j + __s3773 > P_ncols ? P_ncols - j : __s3773;
double *t30 = t19 + j;
double *t29 = P + j;
for (k=0; k<__m3774; k+=1) {
// 2_3
double *t41 = t30 + k*P_ncols;
double *t40 = t18 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3773; ++__zr__) t41[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t47 = t29 + l*P_ncols;
for (p=0; p<__m3773; p+=1) {
// 2_5
t41[p] += (t40[l]*t47[p]);
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
double *t9 = msg->t9;
double *t28 = msg->t28;
double *t22 = msg->t22;
int __s3775 = msg->__s3775;
int __m3776 = msg->__m3776;

for (j=0; j<__m3776; j+=__s3775) {
// 4_2
int __m3775 = j + __s3775 > __m3776 ? __m3776 - j : __s3775;
double *t33 = t22 + j;
double *t39 = t28 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t44 = t33 + k*P_ncols;
double *t43 = t9 + k*P_ncols;
for (l=0; l<__m3775; l+=1) {
// 4_4
double *t53 = t39 + l*P_ncols;
t44[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t44[l] += (t43[p]*t53[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j;

int __s3775 = 496;

int __s3773 = 512;

int nparts__s3776 = 12;
int __s3776;
if (nparts__s3776 > 1 && P_ncols > nparts__s3776) {
__s3776 = P_ncols/nparts__s3776;
// this will fail if P_ncols%nparts__s3776+__s3776 > nparts__s3776
// which primarily effects small sizes
if (P_ncols%nparts__s3776)
++__s3776;
}
else {
__s3776 = P_ncols;
nparts__s3776 = 1;
}

int nparts__s3774 = 12;
int __s3774;
if (nparts__s3774 > 1 && P_ncols > nparts__s3774) {
__s3774 = P_ncols/nparts__s3774;
// this will fail if P_ncols%nparts__s3774+__s3774 > nparts__s3774
// which primarily effects small sizes
if (P_ncols%nparts__s3774)
++__s3774;
}
else {
__s3774 = P_ncols;
nparts__s3774 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t23;
double *t16 = t23;
double *t9 = t20;
double *t11 = t20;
double *t10 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3774);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3774);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3774,ii+=1) {
// 2_1
int __m3774 = i + __s3774 > P_ncols ? P_ncols - i : __s3774;
double *t19 = t20 + i*P_ncols;
double *t18 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t18 = t18;
predict_0[disp].__m3774 = __m3774;
predict_0[disp].P = P;
predict_0[disp].t19 = t19;
predict_0[disp].__s3773 = __s3773;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3774; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3776);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3776);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3776,ii+=1) {
// 4_1
int __m3776 = i + __s3776 > P_ncols ? P_ncols - i : __s3776;
double *t22 = t23 + i;
double *t28 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t28 = t28;
predict_1[disp].t22 = t22;
predict_1[disp].__s3775 = __s3775;
predict_1[disp].__m3776 = __m3776;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3776; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t26 = P + i*P_ncols;
double *t24 = t13 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t26[j] = (t24[j]+t25[j]);
}
}
free(t23);
free(t20);
}
