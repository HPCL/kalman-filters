#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m2396;
double *t25;
double *t31;
double *t12;
int __s2395;
} predict_1_msg_t;

typedef struct { 
int __m2394;
int P_ncols;
double *t22;
double *t21;
double *t8;
int __s2393;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2394 = msg->__m2394;
int P_ncols = msg->P_ncols;
double *t22 = msg->t22;
double *t21 = msg->t21;
double *t8 = msg->t8;
int __s2393 = msg->__s2393;

for (j=0; j<P_ncols; j+=__s2393) {
// 2_2
int __m2393 = j + __s2393 > P_ncols ? P_ncols - j : __s2393;
double *t32 = t8 + j;
double *t33 = t21 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t46 = t22 + k*P_ncols;
double *t45 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2394; ++__zr__) t46[__zr__] = 0.0;
for (l=0; l<__m2393; l+=1) {
// 2_4
double *t56 = t33 + l*P_ncols;
for (p=0; p<__m2394; p+=1) {
// 2_5
t46[p] += (t45[l]*t56[p]);
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
int __m2396 = msg->__m2396;
double *t25 = msg->t25;
double *t31 = msg->t31;
double *t12 = msg->t12;
int __s2395 = msg->__s2395;

for (j=0; j<P_ncols; j+=__s2395) {
// 4_2
int __m2395 = j + __s2395 > P_ncols ? P_ncols - j : __s2395;
double *t36 = t12 + j;
double *t44 = t31 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t49 = t25 + k*P_ncols;
double *t48 = t36 + k*P_ncols;
for (l=0; l<__m2396; l+=1) {
// 4_4
double *t62 = t44 + l*P_ncols;
t49[l] = 0.0;
for (p=0; p<__m2395; p+=1) {
// 4_5
t49[l] += (t48[p]*t62[p]);
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

int __s2397 = 12;

int __s2395 = 512;

int __s2393 = 512;

int nparts__s2394 = 10;
int __s2394;
if (nparts__s2394 > 1 && P_ncols > nparts__s2394) {
__s2394 = P_ncols/nparts__s2394;
// this will fail if P_ncols%nparts__s2394+__s2394 > nparts__s2394
// which primarily effects small sizes
if (P_ncols%nparts__s2394)
++__s2394;
}
else {
__s2394 = P_ncols;
nparts__s2394 = 1;
}

int nparts__s2396 = 10;
int __s2396;
if (nparts__s2396 > 1 && P_ncols > nparts__s2396) {
__s2396 = P_ncols/nparts__s2396;
// this will fail if P_ncols%nparts__s2396+__s2396 > nparts__s2396
// which primarily effects small sizes
if (P_ncols%nparts__s2396)
++__s2396;
}
else {
__s2396 = P_ncols;
nparts__s2396 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t26;
double *t16 = t26;
double *t12 = t23;
double *t11 = t23;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2394);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2394);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2394,ii+=1) {
// 2_1
int __m2394 = i + __s2394 > P_ncols ? P_ncols - i : __s2394;
double *t22 = t23 + i;
double *t21 = P + i;
predict_0[disp].__m2394 = __m2394;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t22 = t22;
predict_0[disp].t21 = t21;
predict_0[disp].t8 = t8;
predict_0[disp].__s2393 = __s2393;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2394; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2396);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2396);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2396,ii+=1) {
// 4_1
int __m2396 = i + __s2396 > P_ncols ? P_ncols - i : __s2396;
double *t25 = t26 + i;
double *t31 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m2396 = __m2396;
predict_1[disp].t25 = t25;
predict_1[disp].t31 = t31;
predict_1[disp].t12 = t12;
predict_1[disp].__s2395 = __s2395;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2396; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s2397) {
// 6_1
int __m2397 = i + __s2397 > P_ncols ? P_ncols - i : __s2397;
double *t29 = P + i*P_ncols;
double *t27 = t18 + i*P_ncols;
double *t28 = Q + i*P_ncols;
for (j=0; j<__m2397; j+=1) {
// 6_2
double *t42 = t29 + j*P_ncols;
double *t40 = t27 + j*P_ncols;
double *t41 = t28 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t42[k] = (t40[k]+t41[k]);
}
}
}
free(t26);
free(t23);
}
