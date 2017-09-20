#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m1173;
double *t25;
double *t24;
double *t26;
int __s1172;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m1173 = msg->__m1173;
double *t25 = msg->t25;
double *t24 = msg->t24;
double *t26 = msg->t26;
int __s1172 = msg->__s1172;

for (j=0; j<P_ncols; j+=__s1172) {
// 6_2
int __m1172 = j + __s1172 > P_ncols ? P_ncols - j : __s1172;
double *t38 = t26 + j;
double *t36 = t24 + j;
double *t37 = t25 + j;
for (k=0; k<__m1173; k+=1) {
// 6_3
double *t48 = t38 + k*P_ncols;
double *t46 = t36 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
for (l=0; l<__m1172; l+=1) {
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

int __s1172 = 512;

int __s1171 = 2;

int nparts__s1173 = 12;
int __s1173;
if (nparts__s1173 > 1 && P_ncols > nparts__s1173) {
__s1173 = P_ncols/nparts__s1173;
// this will fail if P_ncols%nparts__s1173+__s1173 > nparts__s1173
// which primarily effects small sizes
if (P_ncols%nparts__s1173)
++__s1173;
}
else {
__s1173 = P_ncols;
nparts__s1173 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t23;
double *t11 = t23;
double *t10 = A;
double *t8 = t19;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t18 = t19 + i*P_ncols;
double *t17 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t18[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t30 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t18[k] += (t17[j]*t30[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s1171) {
// 4_1
int __m1171 = i + __s1171 > P_ncols ? P_ncols - i : __s1171;
double *t20 = t8 + i;
double *t28 = t10 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t34 = t23 + j*P_ncols;
double *t33 = t20 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t50 = t28 + k*P_ncols;
t34[k] = 0.0;
for (l=0; l<__m1171; l+=1) {
// 4_4
t34[k] += (t33[l]*t50[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1173);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1173);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1173,ii+=1) {
// 6_1
int __m1173 = i + __s1173 > P_ncols ? P_ncols - i : __s1173;
double *t26 = P + i*P_ncols;
double *t24 = t14 + i*P_ncols;
double *t25 = Q + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m1173 = __m1173;
predict_0[disp].t25 = t25;
predict_0[disp].t24 = t24;
predict_0[disp].t26 = t26;
predict_0[disp].__s1172 = __s1172;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1173; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t23);
free(t19);
}
