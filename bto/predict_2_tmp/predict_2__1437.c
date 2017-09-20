#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m3416;
double *t12;
double *t13;
double *t14;
int __s3415;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m3416 = msg->__m3416;
double *t12 = msg->t12;
double *t13 = msg->t13;
double *t14 = msg->t14;
int __s3415 = msg->__s3415;

for (j=0; j<P_ncols; j+=__s3415) {
// 2_2
int __m3415 = j + __s3415 > P_ncols ? P_ncols - j : __s3415;
double *t24 = t14 + j;
double *t23 = t13 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t35 = t24 + k*__m3415;
double *t34 = t12 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3415; ++__zr__) t35[__zr__] = 0.0;
for (l=0; l<__m3416; l+=1) {
// 2_4
double *t42 = t23 + l*P_ncols;
for (p=0; p<__m3415; p+=1) {
// 2_5
t35[p] += (t34[l]*t42[p]);
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

int __s3415 = 512;

int nparts__s3416 = 12;
int __s3416;
if (nparts__s3416 > 1 && P_ncols > nparts__s3416) {
__s3416 = P_ncols/nparts__s3416;
// this will fail if P_ncols%nparts__s3416+__s3416 > nparts__s3416
// which primarily effects small sizes
if (P_ncols%nparts__s3416)
++__s3416;
}
else {
__s3416 = P_ncols;
nparts__s3416 = 1;
}

double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = malloc(sizeof(double)*nparts__s3416*P_ncols*P_ncols);
double *t9 = t15;
double *t48 = t15;
double *t10 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3416);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3416);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3416,ii+=1) {
// 2_1
int __m3416 = i + __s3416 > P_ncols ? P_ncols - i : __s3416;
double *t14 = t15 + ii*P_ncols*P_ncols;
double *t12 = t10 + i;
double *t13 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m3416 = __m3416;
predict_0[disp].t12 = t12;
predict_0[disp].t13 = t13;
predict_0[disp].t14 = t14;
predict_0[disp].__s3415 = __s3415;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3416; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s3416,ii+=1) {
// 2_1
int __m3416 = i + __s3416 > P_ncols ? P_ncols - i : __s3416;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s3415) {
int __m3415 = __j + __s3415 > P_ncols ? P_ncols - __j : __s3415;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3415; __l+=1) {
t48[__j+__k*P_ncols+__l] = t15[ii*P_ncols*P_ncols+__j+__k*__m3415+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s3415) {
int __m3415 = __j + __s3415 > P_ncols ? P_ncols - __j : __s3415;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3415; __l+=1) {
t48[__j+__k*P_ncols+__l] += t15[ii*P_ncols*P_ncols+__j+__k*__m3415+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t17 = t18 + i*P_ncols;
double *t16 = t9 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t33 = A + j*P_ncols;
t17[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t17[j] += (t16[k]*t33[k]);
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t21 = P + i*P_ncols;
double *t19 = t18 + i*P_ncols;
double *t20 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t21[j] = (t19[j]+t20[j]);
}
}
free(t18);
free(t15);
}
