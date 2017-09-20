#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m3112;
int P_ncols;
double *t27;
double *t26;
double *t28;
int __s3111;
} predict_1_msg_t;

typedef struct { 
int __m3109;
int P_ncols;
double *t20;
double *t8;
double *t21;
int __s3108;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m3109 = msg->__m3109;
int P_ncols = msg->P_ncols;
double *t20 = msg->t20;
double *t8 = msg->t8;
double *t21 = msg->t21;
int __s3108 = msg->__s3108;

for (j=0; j<P_ncols; j+=__s3108) {
// 2_2
int __m3108 = j + __s3108 > P_ncols ? P_ncols - j : __s3108;
double *t31 = t21 + j*P_ncols;
double *t30 = t8 + j*P_ncols;
for (k=0; k<__m3108; k+=1) {
// 2_3
double *t41 = t31 + k*P_ncols;
double *t40 = t30 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3109; ++__zr__) t41[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t52 = t20 + l*P_ncols;
for (p=0; p<__m3109; p+=1) {
// 2_5
t41[p] += (t40[l]*t52[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m3112 = msg->__m3112;
int P_ncols = msg->P_ncols;
double *t27 = msg->t27;
double *t26 = msg->t26;
double *t28 = msg->t28;
int __s3111 = msg->__s3111;

for (j=0; j<P_ncols; j+=__s3111) {
// 6_2
int __m3111 = j + __s3111 > P_ncols ? P_ncols - j : __s3111;
double *t38 = t28 + j*P_ncols;
double *t36 = t26 + j*P_ncols;
double *t37 = t27 + j*P_ncols;
for (k=0; k<__m3111; k+=1) {
// 6_3
double *t48 = t38 + k*P_ncols;
double *t46 = t36 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
for (l=0; l<__m3112; l+=1) {
// 6_4
t48[l] = (t46[l]+t47[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s3111 = 504;

int __s3110 = 12;

int __s3108 = 504;

int nparts__s3109 = 12;
int __s3109;
if (nparts__s3109 > 1 && P_ncols > nparts__s3109) {
__s3109 = P_ncols/nparts__s3109;
// this will fail if P_ncols%nparts__s3109+__s3109 > nparts__s3109
// which primarily effects small sizes
if (P_ncols%nparts__s3109)
++__s3109;
}
else {
__s3109 = P_ncols;
nparts__s3109 = 1;
}

int nparts__s3112 = 12;
int __s3112;
if (nparts__s3112 > 1 && P_ncols > nparts__s3112) {
__s3112 = P_ncols/nparts__s3112;
// this will fail if P_ncols%nparts__s3112+__s3112 > nparts__s3112
// which primarily effects small sizes
if (P_ncols%nparts__s3112)
++__s3112;
}
else {
__s3112 = P_ncols;
nparts__s3112 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = t25;
double *t14 = t25;
double *t13 = t25;
double *t12 = t22;
double *t9 = t22;
double *t11 = t22;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3109);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3109);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3109,ii+=1) {
// 2_1
int __m3109 = i + __s3109 > P_ncols ? P_ncols - i : __s3109;
double *t21 = t22 + i;
double *t20 = P + i;
predict_0[disp].__m3109 = __m3109;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t20 = t20;
predict_0[disp].t8 = t8;
predict_0[disp].t21 = t21;
predict_0[disp].__s3108 = __s3108;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3109; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s3110) {
// 4_1
int __m3110 = i + __s3110 > P_ncols ? P_ncols - i : __s3110;
double *t24 = t25 + i*P_ncols;
double *t23 = t12 + i*P_ncols;
for (j=0; j<__m3110; j+=1) {
// 4_2
double *t34 = t24 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t50 = A + k*P_ncols;
t34[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t34[k] += (t33[l]*t50[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3112);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3112);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3112,ii+=1) {
// 6_1
int __m3112 = i + __s3112 > P_ncols ? P_ncols - i : __s3112;
double *t28 = P + i;
double *t26 = t17 + i;
double *t27 = Q + i;
predict_1[disp].__m3112 = __m3112;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t27 = t27;
predict_1[disp].t26 = t26;
predict_1[disp].t28 = t28;
predict_1[disp].__s3111 = __s3111;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3112; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t25);
free(t22);
}
