#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t23;
int __m3856;
double *t14;
double *t24;
int __s3855;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t20;
int __m3854;
double *P;
double *t21;
int __s3853;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t20 = msg->t20;
int __m3854 = msg->__m3854;
double *P = msg->P;
double *t21 = msg->t21;
int __s3853 = msg->__s3853;

for (j=0; j<P_ncols; j+=__s3853) {
// 2_2
int __m3853 = j + __s3853 > P_ncols ? P_ncols - j : __s3853;
double *t31 = t21 + j;
double *t30 = P + j;
for (k=0; k<__m3854; k+=1) {
// 2_3
double *t42 = t31 + k*P_ncols;
double *t41 = t20 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3853; ++__zr__) t42[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t52 = t30 + l*P_ncols;
for (p=0; p<__m3853; p+=1) {
// 2_5
t42[p] += (t41[l]*t52[p]);
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
double *t23 = msg->t23;
int __m3856 = msg->__m3856;
double *t14 = msg->t14;
double *t24 = msg->t24;
int __s3855 = msg->__s3855;

for (j=0; j<P_ncols; j+=__s3855) {
// 4_2
int __m3855 = j + __s3855 > P_ncols ? P_ncols - j : __s3855;
double *t34 = t24 + j;
double *t40 = t14 + j*P_ncols;
for (k=0; k<__m3856; k+=1) {
// 4_3
double *t45 = t34 + k*P_ncols;
double *t44 = t23 + k*P_ncols;
for (l=0; l<__m3855; l+=1) {
// 4_4
double *t58 = t40 + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t45[l] += (t44[p]*t58[p]);
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

int __s3857 = 10;

int __s3855 = 512;

int __s3853 = 512;

int nparts__s3854 = 10;
int __s3854;
if (nparts__s3854 > 1 && P_ncols > nparts__s3854) {
__s3854 = P_ncols/nparts__s3854;
// this will fail if P_ncols%nparts__s3854+__s3854 > nparts__s3854
// which primarily effects small sizes
if (P_ncols%nparts__s3854)
++__s3854;
}
else {
__s3854 = P_ncols;
nparts__s3854 = 1;
}

int nparts__s3856 = 10;
int __s3856;
if (nparts__s3856 > 1 && P_ncols > nparts__s3856) {
__s3856 = P_ncols/nparts__s3856;
// this will fail if P_ncols%nparts__s3856+__s3856 > nparts__s3856
// which primarily effects small sizes
if (P_ncols%nparts__s3856)
++__s3856;
}
else {
__s3856 = P_ncols;
nparts__s3856 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = t25;
double *t13 = t25;
double *t16 = t25;
double *t15 = t22;
double *t9 = t22;
double *t11 = t22;
double *t10 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3854);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3854);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3854,ii+=1) {
// 2_1
int __m3854 = i + __s3854 > P_ncols ? P_ncols - i : __s3854;
double *t21 = t22 + i*P_ncols;
double *t20 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t20 = t20;
predict_0[disp].__m3854 = __m3854;
predict_0[disp].P = P;
predict_0[disp].t21 = t21;
predict_0[disp].__s3853 = __s3853;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3854; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3856);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3856);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3856,ii+=1) {
// 4_1
int __m3856 = i + __s3856 > P_ncols ? P_ncols - i : __s3856;
double *t24 = t25 + i*P_ncols;
double *t23 = t15 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t23 = t23;
predict_1[disp].__m3856 = __m3856;
predict_1[disp].t14 = t14;
predict_1[disp].t24 = t24;
predict_1[disp].__s3855 = __s3855;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3856; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s3857) {
// 6_1
int __m3857 = i + __s3857 > P_ncols ? P_ncols - i : __s3857;
double *t28 = P + i;
double *t26 = t17 + i;
double *t27 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t38 = t28 + j*P_ncols;
double *t36 = t26 + j*P_ncols;
double *t37 = t27 + j*P_ncols;
for (k=0; k<__m3857; k+=1) {
// 6_3
t38[k] = (t36[k]+t37[k]);
}
}
}
free(t25);
free(t22);
}
