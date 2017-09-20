#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m3837;
int P_ncols;
double *t22;
double *t30;
double *t24;
int __s3836;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
int __m3835;
double *t18;
double *t19;
double *t20;
int __s3834;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m3835 = msg->__m3835;
double *t18 = msg->t18;
double *t19 = msg->t19;
double *t20 = msg->t20;
int __s3834 = msg->__s3834;

for (j=0; j<P_ncols; j+=__s3834) {
// 2_2
int __m3834 = j + __s3834 > P_ncols ? P_ncols - j : __s3834;
double *t32 = t20 + j;
double *t31 = t19 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t43 = t32 + k*__m3834;
double *t42 = t18 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3834; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<__m3835; l+=1) {
// 2_4
double *t49 = t31 + l*P_ncols;
for (p=0; p<__m3834; p+=1) {
// 2_5
t43[p] += (t42[l]*t49[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m3837 = msg->__m3837;
int P_ncols = msg->P_ncols;
double *t22 = msg->t22;
double *t30 = msg->t30;
double *t24 = msg->t24;
int __s3836 = msg->__s3836;

for (j=0; j<P_ncols; j+=__s3836) {
// 4_2
int __m3836 = j + __s3836 > P_ncols ? P_ncols - j : __s3836;
double *t35 = t24 + j;
double *t41 = t30 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t46 = t35 + k*__m3836;
double *t45 = t22 + k*P_ncols;
for (l=0; l<__m3836; l+=1) {
// 4_4
double *t55 = t41 + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<__m3837; p+=1) {
// 4_5
t46[l] += (t45[p]*t55[p]);
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

int __s3836 = 512;

int __s3834 = 512;

int nparts__s3835 = 8;
int __s3835;
if (nparts__s3835 > 1 && P_ncols > nparts__s3835) {
__s3835 = P_ncols/nparts__s3835;
// this will fail if P_ncols%nparts__s3835+__s3835 > nparts__s3835
// which primarily effects small sizes
if (P_ncols%nparts__s3835)
++__s3835;
}
else {
__s3835 = P_ncols;
nparts__s3835 = 1;
}

int nparts__s3837 = 8;
int __s3837;
if (nparts__s3837 > 1 && P_ncols > nparts__s3837) {
__s3837 = P_ncols/nparts__s3837;
// this will fail if P_ncols%nparts__s3837+__s3837 > nparts__s3837
// which primarily effects small sizes
if (P_ncols%nparts__s3837)
++__s3837;
}
else {
__s3837 = P_ncols;
nparts__s3837 = 1;
}

double *t25 = malloc(sizeof(double)*nparts__s3837*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*nparts__s3835*P_ncols*P_ncols);
double *t13 = t25;
double *t64 = t25;
double *t15 = t21;
double *t9 = t21;
double *t63 = t21;
double *t10 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3835);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3835);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3835,ii+=1) {
// 2_1
int __m3835 = i + __s3835 > P_ncols ? P_ncols - i : __s3835;
double *t20 = t21 + ii*P_ncols*P_ncols;
double *t18 = t10 + i;
double *t19 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m3835 = __m3835;
predict_0[disp].t18 = t18;
predict_0[disp].t19 = t19;
predict_0[disp].t20 = t20;
predict_0[disp].__s3834 = __s3834;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3835; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s3835,ii+=1) {
// 2_1
int __m3835 = i + __s3835 > P_ncols ? P_ncols - i : __s3835;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s3834) {
int __m3834 = __j + __s3834 > P_ncols ? P_ncols - __j : __s3834;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3834; __l+=1) {
t63[__j+__k*P_ncols+__l] = t21[ii*P_ncols*P_ncols+__j+__k*__m3834+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s3834) {
int __m3834 = __j + __s3834 > P_ncols ? P_ncols - __j : __s3834;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3834; __l+=1) {
t63[__j+__k*P_ncols+__l] += t21[ii*P_ncols*P_ncols+__j+__k*__m3834+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3837);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3837);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3837,ii+=1) {
// 4_1
int __m3837 = i + __s3837 > P_ncols ? P_ncols - i : __s3837;
double *t24 = t25 + ii*P_ncols*P_ncols;
double *t22 = t15 + i;
double *t30 = t17 + i;
predict_1[disp].__m3837 = __m3837;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t22 = t22;
predict_1[disp].t30 = t30;
predict_1[disp].t24 = t24;
predict_1[disp].__s3836 = __s3836;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3837; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s3837,ii+=1) {
// 4_1
int __m3837 = i + __s3837 > P_ncols ? P_ncols - i : __s3837;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s3836) {
int __m3836 = __j + __s3836 > P_ncols ? P_ncols - __j : __s3836;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3836; __l+=1) {
t64[__j+__k*P_ncols+__l] = t25[ii*P_ncols*P_ncols+__j+__k*__m3836+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s3836) {
int __m3836 = __j + __s3836 > P_ncols ? P_ncols - __j : __s3836;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3836; __l+=1) {
t64[__j+__k*P_ncols+__l] += t25[ii*P_ncols*P_ncols+__j+__k*__m3836+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t28 = P + i*P_ncols;
double *t26 = t13 + i*P_ncols;
double *t27 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t28[j] = (t26[j]+t27[j]);
}
}
free(t25);
free(t21);
}
