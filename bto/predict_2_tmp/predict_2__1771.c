#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t29;
double *t23;
int __s4135;
int __m4136;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t9 = msg->t9;
double *t29 = msg->t29;
double *t23 = msg->t23;
int __s4135 = msg->__s4135;
int __m4136 = msg->__m4136;

for (j=0; j<__m4136; j+=__s4135) {
// 4_2
int __m4135 = j + __s4135 > __m4136 ? __m4136 - j : __s4135;
double *t34 = t23 + j;
double *t40 = t29 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t46 = t34 + k*P_ncols;
double *t45 = t9 + k*P_ncols;
for (l=0; l<__m4135; l+=1) {
// 4_4
double *t58 = t40 + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t46[l] += (t45[p]*t58[p]);
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

int __s4137 = 12;

int __s4135 = 480;

int __s4134 = 12;

int nparts__s4136 = 12;
int __s4136;
if (nparts__s4136 > 1 && P_ncols > nparts__s4136) {
__s4136 = P_ncols/nparts__s4136;
// this will fail if P_ncols%nparts__s4136+__s4136 > nparts__s4136
// which primarily effects small sizes
if (P_ncols%nparts__s4136)
++__s4136;
}
else {
__s4136 = P_ncols;
nparts__s4136 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t24;
double *t11 = t24;
double *t14 = t24;
double *t15 = A;
double *t12 = A;
double *t9 = t21;
for (i=0; i<P_ncols; i+=__s4134) {
// 2_1
int __m4134 = i + __s4134 > P_ncols ? P_ncols - i : __s4134;
double *t20 = t21 + i;
double *t19 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t31 = t20 + j*P_ncols;
double *t30 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m4134; ++__zr__) t31[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t42 = t19 + k*P_ncols;
for (l=0; l<__m4134; l+=1) {
// 2_4
t31[l] += (t30[k]*t42[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4136);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4136);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4136,ii+=1) {
// 4_1
int __m4136 = i + __s4136 > P_ncols ? P_ncols - i : __s4136;
double *t23 = t24 + i;
double *t29 = t15 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t9 = t9;
predict_0[disp].t29 = t29;
predict_0[disp].t23 = t23;
predict_0[disp].__s4135 = __s4135;
predict_0[disp].__m4136 = __m4136;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4136; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s4137) {
// 6_1
int __m4137 = i + __s4137 > P_ncols ? P_ncols - i : __s4137;
double *t27 = P + i;
double *t25 = t16 + i;
double *t26 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t38 = t27 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
double *t37 = t26 + j*P_ncols;
for (k=0; k<__m4137; k+=1) {
// 6_3
t38[k] = (t36[k]+t37[k]);
}
}
}
free(t24);
free(t21);
}
