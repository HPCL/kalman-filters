#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t28;
double *t22;
int __s4398;
int __m4399;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t18;
double *t19;
int __s4396;
int __m4397;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t18 = msg->t18;
double *t19 = msg->t19;
int __s4396 = msg->__s4396;
int __m4397 = msg->__m4397;

for (j=0; j<__m4397; j+=__s4396) {
// 2_2
int __m4396 = j + __s4396 > __m4397 ? __m4397 - j : __s4396;
double *t30 = t19 + j;
double *t29 = t18 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t41 = t30 + k*P_ncols;
double *t40 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m4396; ++__zr__) t41[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t47 = t29 + l*P_ncols;
for (p=0; p<__m4396; p+=1) {
// 2_5
t41[p] += (t40[l]*t47[p]);
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
double *t9 = msg->t9;
double *t28 = msg->t28;
double *t22 = msg->t22;
int __s4398 = msg->__s4398;
int __m4399 = msg->__m4399;

for (j=0; j<__m4399; j+=__s4398) {
// 4_2
int __m4398 = j + __s4398 > __m4399 ? __m4399 - j : __s4398;
double *t33 = t22 + j;
double *t39 = t28 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t44 = t33 + k*P_ncols;
double *t43 = t9 + k*P_ncols;
for (l=0; l<__m4398; l+=1) {
// 4_4
double *t53 = t39 + l*P_ncols;
t44[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t44[l] += (t43[p]*t53[p]);
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

int __s4398 = 488;

int __s4396 = 488;

int nparts__s4399 = 10;
int __s4399;
if (nparts__s4399 > 1 && P_ncols > nparts__s4399) {
__s4399 = P_ncols/nparts__s4399;
// this will fail if P_ncols%nparts__s4399+__s4399 > nparts__s4399
// which primarily effects small sizes
if (P_ncols%nparts__s4399)
++__s4399;
}
else {
__s4399 = P_ncols;
nparts__s4399 = 1;
}

int nparts__s4397 = 6;
int __s4397;
if (nparts__s4397 > 1 && P_ncols > nparts__s4397) {
__s4397 = P_ncols/nparts__s4397;
// this will fail if P_ncols%nparts__s4397+__s4397 > nparts__s4397
// which primarily effects small sizes
if (P_ncols%nparts__s4397)
++__s4397;
}
else {
__s4397 = P_ncols;
nparts__s4397 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t23;
double *t16 = t23;
double *t17 = A;
double *t14 = A;
double *t9 = t20;
double *t11 = t20;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4397);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4397);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4397,ii+=1) {
// 2_1
int __m4397 = i + __s4397 > P_ncols ? P_ncols - i : __s4397;
double *t19 = t20 + i;
double *t18 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t18 = t18;
predict_0[disp].t19 = t19;
predict_0[disp].__s4396 = __s4396;
predict_0[disp].__m4397 = __m4397;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4397; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s4399);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s4399);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4399,ii+=1) {
// 4_1
int __m4399 = i + __s4399 > P_ncols ? P_ncols - i : __s4399;
double *t22 = t23 + i;
double *t28 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t28 = t28;
predict_1[disp].t22 = t22;
predict_1[disp].__s4398 = __s4398;
predict_1[disp].__m4399 = __m4399;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s4399; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t26 = P + i*P_ncols;
double *t24 = t13 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t26[j] = (t24[j]+t25[j]);
}
}
free(t23);
free(t20);
}
