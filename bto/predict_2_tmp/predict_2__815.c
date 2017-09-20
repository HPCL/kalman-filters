#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t28;
int __m1947;
double *t10;
double *t22;
int __s1946;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
int __m1947 = msg->__m1947;
double *t10 = msg->t10;
double *t22 = msg->t22;
int __s1946 = msg->__s1946;

for (j=0; j<P_ncols; j+=__s1946) {
// 4_2
int __m1946 = j + __s1946 > P_ncols ? P_ncols - j : __s1946;
double *t33 = t22 + j*P_ncols;
double *t32 = t10 + j*P_ncols;
for (k=0; k<__m1946; k+=1) {
// 4_3
double *t44 = t33 + k*P_ncols;
double *t43 = t32 + k*P_ncols;
for (l=0; l<__m1947; l+=1) {
// 4_4
double *t56 = t28 + l*P_ncols;
t44[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t44[l] += (t43[p]*t56[p]);
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

int __s1948 = 12;

int __s1946 = 504;

int __s1945 = 2;

int nparts__s1947 = 10;
int __s1947;
if (nparts__s1947 > 1 && P_ncols > nparts__s1947) {
__s1947 = P_ncols/nparts__s1947;
// this will fail if P_ncols%nparts__s1947+__s1947 > nparts__s1947
// which primarily effects small sizes
if (P_ncols%nparts__s1947)
++__s1947;
}
else {
__s1947 = P_ncols;
nparts__s1947 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t23;
double *t11 = t23;
double *t13 = t23;
double *t14 = A;
double *t10 = t20;
double *t9 = t20;
for (i=0; i<P_ncols; i+=__s1945) {
// 2_1
int __m1945 = i + __s1945 > P_ncols ? P_ncols - i : __s1945;
double *t19 = t20 + i;
double *t18 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t30 = t19 + j*P_ncols;
double *t29 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m1945; ++__zr__) t30[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t40 = t18 + k*P_ncols;
for (l=0; l<__m1945; l+=1) {
// 2_4
t30[l] += (t29[k]*t40[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1947);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1947);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1947,ii+=1) {
// 4_1
int __m1947 = i + __s1947 > P_ncols ? P_ncols - i : __s1947;
double *t22 = t23 + i;
double *t28 = t14 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t28 = t28;
predict_0[disp].__m1947 = __m1947;
predict_0[disp].t10 = t10;
predict_0[disp].t22 = t22;
predict_0[disp].__s1946 = __s1946;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1947; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s1948) {
// 6_1
int __m1948 = i + __s1948 > P_ncols ? P_ncols - i : __s1948;
double *t26 = P + i*P_ncols;
double *t24 = t15 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<__m1948; j+=1) {
// 6_2
double *t37 = t26 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t23);
free(t20);
}
