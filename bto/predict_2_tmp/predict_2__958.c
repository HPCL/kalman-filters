#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m2455;
double *t25;
double *t31;
double *t12;
int __s2454;
} predict_1_msg_t;

typedef struct { 
int __m2453;
int P_ncols;
double *t21;
double *t8;
double *t22;
int __s2452;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2453 = msg->__m2453;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
double *t8 = msg->t8;
double *t22 = msg->t22;
int __s2452 = msg->__s2452;

for (j=0; j<P_ncols; j+=__s2452) {
// 2_2
int __m2452 = j + __s2452 > P_ncols ? P_ncols - j : __s2452;
double *t33 = t22 + j*P_ncols;
double *t32 = t8 + j*P_ncols;
for (k=0; k<__m2452; k+=1) {
// 2_3
double *t45 = t33 + k*P_ncols;
double *t44 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2453; ++__zr__) t45[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t55 = t21 + l*P_ncols;
for (p=0; p<__m2453; p+=1) {
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
int __m2455 = msg->__m2455;
double *t25 = msg->t25;
double *t31 = msg->t31;
double *t12 = msg->t12;
int __s2454 = msg->__s2454;

for (j=0; j<P_ncols; j+=__s2454) {
// 4_2
int __m2454 = j + __s2454 > P_ncols ? P_ncols - j : __s2454;
double *t35 = t12 + j;
double *t43 = t31 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t48 = t25 + k*P_ncols;
double *t47 = t35 + k*P_ncols;
for (l=0; l<__m2455; l+=1) {
// 4_4
double *t61 = t43 + l*P_ncols;
t48[l] = 0.0;
for (p=0; p<__m2454; p+=1) {
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

int __s2456 = 12;

int __s2454 = 512;

int __s2452 = 512;

int nparts__s2453 = 10;
int __s2453;
if (nparts__s2453 > 1 && P_ncols > nparts__s2453) {
__s2453 = P_ncols/nparts__s2453;
// this will fail if P_ncols%nparts__s2453+__s2453 > nparts__s2453
// which primarily effects small sizes
if (P_ncols%nparts__s2453)
++__s2453;
}
else {
__s2453 = P_ncols;
nparts__s2453 = 1;
}

int nparts__s2455 = 10;
int __s2455;
if (nparts__s2455 > 1 && P_ncols > nparts__s2455) {
__s2455 = P_ncols/nparts__s2455;
// this will fail if P_ncols%nparts__s2455+__s2455 > nparts__s2455
// which primarily effects small sizes
if (P_ncols%nparts__s2455)
++__s2455;
}
else {
__s2455 = P_ncols;
nparts__s2455 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t26;
double *t16 = t26;
double *t12 = t23;
double *t9 = t23;
double *t11 = t23;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2453);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2453);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2453,ii+=1) {
// 2_1
int __m2453 = i + __s2453 > P_ncols ? P_ncols - i : __s2453;
double *t22 = t23 + i;
double *t21 = P + i;
predict_0[disp].__m2453 = __m2453;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].t8 = t8;
predict_0[disp].t22 = t22;
predict_0[disp].__s2452 = __s2452;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2453; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2455);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2455);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2455,ii+=1) {
// 4_1
int __m2455 = i + __s2455 > P_ncols ? P_ncols - i : __s2455;
double *t25 = t26 + i;
double *t31 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m2455 = __m2455;
predict_1[disp].t25 = t25;
predict_1[disp].t31 = t31;
predict_1[disp].t12 = t12;
predict_1[disp].__s2454 = __s2454;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2455; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s2456) {
// 6_1
int __m2456 = i + __s2456 > P_ncols ? P_ncols - i : __s2456;
double *t29 = P + i;
double *t27 = t18 + i;
double *t28 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t41 = t29 + j*P_ncols;
double *t39 = t27 + j*P_ncols;
double *t40 = t28 + j*P_ncols;
for (k=0; k<__m2456; k+=1) {
// 6_3
t41[k] = (t39[k]+t40[k]);
}
}
}
free(t26);
free(t23);
}
