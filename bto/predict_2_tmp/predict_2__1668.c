#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m3950;
int P_ncols;
double *t24;
double *t32;
double *t26;
int __s3949;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t21;
int __m3948;
double *P;
double *t22;
int __s3947;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
int __m3948 = msg->__m3948;
double *P = msg->P;
double *t22 = msg->t22;
int __s3947 = msg->__s3947;

for (j=0; j<P_ncols; j+=__s3947) {
// 2_2
int __m3947 = j + __s3947 > P_ncols ? P_ncols - j : __s3947;
double *t34 = t22 + j;
double *t33 = P + j;
for (k=0; k<__m3948; k+=1) {
// 2_3
double *t45 = t34 + k*P_ncols;
double *t44 = t21 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3947; ++__zr__) t45[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t55 = t33 + l*P_ncols;
for (p=0; p<__m3947; p+=1) {
// 2_5
t45[p] += (t44[l]*t55[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m3950 = msg->__m3950;
int P_ncols = msg->P_ncols;
double *t24 = msg->t24;
double *t32 = msg->t32;
double *t26 = msg->t26;
int __s3949 = msg->__s3949;

for (j=0; j<P_ncols; j+=__s3949) {
// 4_2
int __m3949 = j + __s3949 > P_ncols ? P_ncols - j : __s3949;
double *t37 = t26 + j;
double *t43 = t32 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t48 = t37 + k*__m3949;
double *t47 = t24 + k*P_ncols;
for (l=0; l<__m3949; l+=1) {
// 4_4
double *t61 = t43 + l*P_ncols;
t48[l] = 0.0;
for (p=0; p<__m3950; p+=1) {
// 4_5
t48[l] += (t47[p]*t61[p]);
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

int __s3951 = 2;

int __s3949 = 512;

int __s3947 = 512;

int nparts__s3948 = 10;
int __s3948;
if (nparts__s3948 > 1 && P_ncols > nparts__s3948) {
__s3948 = P_ncols/nparts__s3948;
// this will fail if P_ncols%nparts__s3948+__s3948 > nparts__s3948
// which primarily effects small sizes
if (P_ncols%nparts__s3948)
++__s3948;
}
else {
__s3948 = P_ncols;
nparts__s3948 = 1;
}

int nparts__s3950 = 10;
int __s3950;
if (nparts__s3950 > 1 && P_ncols > nparts__s3950) {
__s3950 = P_ncols/nparts__s3950;
// this will fail if P_ncols%nparts__s3950+__s3950 > nparts__s3950
// which primarily effects small sizes
if (P_ncols%nparts__s3950)
++__s3950;
}
else {
__s3950 = P_ncols;
nparts__s3950 = 1;
}

double *t27 = malloc(sizeof(double)*nparts__s3950*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t27;
double *t13 = t27;
double *t69 = t27;
double *t15 = t23;
double *t9 = t23;
double *t11 = t23;
double *t10 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3948);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3948);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3948,ii+=1) {
// 2_1
int __m3948 = i + __s3948 > P_ncols ? P_ncols - i : __s3948;
double *t22 = t23 + i*P_ncols;
double *t21 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].__m3948 = __m3948;
predict_0[disp].P = P;
predict_0[disp].t22 = t22;
predict_0[disp].__s3947 = __s3947;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3948; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3950);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3950);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3950,ii+=1) {
// 4_1
int __m3950 = i + __s3950 > P_ncols ? P_ncols - i : __s3950;
double *t26 = t27 + ii*P_ncols*P_ncols;
double *t24 = t15 + i;
double *t32 = t17 + i;
predict_1[disp].__m3950 = __m3950;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t24 = t24;
predict_1[disp].t32 = t32;
predict_1[disp].t26 = t26;
predict_1[disp].__s3949 = __s3949;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3950; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s3950,ii+=1) {
// 4_1
int __m3950 = i + __s3950 > P_ncols ? P_ncols - i : __s3950;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s3949) {
int __m3949 = __j + __s3949 > P_ncols ? P_ncols - __j : __s3949;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3949; __l+=1) {
t69[__j+__k*P_ncols+__l] = t27[ii*P_ncols*P_ncols+__j+__k*__m3949+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s3949) {
int __m3949 = __j + __s3949 > P_ncols ? P_ncols - __j : __s3949;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3949; __l+=1) {
t69[__j+__k*P_ncols+__l] += t27[ii*P_ncols*P_ncols+__j+__k*__m3949+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s3951) {
// 6_1
int __m3951 = i + __s3951 > P_ncols ? P_ncols - i : __s3951;
double *t30 = P + i;
double *t28 = t18 + i;
double *t29 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t41 = t30 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
double *t40 = t29 + j*P_ncols;
for (k=0; k<__m3951; k+=1) {
// 6_3
t41[k] = (t39[k]+t40[k]);
}
}
}
free(t27);
free(t23);
}
