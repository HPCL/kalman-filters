#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m3804;
int P_ncols;
double *t21;
double *t29;
double *t23;
int __s3803;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t18;
int __m3802;
double *P;
double *t19;
int __s3801;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t18 = msg->t18;
int __m3802 = msg->__m3802;
double *P = msg->P;
double *t19 = msg->t19;
int __s3801 = msg->__s3801;

for (j=0; j<P_ncols; j+=__s3801) {
// 2_2
int __m3801 = j + __s3801 > P_ncols ? P_ncols - j : __s3801;
double *t31 = t19 + j;
double *t30 = P + j;
for (k=0; k<__m3802; k+=1) {
// 2_3
double *t42 = t31 + k*P_ncols;
double *t41 = t18 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3801; ++__zr__) t42[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t48 = t30 + l*P_ncols;
for (p=0; p<__m3801; p+=1) {
// 2_5
t42[p] += (t41[l]*t48[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m3804 = msg->__m3804;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
double *t29 = msg->t29;
double *t23 = msg->t23;
int __s3803 = msg->__s3803;

for (j=0; j<P_ncols; j+=__s3803) {
// 4_2
int __m3803 = j + __s3803 > P_ncols ? P_ncols - j : __s3803;
double *t34 = t23 + j;
double *t40 = t29 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t45 = t34 + k*__m3803;
double *t44 = t21 + k*P_ncols;
for (l=0; l<__m3803; l+=1) {
// 4_4
double *t54 = t40 + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<__m3804; p+=1) {
// 4_5
t45[l] += (t44[p]*t54[p]);
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

int __s3803 = 512;

int __s3801 = 512;

int nparts__s3802 = 10;
int __s3802;
if (nparts__s3802 > 1 && P_ncols > nparts__s3802) {
__s3802 = P_ncols/nparts__s3802;
// this will fail if P_ncols%nparts__s3802+__s3802 > nparts__s3802
// which primarily effects small sizes
if (P_ncols%nparts__s3802)
++__s3802;
}
else {
__s3802 = P_ncols;
nparts__s3802 = 1;
}

int nparts__s3804 = 10;
int __s3804;
if (nparts__s3804 > 1 && P_ncols > nparts__s3804) {
__s3804 = P_ncols/nparts__s3804;
// this will fail if P_ncols%nparts__s3804+__s3804 > nparts__s3804
// which primarily effects small sizes
if (P_ncols%nparts__s3804)
++__s3804;
}
else {
__s3804 = P_ncols;
nparts__s3804 = 1;
}

double *t24 = malloc(sizeof(double)*nparts__s3804*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t24;
double *t62 = t24;
double *t15 = t20;
double *t9 = t20;
double *t11 = t20;
double *t10 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3802);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3802);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3802,ii+=1) {
// 2_1
int __m3802 = i + __s3802 > P_ncols ? P_ncols - i : __s3802;
double *t19 = t20 + i*P_ncols;
double *t18 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t18 = t18;
predict_0[disp].__m3802 = __m3802;
predict_0[disp].P = P;
predict_0[disp].t19 = t19;
predict_0[disp].__s3801 = __s3801;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3802; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3804);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3804);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3804,ii+=1) {
// 4_1
int __m3804 = i + __s3804 > P_ncols ? P_ncols - i : __s3804;
double *t23 = t24 + ii*P_ncols*P_ncols;
double *t21 = t15 + i;
double *t29 = t17 + i;
predict_1[disp].__m3804 = __m3804;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t21 = t21;
predict_1[disp].t29 = t29;
predict_1[disp].t23 = t23;
predict_1[disp].__s3803 = __s3803;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3804; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s3804,ii+=1) {
// 4_1
int __m3804 = i + __s3804 > P_ncols ? P_ncols - i : __s3804;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s3803) {
int __m3803 = __j + __s3803 > P_ncols ? P_ncols - __j : __s3803;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3803; __l+=1) {
t62[__j+__k*P_ncols+__l] = t24[ii*P_ncols*P_ncols+__j+__k*__m3803+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s3803) {
int __m3803 = __j + __s3803 > P_ncols ? P_ncols - __j : __s3803;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3803; __l+=1) {
t62[__j+__k*P_ncols+__l] += t24[ii*P_ncols*P_ncols+__j+__k*__m3803+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t27 = P + i*P_ncols;
double *t25 = t13 + i*P_ncols;
double *t26 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t27[j] = (t25[j]+t26[j]);
}
}
free(t24);
free(t20);
}
