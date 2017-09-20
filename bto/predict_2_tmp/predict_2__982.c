#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t31;
double *t18;
double *t17;
int __s2509;
int __m2510;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t31 = msg->t31;
double *t18 = msg->t18;
double *t17 = msg->t17;
int __s2509 = msg->__s2509;
int __m2510 = msg->__m2510;

for (j=0; j<__m2510; j+=__s2509) {
// 2_2
int __m2509 = j + __s2509 > __m2510 ? __m2510 - j : __s2509;
double *t28 = t17 + j;
double *t29 = t18 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t40 = t31 + k*P_ncols;
double *t39 = t28 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t40[__zr__] = 0.0;
for (l=0; l<__m2509; l+=1) {
// 2_4
double *t51 = t29 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t40[p] += (t39[l]*t51[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s2512 = 2;

int __s2511 = 2;

int __s2509 = 512;

int nparts__s2510 = 12;
int __s2510;
if (nparts__s2510 > 1 && P_ncols > nparts__s2510) {
__s2510 = P_ncols/nparts__s2510;
// this will fail if P_ncols%nparts__s2510+__s2510 > nparts__s2510
// which primarily effects small sizes
if (P_ncols%nparts__s2510)
++__s2510;
}
else {
__s2510 = P_ncols;
nparts__s2510 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*nparts__s2510*P_ncols*P_ncols);
double *t14 = t23;
double *t13 = t23;
double *t12 = t20;
double *t61 = t20;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2510);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2510);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2510,ii+=1) {
// 2_1
int __m2510 = i + __s2510 > P_ncols ? P_ncols - i : __s2510;
double *t31 = t20 + ii*P_ncols*P_ncols;
double *t17 = t10 + i;
double *t18 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t31 = t31;
predict_0[disp].t18 = t18;
predict_0[disp].t17 = t17;
predict_0[disp].__s2509 = __s2509;
predict_0[disp].__m2510 = __m2510;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2510; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2510,ii+=1) {
// 2_1
int __m2510 = i + __s2510 > P_ncols ? P_ncols - i : __s2510;
if ((ii == 0)) {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t61[__k*P_ncols+__l] = t20[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
} else {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t61[__k*P_ncols+__l] += t20[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s2511) {
// 4_1
int __m2511 = i + __s2511 > P_ncols ? P_ncols - i : __s2511;
double *t22 = t23 + i*P_ncols;
double *t21 = t12 + i*P_ncols;
for (j=0; j<__m2511; j+=1) {
// 4_2
double *t33 = t22 + j*P_ncols;
double *t32 = t21 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t49 = A + k*P_ncols;
t33[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t33[k] += (t32[l]*t49[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s2512) {
// 6_1
int __m2512 = i + __s2512 > P_ncols ? P_ncols - i : __s2512;
double *t26 = P + i*P_ncols;
double *t24 = t14 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<__m2512; j+=1) {
// 6_2
double *t37 = t26 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t23);
free(t20);
}
