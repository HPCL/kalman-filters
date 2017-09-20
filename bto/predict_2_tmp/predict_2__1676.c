#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t31;
double *t25;
int __s3976;
int __m3977;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t21;
int __m3975;
double *P;
double *t22;
int __s3974;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
int __m3975 = msg->__m3975;
double *P = msg->P;
double *t22 = msg->t22;
int __s3974 = msg->__s3974;

for (j=0; j<P_ncols; j+=__s3974) {
// 2_2
int __m3974 = j + __s3974 > P_ncols ? P_ncols - j : __s3974;
double *t33 = t22 + j;
double *t32 = P + j;
for (k=0; k<__m3975; k+=1) {
// 2_3
double *t44 = t33 + k*P_ncols;
double *t43 = t21 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3974; ++__zr__) t44[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t54 = t32 + l*P_ncols;
for (p=0; p<__m3974; p+=1) {
// 2_5
t44[p] += (t43[l]*t54[p]);
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
double *t31 = msg->t31;
double *t25 = msg->t25;
int __s3976 = msg->__s3976;
int __m3977 = msg->__m3977;

for (j=0; j<__m3977; j+=__s3976) {
// 4_2
int __m3976 = j + __s3976 > __m3977 ? __m3977 - j : __s3976;
double *t36 = t25 + j;
double *t42 = t31 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t47 = t36 + k*P_ncols;
double *t46 = t9 + k*P_ncols;
for (l=0; l<__m3976; l+=1) {
// 4_4
double *t60 = t42 + l*P_ncols;
t47[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t47[l] += (t46[p]*t60[p]);
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

int __s3978 = 10;

int __s3976 = 512;

int __s3974 = 512;

int nparts__s3977 = 10;
int __s3977;
if (nparts__s3977 > 1 && P_ncols > nparts__s3977) {
__s3977 = P_ncols/nparts__s3977;
// this will fail if P_ncols%nparts__s3977+__s3977 > nparts__s3977
// which primarily effects small sizes
if (P_ncols%nparts__s3977)
++__s3977;
}
else {
__s3977 = P_ncols;
nparts__s3977 = 1;
}

int nparts__s3975 = 8;
int __s3975;
if (nparts__s3975 > 1 && P_ncols > nparts__s3975) {
__s3975 = P_ncols/nparts__s3975;
// this will fail if P_ncols%nparts__s3975+__s3975 > nparts__s3975
// which primarily effects small sizes
if (P_ncols%nparts__s3975)
++__s3975;
}
else {
__s3975 = P_ncols;
nparts__s3975 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t26;
double *t13 = t26;
double *t16 = t26;
double *t9 = t23;
double *t11 = t23;
double *t10 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3975);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3975);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3975,ii+=1) {
// 2_1
int __m3975 = i + __s3975 > P_ncols ? P_ncols - i : __s3975;
double *t22 = t23 + i*P_ncols;
double *t21 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].__m3975 = __m3975;
predict_0[disp].P = P;
predict_0[disp].t22 = t22;
predict_0[disp].__s3974 = __s3974;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3975; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3977);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3977);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3977,ii+=1) {
// 4_1
int __m3977 = i + __s3977 > P_ncols ? P_ncols - i : __s3977;
double *t25 = t26 + i;
double *t31 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t31 = t31;
predict_1[disp].t25 = t25;
predict_1[disp].__s3976 = __s3976;
predict_1[disp].__m3977 = __m3977;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3977; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s3978) {
// 6_1
int __m3978 = i + __s3978 > P_ncols ? P_ncols - i : __s3978;
double *t29 = P + i;
double *t27 = t18 + i;
double *t28 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m3978; k+=1) {
// 6_3
t40[k] = (t38[k]+t39[k]);
}
}
}
free(t26);
free(t23);
}
