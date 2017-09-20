#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t29;
double *t16;
double *t15;
int __s2476;
int __m2477;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t16 = msg->t16;
double *t15 = msg->t15;
int __s2476 = msg->__s2476;
int __m2477 = msg->__m2477;

for (j=0; j<__m2477; j+=__s2476) {
// 2_2
int __m2476 = j + __s2476 > __m2477 ? __m2477 - j : __s2476;
double *t26 = t15 + j;
double *t27 = t16 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t39 = t29 + k*P_ncols;
double *t38 = t26 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t39[__zr__] = 0.0;
for (l=0; l<__m2476; l+=1) {
// 2_4
double *t50 = t27 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t39[p] += (t38[l]*t50[p]);
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

int __s2478 = 2;

int __s2476 = 512;

int nparts__s2477 = 12;
int __s2477;
if (nparts__s2477 > 1 && P_ncols > nparts__s2477) {
__s2477 = P_ncols/nparts__s2477;
// this will fail if P_ncols%nparts__s2477+__s2477 > nparts__s2477
// which primarily effects small sizes
if (P_ncols%nparts__s2477)
++__s2477;
}
else {
__s2477 = P_ncols;
nparts__s2477 = 1;
}

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*nparts__s2477*P_ncols*P_ncols);
double *t12 = t21;
double *t56 = t18;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2477);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2477);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2477,ii+=1) {
// 2_1
int __m2477 = i + __s2477 > P_ncols ? P_ncols - i : __s2477;
double *t29 = t18 + ii*P_ncols*P_ncols;
double *t15 = t10 + i;
double *t16 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t29 = t29;
predict_0[disp].t16 = t16;
predict_0[disp].t15 = t15;
predict_0[disp].__s2476 = __s2476;
predict_0[disp].__m2477 = __m2477;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2477; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2477,ii+=1) {
// 2_1
int __m2477 = i + __s2477 > P_ncols ? P_ncols - i : __s2477;
if ((ii == 0)) {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t56[__k*P_ncols+__l] = t18[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
} else {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t56[__k*P_ncols+__l] += t18[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
}
}
}

for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t20 = t21 + i*P_ncols;
double *t19 = t56 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t37 = A + j*P_ncols;
t20[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t20[j] += (t19[k]*t37[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s2478) {
// 6_1
int __m2478 = i + __s2478 > P_ncols ? P_ncols - i : __s2478;
double *t24 = P + i*P_ncols;
double *t22 = t12 + i*P_ncols;
double *t23 = Q + i*P_ncols;
for (j=0; j<__m2478; j+=1) {
// 6_2
double *t35 = t24 + j*P_ncols;
double *t33 = t22 + j*P_ncols;
double *t34 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t35[k] = (t33[k]+t34[k]);
}
}
}
free(t21);
free(t18);
}
