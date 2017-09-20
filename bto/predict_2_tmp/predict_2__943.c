#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m2403;
double *t25;
double *t31;
double *t12;
int __s2402;
} predict_1_msg_t;

typedef struct { 
int __m2401;
int P_ncols;
double *t22;
double *t21;
double *t8;
int __s2400;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2401 = msg->__m2401;
int P_ncols = msg->P_ncols;
double *t22 = msg->t22;
double *t21 = msg->t21;
double *t8 = msg->t8;
int __s2400 = msg->__s2400;

for (j=0; j<P_ncols; j+=__s2400) {
// 2_2
int __m2400 = j + __s2400 > P_ncols ? P_ncols - j : __s2400;
double *t32 = t8 + j;
double *t33 = t21 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t46 = t22 + k*P_ncols;
double *t45 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2401; ++__zr__) t46[__zr__] = 0.0;
for (l=0; l<__m2400; l+=1) {
// 2_4
double *t56 = t33 + l*P_ncols;
for (p=0; p<__m2401; p+=1) {
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
int __m2403 = msg->__m2403;
double *t25 = msg->t25;
double *t31 = msg->t31;
double *t12 = msg->t12;
int __s2402 = msg->__s2402;

for (j=0; j<P_ncols; j+=__s2402) {
// 4_2
int __m2402 = j + __s2402 > P_ncols ? P_ncols - j : __s2402;
double *t36 = t12 + j;
double *t44 = t31 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t49 = t25 + k*P_ncols;
double *t48 = t36 + k*P_ncols;
for (l=0; l<__m2403; l+=1) {
// 4_4
double *t62 = t44 + l*P_ncols;
t49[l] = 0.0;
for (p=0; p<__m2402; p+=1) {
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

int __s2404 = 12;

int __s2402 = 504;

int __s2400 = 504;

int nparts__s2401 = 10;
int __s2401;
if (nparts__s2401 > 1 && P_ncols > nparts__s2401) {
__s2401 = P_ncols/nparts__s2401;
// this will fail if P_ncols%nparts__s2401+__s2401 > nparts__s2401
// which primarily effects small sizes
if (P_ncols%nparts__s2401)
++__s2401;
}
else {
__s2401 = P_ncols;
nparts__s2401 = 1;
}

int nparts__s2403 = 10;
int __s2403;
if (nparts__s2403 > 1 && P_ncols > nparts__s2403) {
__s2403 = P_ncols/nparts__s2403;
// this will fail if P_ncols%nparts__s2403+__s2403 > nparts__s2403
// which primarily effects small sizes
if (P_ncols%nparts__s2403)
++__s2403;
}
else {
__s2403 = P_ncols;
nparts__s2403 = 1;
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2401);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2401);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2401,ii+=1) {
// 2_1
int __m2401 = i + __s2401 > P_ncols ? P_ncols - i : __s2401;
double *t22 = t23 + i;
double *t21 = P + i;
predict_0[disp].__m2401 = __m2401;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t22 = t22;
predict_0[disp].t21 = t21;
predict_0[disp].t8 = t8;
predict_0[disp].__s2400 = __s2400;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2401; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2403);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2403);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2403,ii+=1) {
// 4_1
int __m2403 = i + __s2403 > P_ncols ? P_ncols - i : __s2403;
double *t25 = t26 + i;
double *t31 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m2403 = __m2403;
predict_1[disp].t25 = t25;
predict_1[disp].t31 = t31;
predict_1[disp].t12 = t12;
predict_1[disp].__s2402 = __s2402;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2403; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s2404) {
// 6_1
int __m2404 = i + __s2404 > P_ncols ? P_ncols - i : __s2404;
double *t29 = P + i*P_ncols;
double *t27 = t18 + i*P_ncols;
double *t28 = Q + i*P_ncols;
for (j=0; j<__m2404; j+=1) {
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
