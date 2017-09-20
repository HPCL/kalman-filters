#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m2508;
double *t23;
double *t29;
double *t12;
int __s2507;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t19;
int __m2506;
double *t18;
double *t20;
int __s2505;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t19 = msg->t19;
int __m2506 = msg->__m2506;
double *t18 = msg->t18;
double *t20 = msg->t20;
int __s2505 = msg->__s2505;

for (j=0; j<P_ncols; j+=__s2505) {
// 2_2
int __m2505 = j + __s2505 > P_ncols ? P_ncols - j : __s2505;
double *t31 = t20 + j*P_ncols;
double *t30 = t18 + j*P_ncols;
for (k=0; k<__m2505; k+=1) {
// 2_3
double *t43 = t31 + k*P_ncols;
double *t42 = t30 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<__m2506; l+=1) {
// 2_4
double *t49 = t19 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t43[p] += (t42[l]*t49[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m2508 = msg->__m2508;
double *t23 = msg->t23;
double *t29 = msg->t29;
double *t12 = msg->t12;
int __s2507 = msg->__s2507;

for (j=0; j<P_ncols; j+=__s2507) {
// 4_2
int __m2507 = j + __s2507 > P_ncols ? P_ncols - j : __s2507;
double *t33 = t12 + j;
double *t41 = t29 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t46 = t23 + k*P_ncols;
double *t45 = t33 + k*P_ncols;
for (l=0; l<__m2508; l+=1) {
// 4_4
double *t55 = t41 + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<__m2507; p+=1) {
// 4_5
t46[l] += (t45[p]*t55[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j;

int __s2507 = 504;

int __s2505 = 512;

int nparts__s2506 = 10;
int __s2506;
if (nparts__s2506 > 1 && P_ncols > nparts__s2506) {
__s2506 = P_ncols/nparts__s2506;
// this will fail if P_ncols%nparts__s2506+__s2506 > nparts__s2506
// which primarily effects small sizes
if (P_ncols%nparts__s2506)
++__s2506;
}
else {
__s2506 = P_ncols;
nparts__s2506 = 1;
}

int nparts__s2508 = 10;
int __s2508;
if (nparts__s2508 > 1 && P_ncols > nparts__s2508) {
__s2508 = P_ncols/nparts__s2508;
// this will fail if P_ncols%nparts__s2508+__s2508 > nparts__s2508
// which primarily effects small sizes
if (P_ncols%nparts__s2508)
++__s2508;
}
else {
__s2508 = P_ncols;
nparts__s2508 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*nparts__s2506*P_ncols*P_ncols);
double *t16 = t24;
double *t12 = t21;
double *t9 = t21;
double *t63 = t21;
double *t10 = A;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2506);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2506);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2506,ii+=1) {
// 2_1
int __m2506 = i + __s2506 > P_ncols ? P_ncols - i : __s2506;
double *t20 = t21 + ii*P_ncols*P_ncols;
double *t18 = t10 + i;
double *t19 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t19 = t19;
predict_0[disp].__m2506 = __m2506;
predict_0[disp].t18 = t18;
predict_0[disp].t20 = t20;
predict_0[disp].__s2505 = __s2505;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2506; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2506,ii+=1) {
// 2_1
int __m2506 = i + __s2506 > P_ncols ? P_ncols - i : __s2506;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2505) {
int __m2505 = __j + __s2505 > P_ncols ? P_ncols - __j : __s2505;
for (__k = 0; __k < __m2505; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t63[__j*P_ncols+__k*P_ncols+__l] = t21[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2505) {
int __m2505 = __j + __s2505 > P_ncols ? P_ncols - __j : __s2505;
for (__k = 0; __k < __m2505; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t63[__j*P_ncols+__k*P_ncols+__l] += t21[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2508);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2508);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2508,ii+=1) {
// 4_1
int __m2508 = i + __s2508 > P_ncols ? P_ncols - i : __s2508;
double *t23 = t24 + i;
double *t29 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m2508 = __m2508;
predict_1[disp].t23 = t23;
predict_1[disp].t29 = t29;
predict_1[disp].t12 = t12;
predict_1[disp].__s2507 = __s2507;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2508; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t27 = P + i*P_ncols;
double *t25 = t16 + i*P_ncols;
double *t26 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t27[j] = (t25[j]+t26[j]);
}
}
free(t24);
free(t21);
}
