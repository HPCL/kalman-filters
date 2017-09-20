#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m3105;
int P_ncols;
double *t17;
double *t8;
double *t18;
int __s3104;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m3105 = msg->__m3105;
int P_ncols = msg->P_ncols;
double *t17 = msg->t17;
double *t8 = msg->t8;
double *t18 = msg->t18;
int __s3104 = msg->__s3104;

for (j=0; j<P_ncols; j+=__s3104) {
// 2_2
int __m3104 = j + __s3104 > P_ncols ? P_ncols - j : __s3104;
double *t28 = t18 + j*P_ncols;
double *t27 = t8 + j*P_ncols;
for (k=0; k<__m3104; k+=1) {
// 2_3
double *t38 = t28 + k*P_ncols;
double *t37 = t27 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3105; ++__zr__) t38[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t49 = t17 + l*P_ncols;
for (p=0; p<__m3105; p+=1) {
// 2_5
t38[p] += (t37[l]*t49[p]);
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

int __s3106 = 12;

int __s3104 = 512;

int nparts__s3105 = 10;
int __s3105;
if (nparts__s3105 > 1 && P_ncols > nparts__s3105) {
__s3105 = P_ncols/nparts__s3105;
// this will fail if P_ncols%nparts__s3105+__s3105 > nparts__s3105
// which primarily effects small sizes
if (P_ncols%nparts__s3105)
++__s3105;
}
else {
__s3105 = P_ncols;
nparts__s3105 = 1;
}

double *t21 = malloc(sizeof(double)*__s3106*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t12 = t19;
double *t9 = t19;
double *t11 = t19;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3105);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3105);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3105,ii+=1) {
// 2_1
int __m3105 = i + __s3105 > P_ncols ? P_ncols - i : __s3105;
double *t18 = t19 + i;
double *t17 = P + i;
predict_0[disp].__m3105 = __m3105;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t17 = t17;
predict_0[disp].t8 = t8;
predict_0[disp].t18 = t18;
predict_0[disp].__s3104 = __s3104;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3105; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s3106) {
// 4_1
int __m3106 = i + __s3106 > P_ncols ? P_ncols - i : __s3106;
double *t25 = P + i*P_ncols;
double *t20 = t12 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<__m3106; j+=1) {
// 4_2
double *t31 = t21 + j*P_ncols;
double *t30 = t20 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t47 = A + k*P_ncols;
t31[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t31[k] += (t30[l]*t47[l]);
}
}
}
for (j=0; j<__m3106; j+=1) {
// 6_2
double *t35 = t25 + j*P_ncols;
double *t33 = t21 + j*P_ncols;
double *t34 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t35[k] = (t33[k]+t34[k]);
}
}
}
free(t21);
free(t19);
}
