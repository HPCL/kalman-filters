#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t29;
double *t25;
double *t30;
int __s1410;
int __m1411;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *P;
double *t22;
double *t23;
int __s1408;
int __m1409;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t22 = msg->t22;
double *t23 = msg->t23;
int __s1408 = msg->__s1408;
int __m1409 = msg->__m1409;

for (j=0; j<__m1409; j+=__s1408) {
// 2_2
int __m1408 = j + __s1408 > __m1409 ? __m1409 - j : __s1408;
double *t33 = t23 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<__m1408; k+=1) {
// 2_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t53 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t43[p] += (t42[l]*t53[p]);
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
double *A = msg->A;
double *t29 = msg->t29;
double *t25 = msg->t25;
double *t30 = msg->t30;
int __s1410 = msg->__s1410;
int __m1411 = msg->__m1411;

for (j=0; j<__m1411; j+=__s1410) {
// 4_2
int __m1410 = j + __s1410 > __m1411 ? __m1411 - j : __s1410;
double *t36 = malloc(sizeof(double)*__s1410*P_ncols);
double *t40 = t30 + j*P_ncols;
double *t35 = t25 + j*P_ncols;
double *t39 = t29 + j*P_ncols;
for (k=0; k<__m1410; k+=1) {
// 4_3
double *t46 = t36 + k*P_ncols;
double *t45 = t35 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t63 = A + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t46[l] += (t45[p]*t63[p]);
}
}
}
for (k=0; k<__m1410; k+=1) {
// 6_3
double *t50 = t40 + k*P_ncols;
double *t48 = t36 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 6_4
t50[l] = (t48[l]+t49[l]);
}
}
free(t36);
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s1410 = 512;

int __s1408 = 512;

int nparts__s1411 = 10;
int __s1411;
if (nparts__s1411 > 1 && P_ncols > nparts__s1411) {
__s1411 = P_ncols/nparts__s1411;
// this will fail if P_ncols%nparts__s1411+__s1411 > nparts__s1411
// which primarily effects small sizes
if (P_ncols%nparts__s1411)
++__s1411;
}
else {
__s1411 = P_ncols;
nparts__s1411 = 1;
}

int nparts__s1409 = 10;
int __s1409;
if (nparts__s1409 > 1 && P_ncols > nparts__s1409) {
__s1409 = P_ncols/nparts__s1409;
// this will fail if P_ncols%nparts__s1409+__s1409 > nparts__s1409
// which primarily effects small sizes
if (P_ncols%nparts__s1409)
++__s1409;
}
else {
__s1409 = P_ncols;
nparts__s1409 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t24;
double *t12 = t24;
double *t9 = t24;
double *t11 = t24;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1409);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1409);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1409,ii+=1) {
// 2_1
int __m1409 = i + __s1409 > P_ncols ? P_ncols - i : __s1409;
double *t23 = t24 + i*P_ncols;
double *t22 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t22 = t22;
predict_0[disp].t23 = t23;
predict_0[disp].__s1408 = __s1408;
predict_0[disp].__m1409 = __m1409;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1409; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1411);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1411);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1411,ii+=1) {
// 4_1
int __m1411 = i + __s1411 > P_ncols ? P_ncols - i : __s1411;
double *t30 = P + i*P_ncols;
double *t25 = t14 + i*P_ncols;
double *t29 = Q + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].A = A;
predict_1[disp].t29 = t29;
predict_1[disp].t25 = t25;
predict_1[disp].t30 = t30;
predict_1[disp].__s1410 = __s1410;
predict_1[disp].__m1411 = __m1411;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1411; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t24);
}
