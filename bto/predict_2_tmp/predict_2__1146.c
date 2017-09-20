#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2957;
int P_ncols;
double *t26;
double *t25;
double *t27;
int __s2956;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2957 = msg->__m2957;
int P_ncols = msg->P_ncols;
double *t26 = msg->t26;
double *t25 = msg->t25;
double *t27 = msg->t27;
int __s2956 = msg->__s2956;

for (j=0; j<P_ncols; j+=__s2956) {
// 6_2
int __m2956 = j + __s2956 > P_ncols ? P_ncols - j : __s2956;
double *t37 = t27 + j*P_ncols;
double *t35 = t25 + j*P_ncols;
double *t36 = t26 + j*P_ncols;
for (k=0; k<__m2956; k+=1) {
// 6_3
double *t48 = t37 + k*P_ncols;
double *t46 = t35 + k*P_ncols;
double *t47 = t36 + k*P_ncols;
for (l=0; l<__m2957; l+=1) {
// 6_4
t48[l] = (t46[l]+t47[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s2956 = 504;

int __s2955 = 12;

int __s2954 = 12;

int nparts__s2957 = 12;
int __s2957;
if (nparts__s2957 > 1 && P_ncols > nparts__s2957) {
__s2957 = P_ncols/nparts__s2957;
// this will fail if P_ncols%nparts__s2957+__s2957 > nparts__s2957
// which primarily effects small sizes
if (P_ncols%nparts__s2957)
++__s2957;
}
else {
__s2957 = P_ncols;
nparts__s2957 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t24;
double *t12 = t24;
double *t11 = t24;
double *t10 = t21;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s2954) {
// 2_1
int __m2954 = i + __s2954 > P_ncols ? P_ncols - i : __s2954;
double *t18 = t8 + i;
double *t19 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t30 = t21 + j*P_ncols;
double *t29 = t18 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t30[__zr__] = 0.0;
for (k=0; k<__m2954; k+=1) {
// 2_3
double *t40 = t19 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t30[l] += (t29[k]*t40[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s2955) {
// 4_1
int __m2955 = i + __s2955 > P_ncols ? P_ncols - i : __s2955;
double *t23 = t24 + i*P_ncols;
double *t22 = t10 + i*P_ncols;
for (j=0; j<__m2955; j+=1) {
// 4_2
double *t33 = t23 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t50 = A + k*P_ncols;
t33[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t33[k] += (t32[l]*t50[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2957);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2957);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2957,ii+=1) {
// 6_1
int __m2957 = i + __s2957 > P_ncols ? P_ncols - i : __s2957;
double *t27 = P + i;
double *t25 = t15 + i;
double *t26 = Q + i;
predict_0[disp].__m2957 = __m2957;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t26 = t26;
predict_0[disp].t25 = t25;
predict_0[disp].t27 = t27;
predict_0[disp].__s2956 = __s2956;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2957; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t24);
free(t21);
}
