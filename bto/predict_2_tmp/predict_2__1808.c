#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t28;
double *t22;
int __s4245;
int __m4246;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t18;
double *t19;
int __s4243;
int __m4244;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t18 = msg->t18;
double *t19 = msg->t19;
int __s4243 = msg->__s4243;
int __m4244 = msg->__m4244;

for (j=0; j<__m4244; j+=__s4243) {
// 2_2
int __m4243 = j + __s4243 > __m4244 ? __m4244 - j : __s4243;
double *t30 = t19 + j;
double *t29 = t18 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t41 = t30 + k*P_ncols;
double *t40 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m4243; ++__zr__) t41[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t47 = t29 + l*P_ncols;
for (p=0; p<__m4243; p+=1) {
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
int __s4245 = msg->__s4245;
int __m4246 = msg->__m4246;

for (j=0; j<__m4246; j+=__s4245) {
// 4_2
int __m4245 = j + __s4245 > __m4246 ? __m4246 - j : __s4245;
double *t33 = t22 + j;
double *t39 = t28 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t44 = t33 + k*P_ncols;
double *t43 = t9 + k*P_ncols;
for (l=0; l<__m4245; l+=1) {
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

int __s4245 = 488;

int __s4243 = 488;

int nparts__s4246 = 10;
int __s4246;
if (nparts__s4246 > 1 && P_ncols > nparts__s4246) {
__s4246 = P_ncols/nparts__s4246;
// this will fail if P_ncols%nparts__s4246+__s4246 > nparts__s4246
// which primarily effects small sizes
if (P_ncols%nparts__s4246)
++__s4246;
}
else {
__s4246 = P_ncols;
nparts__s4246 = 1;
}

int nparts__s4244 = 10;
int __s4244;
if (nparts__s4244 > 1 && P_ncols > nparts__s4244) {
__s4244 = P_ncols/nparts__s4244;
// this will fail if P_ncols%nparts__s4244+__s4244 > nparts__s4244
// which primarily effects small sizes
if (P_ncols%nparts__s4244)
++__s4244;
}
else {
__s4244 = P_ncols;
nparts__s4244 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t23;
double *t16 = t23;
double *t17 = A;
double *t14 = A;
double *t9 = t20;
double *t11 = t20;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4244);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4244);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4244,ii+=1) {
// 2_1
int __m4244 = i + __s4244 > P_ncols ? P_ncols - i : __s4244;
double *t19 = t20 + i;
double *t18 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t18 = t18;
predict_0[disp].t19 = t19;
predict_0[disp].__s4243 = __s4243;
predict_0[disp].__m4244 = __m4244;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4244; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s4246);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s4246);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4246,ii+=1) {
// 4_1
int __m4246 = i + __s4246 > P_ncols ? P_ncols - i : __s4246;
double *t22 = t23 + i;
double *t28 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t28 = t28;
predict_1[disp].t22 = t22;
predict_1[disp].__s4245 = __s4245;
predict_1[disp].__m4246 = __m4246;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s4246; ++disp) {
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
