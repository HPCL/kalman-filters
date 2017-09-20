#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *P;
double *t16;
double *t20;
int __s1678;
int __m1679;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *P = msg->P;
double *t16 = msg->t16;
double *t20 = msg->t20;
int __s1678 = msg->__s1678;
int __m1679 = msg->__m1679;

for (j=0; j<__m1679; j+=__s1678) {
// 2_2
int __m1678 = j + __s1678 > __m1679 ? __m1679 - j : __s1678;
double *t27 = malloc(sizeof(double)*__s1678*P_ncols);
double *t30 = t20 + j*P_ncols;
double *t26 = t16 + j*P_ncols;
for (k=0; k<__m1678; k+=1) {
// 2_3
double *t37 = t27 + k*P_ncols;
double *t36 = t26 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t37[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t43 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t37[p] += (t36[l]*t43[p]);
}
}
}
for (k=0; k<__m1678; k+=1) {
// 4_3
double *t40 = t30 + k*P_ncols;
double *t39 = t27 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t49 = A + l*P_ncols;
t40[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t40[l] += (t39[p]*t49[p]);
}
}
}
free(t27);
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j;

int __s1678 = 512;

int nparts__s1679 = 12;
int __s1679;
if (nparts__s1679 > 1 && P_ncols > nparts__s1679) {
__s1679 = P_ncols/nparts__s1679;
// this will fail if P_ncols%nparts__s1679+__s1679 > nparts__s1679
// which primarily effects small sizes
if (P_ncols%nparts__s1679)
++__s1679;
}
else {
__s1679 = P_ncols;
nparts__s1679 = 1;
}

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t21;
double *t15 = t21;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1679);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1679);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1679,ii+=1) {
// 2_1
int __m1679 = i + __s1679 > P_ncols ? P_ncols - i : __s1679;
double *t20 = t21 + i*P_ncols;
double *t16 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].P = P;
predict_0[disp].t16 = t16;
predict_0[disp].t20 = t20;
predict_0[disp].__s1678 = __s1678;
predict_0[disp].__m1679 = __m1679;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1679; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t24 = P + i*P_ncols;
double *t22 = t13 + i*P_ncols;
double *t23 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t24[j] = (t22[j]+t23[j]);
}
}
free(t21);
}
