#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m2722;
double *t31;
double *t32;
int __s2723;
double *t9;
double *t34;
int __s2721;
int __s2722;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *P;
double *t24;
double *t25;
int __s2719;
int __m2720;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t24 = msg->t24;
double *t25 = msg->t25;
int __s2719 = msg->__s2719;
int __m2720 = msg->__m2720;

for (j=0; j<__m2720; j+=__s2719) {
// 2_2
int __m2719 = j + __s2719 > __m2720 ? __m2720 - j : __s2719;
double *t36 = t25 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
for (k=0; k<__m2719; k+=1) {
// 2_3
double *t47 = t36 + k*P_ncols;
double *t46 = t35 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t47[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t57 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t47[p] += (t46[l]*t57[p]);
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
int __m2722 = msg->__m2722;
double *t31 = msg->t31;
double *t32 = msg->t32;
int __s2723 = msg->__s2723;
double *t9 = msg->t9;
double *t34 = msg->t34;
int __s2721 = msg->__s2721;
int __s2722 = msg->__s2722;

double *t28 = malloc(sizeof(double)*__s2722*P_ncols);
for (j=0; j<__m2722; j+=__s2721) {
// 4_2
int __m2721 = j + __s2721 > __m2722 ? __m2722 - j : __s2721;
double *t39 = t28 + j;
double *t45 = t34 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t50 = t39 + k*__m2722;
double *t49 = t9 + k*P_ncols;
for (l=0; l<__m2721; l+=1) {
// 4_4
double *t67 = t45 + l*P_ncols;
t50[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t50[l] += (t49[p]*t67[p]);
}
}
}
}
for (j=0; j<__m2722; j+=__s2723) {
// 6_2
int __m2723 = j + __s2723 > __m2722 ? __m2722 - j : __s2723;
double *t43 = t32 + j;
double *t41 = t28 + j;
double *t42 = t31 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t54 = t43 + k*P_ncols;
double *t52 = t41 + k*__m2722;
double *t53 = t42 + k*P_ncols;
for (l=0; l<__m2723; l+=1) {
// 6_4
t54[l] = (t52[l]+t53[l]);
}
}
}
free(t28);
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s2723 = 504;

int __s2721 = 504;

int __s2719 = 512;

int nparts__s2722 = 12;
int __s2722;
if (nparts__s2722 > 1 && P_ncols > nparts__s2722) {
__s2722 = P_ncols/nparts__s2722;
// this will fail if P_ncols%nparts__s2722+__s2722 > nparts__s2722
// which primarily effects small sizes
if (P_ncols%nparts__s2722)
++__s2722;
}
else {
__s2722 = P_ncols;
nparts__s2722 = 1;
}

int nparts__s2720 = 10;
int __s2720;
if (nparts__s2720 > 1 && P_ncols > nparts__s2720) {
__s2720 = P_ncols/nparts__s2720;
// this will fail if P_ncols%nparts__s2720+__s2720 > nparts__s2720
// which primarily effects small sizes
if (P_ncols%nparts__s2720)
++__s2720;
}
else {
__s2720 = P_ncols;
nparts__s2720 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t26;
double *t11 = t26;
double *t10 = A;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2720);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2720);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2720,ii+=1) {
// 2_1
int __m2720 = i + __s2720 > P_ncols ? P_ncols - i : __s2720;
double *t25 = t26 + i*P_ncols;
double *t24 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t24 = t24;
predict_0[disp].t25 = t25;
predict_0[disp].__s2719 = __s2719;
predict_0[disp].__m2720 = __m2720;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2720; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2722);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2722);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2722,ii+=1) {
// 4_1
int __m2722 = i + __s2722 > P_ncols ? P_ncols - i : __s2722;
double *t32 = P + i;
double *t34 = t17 + i*P_ncols;
double *t31 = Q + i;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m2722 = __m2722;
predict_1[disp].t31 = t31;
predict_1[disp].t32 = t32;
predict_1[disp].__s2723 = __s2723;
predict_1[disp].t9 = t9;
predict_1[disp].t34 = t34;
predict_1[disp].__s2721 = __s2721;
predict_1[disp].__s2722 = __s2722;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2722; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t26);
}
