#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2523;
int P_ncols;
double *t13;
double *t12;
double *t8;
int __s2522;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2523 = msg->__m2523;
int P_ncols = msg->P_ncols;
double *t13 = msg->t13;
double *t12 = msg->t12;
double *t8 = msg->t8;
int __s2522 = msg->__s2522;

for (j=0; j<P_ncols; j+=__s2522) {
// 2_2
int __m2522 = j + __s2522 > P_ncols ? P_ncols - j : __s2522;
double *t22 = t8 + j;
double *t23 = t12 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t35 = t13 + k*P_ncols;
double *t34 = t22 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2523; ++__zr__) t35[__zr__] = 0.0;
for (l=0; l<__m2522; l+=1) {
// 2_4
double *t42 = t23 + l*P_ncols;
for (p=0; p<__m2523; p+=1) {
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

int __s2522 = 512;

int nparts__s2523 = 12;
int __s2523;
if (nparts__s2523 > 1 && P_ncols > nparts__s2523) {
__s2523 = P_ncols/nparts__s2523;
// this will fail if P_ncols%nparts__s2523+__s2523 > nparts__s2523
// which primarily effects small sizes
if (P_ncols%nparts__s2523)
++__s2523;
}
else {
__s2523 = P_ncols;
nparts__s2523 = 1;
}

double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t14;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2523);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2523);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2523,ii+=1) {
// 2_1
int __m2523 = i + __s2523 > P_ncols ? P_ncols - i : __s2523;
double *t13 = t14 + i;
double *t12 = P + i;
predict_0[disp].__m2523 = __m2523;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t13 = t13;
predict_0[disp].t12 = t12;
predict_0[disp].t8 = t8;
predict_0[disp].__s2522 = __s2522;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2523; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t16 = t17 + i*P_ncols;
double *t15 = t11 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t33 = A + j*P_ncols;
t16[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t16[j] += (t15[k]*t33[k]);
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t20 = P + i*P_ncols;
double *t18 = t17 + i*P_ncols;
double *t19 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t20[j] = (t18[j]+t19[j]);
}
}
free(t17);
free(t14);
}
