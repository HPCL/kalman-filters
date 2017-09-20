#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *P;
double *t18;
double *t19;
int __s528;
int __m529;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t18 = msg->t18;
double *t19 = msg->t19;
int __s528 = msg->__s528;
int __m529 = msg->__m529;

for (j=0; j<__m529; j+=__s528) {
// 2_2
int __m528 = j + __s528 > __m529 ? __m529 - j : __s528;
double *t30 = t19 + j*P_ncols;
double *t29 = t18 + j*P_ncols;
for (k=0; k<__m528; k+=1) {
// 2_3
double *t40 = t30 + k*P_ncols;
double *t39 = t29 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t40[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t51 = P + l*P_ncols;
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

int __s531 = 2;

int __s530 = 2;

int __s528 = 512;

int nparts__s529 = 8;
int __s529;
if (nparts__s529 > 1 && P_ncols > nparts__s529) {
__s529 = P_ncols/nparts__s529;
// this will fail if P_ncols%nparts__s529+__s529 > nparts__s529
// which primarily effects small sizes
if (P_ncols%nparts__s529)
++__s529;
}
else {
__s529 = P_ncols;
nparts__s529 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t23;
double *t13 = t23;
double *t9 = t20;
double *t11 = t20;
double *t10 = A;
double *t8 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s529);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s529);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s529,ii+=1) {
// 2_1
int __m529 = i + __s529 > P_ncols ? P_ncols - i : __s529;
double *t19 = t20 + i*P_ncols;
double *t18 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t18 = t18;
predict_0[disp].t19 = t19;
predict_0[disp].__s528 = __s528;
predict_0[disp].__m529 = __m529;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s529; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s530) {
// 4_1
int __m530 = i + __s530 > P_ncols ? P_ncols - i : __s530;
double *t22 = t23 + i;
double *t28 = t14 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t33 = t22 + j*P_ncols;
double *t32 = t9 + j*P_ncols;
for (k=0; k<__m530; k+=1) {
// 4_3
double *t49 = t28 + k*P_ncols;
t33[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t33[k] += (t32[l]*t49[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s531) {
// 6_1
int __m531 = i + __s531 > P_ncols ? P_ncols - i : __s531;
double *t26 = P + i;
double *t24 = t15 + i;
double *t25 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t37 = t26 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
for (k=0; k<__m531; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t23);
free(t20);
}
