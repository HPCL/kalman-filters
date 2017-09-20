#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t31;
double *t25;
int __s4314;
int __m4315;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t21;
double *t22;
int __s4312;
int __m4313;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t21 = msg->t21;
double *t22 = msg->t22;
int __s4312 = msg->__s4312;
int __m4313 = msg->__m4313;

for (j=0; j<__m4313; j+=__s4312) {
// 2_2
int __m4312 = j + __s4312 > __m4313 ? __m4313 - j : __s4312;
double *t33 = t22 + j;
double *t32 = t21 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t44 = t33 + k*P_ncols;
double *t43 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m4312; ++__zr__) t44[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t54 = t32 + l*P_ncols;
for (p=0; p<__m4312; p+=1) {
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
int __s4314 = msg->__s4314;
int __m4315 = msg->__m4315;

for (j=0; j<__m4315; j+=__s4314) {
// 4_2
int __m4314 = j + __s4314 > __m4315 ? __m4315 - j : __s4314;
double *t36 = t25 + j;
double *t42 = t31 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t47 = t36 + k*P_ncols;
double *t46 = t9 + k*P_ncols;
for (l=0; l<__m4314; l+=1) {
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

int __s4316 = 2;

int __s4314 = 488;

int __s4312 = 488;

int nparts__s4315 = 10;
int __s4315;
if (nparts__s4315 > 1 && P_ncols > nparts__s4315) {
__s4315 = P_ncols/nparts__s4315;
// this will fail if P_ncols%nparts__s4315+__s4315 > nparts__s4315
// which primarily effects small sizes
if (P_ncols%nparts__s4315)
++__s4315;
}
else {
__s4315 = P_ncols;
nparts__s4315 = 1;
}

int nparts__s4313 = 6;
int __s4313;
if (nparts__s4313 > 1 && P_ncols > nparts__s4313) {
__s4313 = P_ncols/nparts__s4313;
// this will fail if P_ncols%nparts__s4313+__s4313 > nparts__s4313
// which primarily effects small sizes
if (P_ncols%nparts__s4313)
++__s4313;
}
else {
__s4313 = P_ncols;
nparts__s4313 = 1;
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4313);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4313);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4313,ii+=1) {
// 2_1
int __m4313 = i + __s4313 > P_ncols ? P_ncols - i : __s4313;
double *t22 = t23 + i;
double *t21 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t21 = t21;
predict_0[disp].t22 = t22;
predict_0[disp].__s4312 = __s4312;
predict_0[disp].__m4313 = __m4313;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4313; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s4315);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s4315);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4315,ii+=1) {
// 4_1
int __m4315 = i + __s4315 > P_ncols ? P_ncols - i : __s4315;
double *t25 = t26 + i;
double *t31 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t31 = t31;
predict_1[disp].t25 = t25;
predict_1[disp].__s4314 = __s4314;
predict_1[disp].__m4315 = __m4315;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s4315; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s4316) {
// 6_1
int __m4316 = i + __s4316 > P_ncols ? P_ncols - i : __s4316;
double *t29 = P + i;
double *t27 = t18 + i;
double *t28 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m4316; k+=1) {
// 6_3
t40[k] = (t38[k]+t39[k]);
}
}
}
free(t26);
free(t23);
}
