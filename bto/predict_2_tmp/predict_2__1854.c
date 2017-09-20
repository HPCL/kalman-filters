#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t28;
double *t27;
double *t29;
int __s4354;
int __m4355;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t21;
double *t22;
int __s4351;
int __m4352;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t21 = msg->t21;
double *t22 = msg->t22;
int __s4351 = msg->__s4351;
int __m4352 = msg->__m4352;

for (j=0; j<__m4352; j+=__s4351) {
// 2_2
int __m4351 = j + __s4351 > __m4352 ? __m4352 - j : __s4351;
double *t33 = t22 + j;
double *t32 = t21 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t43 = t33 + k*P_ncols;
double *t42 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m4351; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t54 = t32 + l*P_ncols;
for (p=0; p<__m4351; p+=1) {
// 2_5
t43[p] += (t42[l]*t54[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s4354 = msg->__s4354;
int __m4355 = msg->__m4355;

for (j=0; j<__m4355; j+=__s4354) {
// 6_2
int __m4354 = j + __s4354 > __m4355 ? __m4355 - j : __s4354;
double *t40 = t29 + j;
double *t38 = t27 + j;
double *t39 = t28 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t50 = t40 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<__m4354; l+=1) {
// 6_4
t50[l] = (t48[l]+t49[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s4354 = 504;

int __s4353 = 10;

int __s4351 = 488;

int nparts__s4355 = 10;
int __s4355;
if (nparts__s4355 > 1 && P_ncols > nparts__s4355) {
__s4355 = P_ncols/nparts__s4355;
// this will fail if P_ncols%nparts__s4355+__s4355 > nparts__s4355
// which primarily effects small sizes
if (P_ncols%nparts__s4355)
++__s4355;
}
else {
__s4355 = P_ncols;
nparts__s4355 = 1;
}

int nparts__s4352 = 8;
int __s4352;
if (nparts__s4352 > 1 && P_ncols > nparts__s4352) {
__s4352 = P_ncols/nparts__s4352;
// this will fail if P_ncols%nparts__s4352+__s4352 > nparts__s4352
// which primarily effects small sizes
if (P_ncols%nparts__s4352)
++__s4352;
}
else {
__s4352 = P_ncols;
nparts__s4352 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t26;
double *t15 = t26;
double *t13 = t26;
double *t14 = A;
double *t9 = t23;
double *t11 = t23;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4352);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4352);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4352,ii+=1) {
// 2_1
int __m4352 = i + __s4352 > P_ncols ? P_ncols - i : __s4352;
double *t22 = t23 + i;
double *t21 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t21 = t21;
predict_0[disp].t22 = t22;
predict_0[disp].__s4351 = __s4351;
predict_0[disp].__m4352 = __m4352;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4352; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s4353) {
// 4_1
int __m4353 = i + __s4353 > P_ncols ? P_ncols - i : __s4353;
double *t25 = t26 + i;
double *t31 = t14 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t36 = t25 + j*P_ncols;
double *t35 = t9 + j*P_ncols;
for (k=0; k<__m4353; k+=1) {
// 4_3
double *t52 = t31 + k*P_ncols;
t36[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t36[k] += (t35[l]*t52[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s4355);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s4355);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4355,ii+=1) {
// 6_1
int __m4355 = i + __s4355 > P_ncols ? P_ncols - i : __s4355;
double *t29 = P + i;
double *t27 = t18 + i;
double *t28 = Q + i;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s4354 = __s4354;
predict_1[disp].__m4355 = __m4355;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s4355; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t26);
free(t23);
}
