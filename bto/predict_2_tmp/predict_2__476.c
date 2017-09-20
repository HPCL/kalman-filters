#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t19;
int __m1252;
double *t18;
double *t20;
int __s1251;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t19 = msg->t19;
int __m1252 = msg->__m1252;
double *t18 = msg->t18;
double *t20 = msg->t20;
int __s1251 = msg->__s1251;

for (j=0; j<P_ncols; j+=__s1251) {
// 2_2
int __m1251 = j + __s1251 > P_ncols ? P_ncols - j : __s1251;
double *t31 = t20 + j*P_ncols;
double *t30 = t18 + j*P_ncols;
for (k=0; k<__m1251; k+=1) {
// 2_3
double *t41 = t31 + k*P_ncols;
double *t40 = t30 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t41[__zr__] = 0.0;
for (l=0; l<__m1252; l+=1) {
// 2_4
double *t52 = t19 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t41[p] += (t40[l]*t52[p]);
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

int __s1253 = 12;

int __s1251 = 512;

int nparts__s1252 = 12;
int __s1252;
if (nparts__s1252 > 1 && P_ncols > nparts__s1252) {
__s1252 = P_ncols/nparts__s1252;
// this will fail if P_ncols%nparts__s1252+__s1252 > nparts__s1252
// which primarily effects small sizes
if (P_ncols%nparts__s1252)
++__s1252;
}
else {
__s1252 = P_ncols;
nparts__s1252 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*__s1253);
double *t21 = malloc(sizeof(double)*nparts__s1252*P_ncols*P_ncols);
double *t9 = t21;
double *t62 = t21;
double *t10 = A;
double *t8 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1252);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1252);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1252,ii+=1) {
// 2_1
int __m1252 = i + __s1252 > P_ncols ? P_ncols - i : __s1252;
double *t20 = t21 + ii*P_ncols*P_ncols;
double *t18 = t10 + i;
double *t19 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t19 = t19;
predict_0[disp].__m1252 = __m1252;
predict_0[disp].t18 = t18;
predict_0[disp].t20 = t20;
predict_0[disp].__s1251 = __s1251;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1252; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1252,ii+=1) {
// 2_1
int __m1252 = i + __s1252 > P_ncols ? P_ncols - i : __s1252;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1251) {
int __m1251 = __j + __s1251 > P_ncols ? P_ncols - __j : __s1251;
for (__k = 0; __k < __m1251; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t62[__j*P_ncols+__k*P_ncols+__l] = t21[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1251) {
int __m1251 = __j + __s1251 > P_ncols ? P_ncols - __j : __s1251;
for (__k = 0; __k < __m1251; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t62[__j*P_ncols+__k*P_ncols+__l] += t21[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s1253) {
// 4_1
int __m1253 = i + __s1253 > P_ncols ? P_ncols - i : __s1253;
double *t27 = P + i;
double *t29 = t14 + i*P_ncols;
double *t26 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t34 = t23 + j*__m1253;
double *t33 = t9 + j*P_ncols;
for (k=0; k<__m1253; k+=1) {
// 4_3
double *t50 = t29 + k*P_ncols;
t34[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t34[k] += (t33[l]*t50[l]);
}
}
}
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t38 = t27 + j*P_ncols;
double *t36 = t23 + j*__m1253;
double *t37 = t26 + j*P_ncols;
for (k=0; k<__m1253; k+=1) {
// 6_3
t38[k] = (t36[k]+t37[k]);
}
}
}
free(t23);
free(t21);
}
