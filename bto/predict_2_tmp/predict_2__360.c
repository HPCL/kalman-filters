#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t28;
int __m976;
double *t12;
double *t22;
int __s975;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t18;
int __m974;
double *t17;
double *t19;
int __s973;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t18 = msg->t18;
int __m974 = msg->__m974;
double *t17 = msg->t17;
double *t19 = msg->t19;
int __s973 = msg->__s973;

for (j=0; j<P_ncols; j+=__s973) {
// 2_2
int __m973 = j + __s973 > P_ncols ? P_ncols - j : __s973;
double *t30 = t19 + j*P_ncols;
double *t29 = t17 + j*P_ncols;
for (k=0; k<__m973; k+=1) {
// 2_3
double *t40 = t30 + k*P_ncols;
double *t39 = t29 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t40[__zr__] = 0.0;
for (l=0; l<__m974; l+=1) {
// 2_4
double *t46 = t18 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t40[p] += (t39[l]*t46[p]);
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
double *t28 = msg->t28;
int __m976 = msg->__m976;
double *t12 = msg->t12;
double *t22 = msg->t22;
int __s975 = msg->__s975;

for (j=0; j<P_ncols; j+=__s975) {
// 4_2
int __m975 = j + __s975 > P_ncols ? P_ncols - j : __s975;
double *t33 = t22 + j*P_ncols;
double *t32 = t12 + j*P_ncols;
for (k=0; k<__m975; k+=1) {
// 4_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (l=0; l<__m976; l+=1) {
// 4_4
double *t52 = t28 + l*P_ncols;
t43[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t43[l] += (t42[p]*t52[p]);
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

int __s975 = 504;

int __s973 = 512;

int nparts__s974 = 12;
int __s974;
if (nparts__s974 > 1 && P_ncols > nparts__s974) {
__s974 = P_ncols/nparts__s974;
// this will fail if P_ncols%nparts__s974+__s974 > nparts__s974
// which primarily effects small sizes
if (P_ncols%nparts__s974)
++__s974;
}
else {
__s974 = P_ncols;
nparts__s974 = 1;
}

int nparts__s976 = 12;
int __s976;
if (nparts__s976 > 1 && P_ncols > nparts__s976) {
__s976 = P_ncols/nparts__s976;
// this will fail if P_ncols%nparts__s976+__s976 > nparts__s976
// which primarily effects small sizes
if (P_ncols%nparts__s976)
++__s976;
}
else {
__s976 = P_ncols;
nparts__s976 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*nparts__s974*P_ncols*P_ncols);
double *t13 = t23;
double *t15 = t23;
double *t12 = t20;
double *t9 = t20;
double *t60 = t20;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s974);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s974);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s974,ii+=1) {
// 2_1
int __m974 = i + __s974 > P_ncols ? P_ncols - i : __s974;
double *t19 = t20 + ii*P_ncols*P_ncols;
double *t17 = t10 + i;
double *t18 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t18 = t18;
predict_0[disp].__m974 = __m974;
predict_0[disp].t17 = t17;
predict_0[disp].t19 = t19;
predict_0[disp].__s973 = __s973;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s974; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s974,ii+=1) {
// 2_1
int __m974 = i + __s974 > P_ncols ? P_ncols - i : __s974;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s973) {
int __m973 = __j + __s973 > P_ncols ? P_ncols - __j : __s973;
for (__k = 0; __k < __m973; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t60[__j*P_ncols+__k*P_ncols+__l] = t20[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s973) {
int __m973 = __j + __s973 > P_ncols ? P_ncols - __j : __s973;
for (__k = 0; __k < __m973; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t60[__j*P_ncols+__k*P_ncols+__l] += t20[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s976);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s976);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s976,ii+=1) {
// 4_1
int __m976 = i + __s976 > P_ncols ? P_ncols - i : __s976;
double *t22 = t23 + i;
double *t28 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].__m976 = __m976;
predict_1[disp].t12 = t12;
predict_1[disp].t22 = t22;
predict_1[disp].__s975 = __s975;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s976; ++disp) {
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
