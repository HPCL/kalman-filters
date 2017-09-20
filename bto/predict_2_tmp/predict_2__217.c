#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t16;
int __m612;
double *t15;
double *t17;
int __s611;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t16 = msg->t16;
int __m612 = msg->__m612;
double *t15 = msg->t15;
double *t17 = msg->t17;
int __s611 = msg->__s611;

for (j=0; j<P_ncols; j+=__s611) {
// 2_2
int __m611 = j + __s611 > P_ncols ? P_ncols - j : __s611;
double *t27 = t17 + j*P_ncols;
double *t26 = t15 + j*P_ncols;
for (k=0; k<__m611; k+=1) {
// 2_3
double *t38 = t27 + k*P_ncols;
double *t37 = t26 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t38[__zr__] = 0.0;
for (l=0; l<__m612; l+=1) {
// 2_4
double *t49 = t16 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t38[p] += (t37[l]*t49[p]);
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

int __s613 = 2;

int __s611 = 504;

int nparts__s612 = 8;
int __s612;
if (nparts__s612 > 1 && P_ncols > nparts__s612) {
__s612 = P_ncols/nparts__s612;
// this will fail if P_ncols%nparts__s612+__s612 > nparts__s612
// which primarily effects small sizes
if (P_ncols%nparts__s612)
++__s612;
}
else {
__s612 = P_ncols;
nparts__s612 = 1;
}

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*nparts__s612*P_ncols*P_ncols);
double *t12 = t21;
double *t9 = t18;
double *t55 = t18;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s612);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s612);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s612,ii+=1) {
// 2_1
int __m612 = i + __s612 > P_ncols ? P_ncols - i : __s612;
double *t17 = t18 + ii*P_ncols*P_ncols;
double *t15 = t10 + i;
double *t16 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t16 = t16;
predict_0[disp].__m612 = __m612;
predict_0[disp].t15 = t15;
predict_0[disp].t17 = t17;
predict_0[disp].__s611 = __s611;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s612; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s612,ii+=1) {
// 2_1
int __m612 = i + __s612 > P_ncols ? P_ncols - i : __s612;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s611) {
int __m611 = __j + __s611 > P_ncols ? P_ncols - __j : __s611;
for (__k = 0; __k < __m611; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t55[__j*P_ncols+__k*P_ncols+__l] = t18[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s611) {
int __m611 = __j + __s611 > P_ncols ? P_ncols - __j : __s611;
for (__k = 0; __k < __m611; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t55[__j*P_ncols+__k*P_ncols+__l] += t18[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t20 = t21 + i*P_ncols;
double *t19 = t9 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t36 = A + j*P_ncols;
t20[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t20[j] += (t19[k]*t36[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s613) {
// 6_1
int __m613 = i + __s613 > P_ncols ? P_ncols - i : __s613;
double *t24 = P + i*P_ncols;
double *t22 = t12 + i*P_ncols;
double *t23 = Q + i*P_ncols;
for (j=0; j<__m613; j+=1) {
// 6_2
double *t34 = t24 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t34[k] = (t32[k]+t33[k]);
}
}
}
free(t21);
free(t18);
}
