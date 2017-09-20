#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t20;
int __m4339;
double *t14;
double *t21;
int __s4338;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t17;
double *t18;
int __s4336;
int __m4337;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t17 = msg->t17;
double *t18 = msg->t18;
int __s4336 = msg->__s4336;
int __m4337 = msg->__m4337;

for (j=0; j<__m4337; j+=__s4336) {
// 2_2
int __m4336 = j + __s4336 > __m4337 ? __m4337 - j : __s4336;
double *t28 = t18 + j;
double *t27 = t17 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t39 = t28 + k*P_ncols;
double *t38 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m4336; ++__zr__) t39[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t45 = t27 + l*P_ncols;
for (p=0; p<__m4336; p+=1) {
// 2_5
t39[p] += (t38[l]*t45[p]);
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
double *t20 = msg->t20;
int __m4339 = msg->__m4339;
double *t14 = msg->t14;
double *t21 = msg->t21;
int __s4338 = msg->__s4338;

for (j=0; j<P_ncols; j+=__s4338) {
// 4_2
int __m4338 = j + __s4338 > P_ncols ? P_ncols - j : __s4338;
double *t31 = t21 + j;
double *t37 = t14 + j*P_ncols;
for (k=0; k<__m4339; k+=1) {
// 4_3
double *t42 = t31 + k*P_ncols;
double *t41 = t20 + k*P_ncols;
for (l=0; l<__m4338; l+=1) {
// 4_4
double *t51 = t37 + l*P_ncols;
t42[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t42[l] += (t41[p]*t51[p]);
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

int __s4338 = 488;

int __s4336 = 488;

int nparts__s4337 = 6;
int __s4337;
if (nparts__s4337 > 1 && P_ncols > nparts__s4337) {
__s4337 = P_ncols/nparts__s4337;
// this will fail if P_ncols%nparts__s4337+__s4337 > nparts__s4337
// which primarily effects small sizes
if (P_ncols%nparts__s4337)
++__s4337;
}
else {
__s4337 = P_ncols;
nparts__s4337 = 1;
}

int nparts__s4339 = 10;
int __s4339;
if (nparts__s4339 > 1 && P_ncols > nparts__s4339) {
__s4339 = P_ncols/nparts__s4339;
// this will fail if P_ncols%nparts__s4339+__s4339 > nparts__s4339
// which primarily effects small sizes
if (P_ncols%nparts__s4339)
++__s4339;
}
else {
__s4339 = P_ncols;
nparts__s4339 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t22;
double *t16 = t22;
double *t14 = A;
double *t15 = t19;
double *t9 = t19;
double *t11 = t19;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4337);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4337);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4337,ii+=1) {
// 2_1
int __m4337 = i + __s4337 > P_ncols ? P_ncols - i : __s4337;
double *t18 = t19 + i;
double *t17 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t17 = t17;
predict_0[disp].t18 = t18;
predict_0[disp].__s4336 = __s4336;
predict_0[disp].__m4337 = __m4337;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4337; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s4339);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s4339);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4339,ii+=1) {
// 4_1
int __m4339 = i + __s4339 > P_ncols ? P_ncols - i : __s4339;
double *t21 = t22 + i*P_ncols;
double *t20 = t15 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t20 = t20;
predict_1[disp].__m4339 = __m4339;
predict_1[disp].t14 = t14;
predict_1[disp].t21 = t21;
predict_1[disp].__s4338 = __s4338;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s4339; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t25 = P + i*P_ncols;
double *t23 = t13 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t25[j] = (t23[j]+t24[j]);
}
}
free(t22);
free(t19);
}
