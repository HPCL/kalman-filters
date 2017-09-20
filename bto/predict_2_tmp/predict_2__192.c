#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m523;
int P_ncols;
double *t23;
double *t22;
double *t24;
int __s522;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m523 = msg->__m523;
int P_ncols = msg->P_ncols;
double *t23 = msg->t23;
double *t22 = msg->t22;
double *t24 = msg->t24;
int __s522 = msg->__s522;

for (j=0; j<P_ncols; j+=__s522) {
// 6_2
int __m522 = j + __s522 > P_ncols ? P_ncols - j : __s522;
double *t34 = t24 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
for (k=0; k<__m522; k+=1) {
// 6_3
double *t47 = t34 + k*P_ncols;
double *t45 = t32 + k*P_ncols;
double *t46 = t33 + k*P_ncols;
for (l=0; l<__m523; l+=1) {
// 6_4
t47[l] = (t45[l]+t46[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s522 = 512;

int __s521 = 2;

int nparts__s523 = 12;
int __s523;
if (nparts__s523 > 1 && P_ncols > nparts__s523) {
__s523 = P_ncols/nparts__s523;
// this will fail if P_ncols%nparts__s523+__s523 > nparts__s523
// which primarily effects small sizes
if (P_ncols%nparts__s523)
++__s523;
}
else {
__s523 = P_ncols;
nparts__s523 = 1;
}

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t21;
double *t10 = t21;
double *t9 = t18;
for (i=0; i<P_ncols; i+=__s521) {
// 2_1
int __m521 = i + __s521 > P_ncols ? P_ncols - i : __s521;
double *t17 = t18 + i;
double *t16 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t27 = t17 + j*P_ncols;
double *t26 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m521; ++__zr__) t27[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t38 = t16 + k*P_ncols;
for (l=0; l<__m521; l+=1) {
// 2_4
t27[l] += (t26[k]*t38[l]);
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s523);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s523);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s523,ii+=1) {
// 6_1
int __m523 = i + __s523 > P_ncols ? P_ncols - i : __s523;
double *t24 = P + i;
double *t22 = t13 + i;
double *t23 = Q + i;
predict_0[disp].__m523 = __m523;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t23 = t23;
predict_0[disp].t22 = t22;
predict_0[disp].t24 = t24;
predict_0[disp].__s522 = __s522;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s523; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t21);
free(t18);
}
