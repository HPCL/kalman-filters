#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t18;
int __m676;
double *t17;
double *t19;
int __s675;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t18 = msg->t18;
int __m676 = msg->__m676;
double *t17 = msg->t17;
double *t19 = msg->t19;
int __s675 = msg->__s675;

for (j=0; j<P_ncols; j+=__s675) {
// 2_2
int __m675 = j + __s675 > P_ncols ? P_ncols - j : __s675;
double *t29 = t19 + j*P_ncols;
double *t28 = t17 + j*P_ncols;
for (k=0; k<__m675; k+=1) {
// 2_3
double *t39 = t29 + k*P_ncols;
double *t38 = t28 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t39[__zr__] = 0.0;
for (l=0; l<__m676; l+=1) {
// 2_4
double *t50 = t18 + l*P_ncols;
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
int disp, __zr__,i,ii,j,k,l;

int __s678 = 2;

int __s677 = 2;

int __s675 = 504;

int nparts__s676 = 10;
int __s676;
if (nparts__s676 > 1 && P_ncols > nparts__s676) {
__s676 = P_ncols/nparts__s676;
// this will fail if P_ncols%nparts__s676+__s676 > nparts__s676
// which primarily effects small sizes
if (P_ncols%nparts__s676)
++__s676;
}
else {
__s676 = P_ncols;
nparts__s676 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*nparts__s676*P_ncols*P_ncols);
double *t14 = t23;
double *t13 = t23;
double *t12 = t20;
double *t9 = t20;
double *t60 = t20;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s676);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s676);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s676,ii+=1) {
// 2_1
int __m676 = i + __s676 > P_ncols ? P_ncols - i : __s676;
double *t19 = t20 + ii*P_ncols*P_ncols;
double *t17 = t10 + i;
double *t18 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t18 = t18;
predict_0[disp].__m676 = __m676;
predict_0[disp].t17 = t17;
predict_0[disp].t19 = t19;
predict_0[disp].__s675 = __s675;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s676; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s676,ii+=1) {
// 2_1
int __m676 = i + __s676 > P_ncols ? P_ncols - i : __s676;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s675) {
int __m675 = __j + __s675 > P_ncols ? P_ncols - __j : __s675;
for (__k = 0; __k < __m675; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t60[__j*P_ncols+__k*P_ncols+__l] = t20[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s675) {
int __m675 = __j + __s675 > P_ncols ? P_ncols - __j : __s675;
for (__k = 0; __k < __m675; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t60[__j*P_ncols+__k*P_ncols+__l] += t20[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s677) {
// 4_1
int __m677 = i + __s677 > P_ncols ? P_ncols - i : __s677;
double *t22 = t23 + i*P_ncols;
double *t21 = t12 + i*P_ncols;
for (j=0; j<__m677; j+=1) {
// 4_2
double *t32 = t22 + j*P_ncols;
double *t31 = t21 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t48 = A + k*P_ncols;
t32[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t32[k] += (t31[l]*t48[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s678) {
// 6_1
int __m678 = i + __s678 > P_ncols ? P_ncols - i : __s678;
double *t26 = P + i*P_ncols;
double *t24 = t14 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<__m678; j+=1) {
// 6_2
double *t36 = t26 + j*P_ncols;
double *t34 = t24 + j*P_ncols;
double *t35 = t25 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t36[k] = (t34[k]+t35[k]);
}
}
}
free(t23);
free(t20);
}
