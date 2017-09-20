#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m1314;
double *t23;
double *t22;
double *t24;
int __s1313;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m1314 = msg->__m1314;
double *t23 = msg->t23;
double *t22 = msg->t22;
double *t24 = msg->t24;
int __s1313 = msg->__s1313;

for (j=0; j<P_ncols; j+=__s1313) {
// 6_2
int __m1313 = j + __s1313 > P_ncols ? P_ncols - j : __s1313;
double *t34 = t24 + j;
double *t32 = t22 + j;
double *t33 = t23 + j;
for (k=0; k<__m1314; k+=1) {
// 6_3
double *t47 = t34 + k*P_ncols;
double *t45 = t32 + k*P_ncols;
double *t46 = t33 + k*P_ncols;
for (l=0; l<__m1313; l+=1) {
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

int __s1313 = 504;

int __s1312 = 2;

int nparts__s1314 = 12;
int __s1314;
if (nparts__s1314 > 1 && P_ncols > nparts__s1314) {
__s1314 = P_ncols/nparts__s1314;
// this will fail if P_ncols%nparts__s1314+__s1314 > nparts__s1314
// which primarily effects small sizes
if (P_ncols%nparts__s1314)
++__s1314;
}
else {
__s1314 = P_ncols;
nparts__s1314 = 1;
}

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t21;
double *t10 = t21;
double *t9 = t18;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s1312) {
// 2_1
int __m1312 = i + __s1312 > P_ncols ? P_ncols - i : __s1312;
double *t17 = t18 + i*P_ncols;
double *t16 = t8 + i*P_ncols;
for (j=0; j<__m1312; j+=1) {
// 2_2
double *t27 = t17 + j*P_ncols;
double *t26 = t16 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t27[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t38 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1314);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1314);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1314,ii+=1) {
// 6_1
int __m1314 = i + __s1314 > P_ncols ? P_ncols - i : __s1314;
double *t24 = P + i*P_ncols;
double *t22 = t13 + i*P_ncols;
double *t23 = Q + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m1314 = __m1314;
predict_0[disp].t23 = t23;
predict_0[disp].t22 = t22;
predict_0[disp].t24 = t24;
predict_0[disp].__s1313 = __s1313;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1314; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t21);
free(t18);
}
