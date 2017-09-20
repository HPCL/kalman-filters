#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t23;
int __s1361;
int __m1360;
double *P;
double *t19;
int __s1359;
int __s1360;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t23 = msg->t23;
int __s1361 = msg->__s1361;
int __m1360 = msg->__m1360;
double *P = msg->P;
double *t19 = msg->t19;
int __s1359 = msg->__s1359;
int __s1360 = msg->__s1360;

double *t20 = malloc(sizeof(double)*__s1360*P_ncols);
for (j=0; j<__m1360; j+=__s1359) {
// 2_2
int __m1359 = j + __s1359 > __m1360 ? __m1360 - j : __s1359;
double *t30 = t20 + j*P_ncols;
double *t29 = t19 + j*P_ncols;
for (k=0; k<__m1359; k+=1) {
// 2_3
double *t40 = t30 + k*P_ncols;
double *t39 = t29 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t40[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t50 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t40[p] += (t39[l]*t50[p]);
}
}
}
}
for (j=0; j<__m1360; j+=__s1361) {
// 4_2
int __m1361 = j + __s1361 > __m1360 ? __m1360 - j : __s1361;
double *t33 = t23 + j*P_ncols;
double *t32 = t20 + j*P_ncols;
for (k=0; k<__m1361; k+=1) {
// 4_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t56 = A + l*P_ncols;
t43[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t43[l] += (t42[p]*t56[p]);
}
}
}
}
free(t20);
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k;

int __s1363 = 2;

int __s1361 = 512;

int __s1359 = 512;

int nparts__s1360 = 10;
int __s1360;
if (nparts__s1360 > 1 && P_ncols > nparts__s1360) {
__s1360 = P_ncols/nparts__s1360;
// this will fail if P_ncols%nparts__s1360+__s1360 > nparts__s1360
// which primarily effects small sizes
if (P_ncols%nparts__s1360)
++__s1360;
}
else {
__s1360 = P_ncols;
nparts__s1360 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t24;
double *t13 = t24;
double *t15 = t24;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1360);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1360);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1360,ii+=1) {
// 2_1
int __m1360 = i + __s1360 > P_ncols ? P_ncols - i : __s1360;
double *t23 = t24 + i*P_ncols;
double *t19 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t23 = t23;
predict_0[disp].__s1361 = __s1361;
predict_0[disp].__m1360 = __m1360;
predict_0[disp].P = P;
predict_0[disp].t19 = t19;
predict_0[disp].__s1359 = __s1359;
predict_0[disp].__s1360 = __s1360;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1360; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s1363) {
// 6_1
int __m1363 = i + __s1363 > P_ncols ? P_ncols - i : __s1363;
double *t27 = P + i;
double *t25 = t16 + i;
double *t26 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t37 = t27 + j*P_ncols;
double *t35 = t25 + j*P_ncols;
double *t36 = t26 + j*P_ncols;
for (k=0; k<__m1363; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t24);
}
