#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2944;
int P_ncols;
double *t18;
double *t17;
double *t8;
int __s2943;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2944 = msg->__m2944;
int P_ncols = msg->P_ncols;
double *t18 = msg->t18;
double *t17 = msg->t17;
double *t8 = msg->t8;
int __s2943 = msg->__s2943;

for (j=0; j<P_ncols; j+=__s2943) {
// 2_2
int __m2943 = j + __s2943 > P_ncols ? P_ncols - j : __s2943;
double *t27 = t8 + j;
double *t28 = t17 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t39 = t18 + k*P_ncols;
double *t38 = t27 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2944; ++__zr__) t39[__zr__] = 0.0;
for (l=0; l<__m2943; l+=1) {
// 2_4
double *t50 = t28 + l*P_ncols;
for (p=0; p<__m2944; p+=1) {
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

int __s2946 = 12;

int __s2945 = 12;

int __s2943 = 512;

int nparts__s2944 = 12;
int __s2944;
if (nparts__s2944 > 1 && P_ncols > nparts__s2944) {
__s2944 = P_ncols/nparts__s2944;
// this will fail if P_ncols%nparts__s2944+__s2944 > nparts__s2944
// which primarily effects small sizes
if (P_ncols%nparts__s2944)
++__s2944;
}
else {
__s2944 = P_ncols;
nparts__s2944 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t22;
double *t13 = t22;
double *t12 = t19;
double *t11 = t19;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2944);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2944);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2944,ii+=1) {
// 2_1
int __m2944 = i + __s2944 > P_ncols ? P_ncols - i : __s2944;
double *t18 = t19 + i;
double *t17 = P + i;
predict_0[disp].__m2944 = __m2944;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t18 = t18;
predict_0[disp].t17 = t17;
predict_0[disp].t8 = t8;
predict_0[disp].__s2943 = __s2943;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2944; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s2945) {
// 4_1
int __m2945 = i + __s2945 > P_ncols ? P_ncols - i : __s2945;
double *t21 = t22 + i*P_ncols;
double *t20 = t12 + i*P_ncols;
for (j=0; j<__m2945; j+=1) {
// 4_2
double *t32 = t21 + j*P_ncols;
double *t31 = t20 + j*P_ncols;
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
for (i=0; i<P_ncols; i+=__s2946) {
// 6_1
int __m2946 = i + __s2946 > P_ncols ? P_ncols - i : __s2946;
double *t25 = P + i*P_ncols;
double *t23 = t14 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<__m2946; j+=1) {
// 6_2
double *t36 = t25 + j*P_ncols;
double *t34 = t23 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t36[k] = (t34[k]+t35[k]);
}
}
}
free(t22);
free(t19);
}
