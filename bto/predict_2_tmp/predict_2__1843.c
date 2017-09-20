#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t31;
double *t25;
int __s4331;
int __m4332;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t21;
double *t22;
int __s4329;
int __m4330;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t21 = msg->t21;
double *t22 = msg->t22;
int __s4329 = msg->__s4329;
int __m4330 = msg->__m4330;

for (j=0; j<__m4330; j+=__s4329) {
// 2_2
int __m4329 = j + __s4329 > __m4330 ? __m4330 - j : __s4329;
double *t33 = t22 + j;
double *t32 = t21 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t44 = t33 + k*P_ncols;
double *t43 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m4329; ++__zr__) t44[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t54 = t32 + l*P_ncols;
for (p=0; p<__m4329; p+=1) {
// 2_5
t44[p] += (t43[l]*t54[p]);
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
double *t31 = msg->t31;
double *t25 = msg->t25;
int __s4331 = msg->__s4331;
int __m4332 = msg->__m4332;

for (j=0; j<__m4332; j+=__s4331) {
// 4_2
int __m4331 = j + __s4331 > __m4332 ? __m4332 - j : __s4331;
double *t36 = t25 + j;
double *t42 = t31 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t47 = t36 + k*P_ncols;
double *t46 = t9 + k*P_ncols;
for (l=0; l<__m4331; l+=1) {
// 4_4
double *t60 = t42 + l*P_ncols;
t47[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t47[l] += (t46[p]*t60[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k;

int __s4333 = 10;

int __s4331 = 488;

int __s4329 = 488;

int nparts__s4332 = 10;
int __s4332;
if (nparts__s4332 > 1 && P_ncols > nparts__s4332) {
__s4332 = P_ncols/nparts__s4332;
// this will fail if P_ncols%nparts__s4332+__s4332 > nparts__s4332
// which primarily effects small sizes
if (P_ncols%nparts__s4332)
++__s4332;
}
else {
__s4332 = P_ncols;
nparts__s4332 = 1;
}

int nparts__s4330 = 8;
int __s4330;
if (nparts__s4330 > 1 && P_ncols > nparts__s4330) {
__s4330 = P_ncols/nparts__s4330;
// this will fail if P_ncols%nparts__s4330+__s4330 > nparts__s4330
// which primarily effects small sizes
if (P_ncols%nparts__s4330)
++__s4330;
}
else {
__s4330 = P_ncols;
nparts__s4330 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t26;
double *t13 = t26;
double *t16 = t26;
double *t17 = A;
double *t14 = A;
double *t9 = t23;
double *t11 = t23;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4330);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4330);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4330,ii+=1) {
// 2_1
int __m4330 = i + __s4330 > P_ncols ? P_ncols - i : __s4330;
double *t22 = t23 + i;
double *t21 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t21 = t21;
predict_0[disp].t22 = t22;
predict_0[disp].__s4329 = __s4329;
predict_0[disp].__m4330 = __m4330;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4330; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s4332);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s4332);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4332,ii+=1) {
// 4_1
int __m4332 = i + __s4332 > P_ncols ? P_ncols - i : __s4332;
double *t25 = t26 + i;
double *t31 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t31 = t31;
predict_1[disp].t25 = t25;
predict_1[disp].__s4331 = __s4331;
predict_1[disp].__m4332 = __m4332;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s4332; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s4333) {
// 6_1
int __m4333 = i + __s4333 > P_ncols ? P_ncols - i : __s4333;
double *t29 = P + i;
double *t27 = t18 + i;
double *t28 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m4333; k+=1) {
// 6_3
t40[k] = (t38[k]+t39[k]);
}
}
}
free(t26);
free(t23);
}
