#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m4197;
double *t25;
double *t31;
double *t12;
int __s4196;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t21;
double *t22;
int __s4194;
int __m4195;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t21 = msg->t21;
double *t22 = msg->t22;
int __s4194 = msg->__s4194;
int __m4195 = msg->__m4195;

for (j=0; j<__m4195; j+=__s4194) {
// 2_2
int __m4194 = j + __s4194 > __m4195 ? __m4195 - j : __s4194;
double *t33 = t22 + j;
double *t32 = t21 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t45 = t33 + k*P_ncols;
double *t44 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m4194; ++__zr__) t45[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t55 = t32 + l*P_ncols;
for (p=0; p<__m4194; p+=1) {
// 2_5
t45[p] += (t44[l]*t55[p]);
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
int __m4197 = msg->__m4197;
double *t25 = msg->t25;
double *t31 = msg->t31;
double *t12 = msg->t12;
int __s4196 = msg->__s4196;

for (j=0; j<P_ncols; j+=__s4196) {
// 4_2
int __m4196 = j + __s4196 > P_ncols ? P_ncols - j : __s4196;
double *t35 = t12 + j;
double *t43 = t31 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t48 = t25 + k*P_ncols;
double *t47 = t35 + k*P_ncols;
for (l=0; l<__m4197; l+=1) {
// 4_4
double *t61 = t43 + l*P_ncols;
t48[l] = 0.0;
for (p=0; p<__m4196; p+=1) {
// 4_5
t48[l] += (t47[p]*t61[p]);
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

int __s4198 = 12;

int __s4196 = 488;

int __s4194 = 488;

int nparts__s4195 = 8;
int __s4195;
if (nparts__s4195 > 1 && P_ncols > nparts__s4195) {
__s4195 = P_ncols/nparts__s4195;
// this will fail if P_ncols%nparts__s4195+__s4195 > nparts__s4195
// which primarily effects small sizes
if (P_ncols%nparts__s4195)
++__s4195;
}
else {
__s4195 = P_ncols;
nparts__s4195 = 1;
}

int nparts__s4197 = 10;
int __s4197;
if (nparts__s4197 > 1 && P_ncols > nparts__s4197) {
__s4197 = P_ncols/nparts__s4197;
// this will fail if P_ncols%nparts__s4197+__s4197 > nparts__s4197
// which primarily effects small sizes
if (P_ncols%nparts__s4197)
++__s4197;
}
else {
__s4197 = P_ncols;
nparts__s4197 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t26;
double *t16 = t26;
double *t17 = A;
double *t14 = A;
double *t12 = t23;
double *t9 = t23;
double *t11 = t23;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4195);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4195);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4195,ii+=1) {
// 2_1
int __m4195 = i + __s4195 > P_ncols ? P_ncols - i : __s4195;
double *t22 = t23 + i;
double *t21 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t21 = t21;
predict_0[disp].t22 = t22;
predict_0[disp].__s4194 = __s4194;
predict_0[disp].__m4195 = __m4195;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4195; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s4197);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s4197);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4197,ii+=1) {
// 4_1
int __m4197 = i + __s4197 > P_ncols ? P_ncols - i : __s4197;
double *t25 = t26 + i;
double *t31 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m4197 = __m4197;
predict_1[disp].t25 = t25;
predict_1[disp].t31 = t31;
predict_1[disp].t12 = t12;
predict_1[disp].__s4196 = __s4196;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s4197; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s4198) {
// 6_1
int __m4198 = i + __s4198 > P_ncols ? P_ncols - i : __s4198;
double *t29 = P + i;
double *t27 = t18 + i;
double *t28 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t41 = t29 + j*P_ncols;
double *t39 = t27 + j*P_ncols;
double *t40 = t28 + j*P_ncols;
for (k=0; k<__m4198; k+=1) {
// 6_3
t41[k] = (t39[k]+t40[k]);
}
}
}
free(t26);
free(t23);
}
