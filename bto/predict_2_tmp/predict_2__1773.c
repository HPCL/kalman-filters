#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t26;
double *t20;
int __s4139;
int __m4140;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t9 = msg->t9;
double *t26 = msg->t26;
double *t20 = msg->t20;
int __s4139 = msg->__s4139;
int __m4140 = msg->__m4140;

for (j=0; j<__m4140; j+=__s4139) {
// 4_2
int __m4139 = j + __s4139 > __m4140 ? __m4140 - j : __s4139;
double *t31 = t20 + j;
double *t37 = t26 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t43 = t31 + k*P_ncols;
double *t42 = t9 + k*P_ncols;
for (l=0; l<__m4139; l+=1) {
// 4_4
double *t51 = t37 + l*P_ncols;
t43[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t43[l] += (t42[p]*t51[p]);
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

int __s4139 = 488;

int __s4138 = 10;

int nparts__s4140 = 10;
int __s4140;
if (nparts__s4140 > 1 && P_ncols > nparts__s4140) {
__s4140 = P_ncols/nparts__s4140;
// this will fail if P_ncols%nparts__s4140+__s4140 > nparts__s4140
// which primarily effects small sizes
if (P_ncols%nparts__s4140)
++__s4140;
}
else {
__s4140 = P_ncols;
nparts__s4140 = 1;
}

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t21;
double *t14 = t21;
double *t15 = A;
double *t12 = A;
double *t9 = t18;
for (i=0; i<P_ncols; i+=__s4138) {
// 2_1
int __m4138 = i + __s4138 > P_ncols ? P_ncols - i : __s4138;
double *t17 = t18 + i;
double *t16 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t28 = t17 + j*P_ncols;
double *t27 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m4138; ++__zr__) t28[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t39 = t16 + k*P_ncols;
for (l=0; l<__m4138; l+=1) {
// 2_4
t28[l] += (t27[k]*t39[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4140);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4140);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4140,ii+=1) {
// 4_1
int __m4140 = i + __s4140 > P_ncols ? P_ncols - i : __s4140;
double *t20 = t21 + i;
double *t26 = t15 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t9 = t9;
predict_0[disp].t26 = t26;
predict_0[disp].t20 = t20;
predict_0[disp].__s4139 = __s4139;
predict_0[disp].__m4140 = __m4140;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4140; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t24 = P + i*P_ncols;
double *t22 = t11 + i*P_ncols;
double *t23 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t24[j] = (t22[j]+t23[j]);
}
}
free(t21);
free(t18);
}
