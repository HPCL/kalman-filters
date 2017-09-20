#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t29;
double *t28;
double *t30;
int __s221;
int __m222;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t25;
double *t26;
int __s219;
int __m220;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *P;
double *t22;
double *t23;
int __s217;
int __m218;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t22 = msg->t22;
double *t23 = msg->t23;
int __s217 = msg->__s217;
int __m218 = msg->__m218;

for (j=0; j<__m218; j+=__s217) {
// 2_2
int __m217 = j + __s217 > __m218 ? __m218 - j : __s217;
double *t33 = t23 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<__m217; k+=1) {
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
double *t25 = msg->t25;
double *t26 = msg->t26;
int __s219 = msg->__s219;
int __m220 = msg->__m220;

for (j=0; j<__m220; j+=__s219) {
// 4_2
int __m219 = j + __s219 > __m220 ? __m220 - j : __s219;
double *t36 = t26 + j*P_ncols;
double *t35 = t25 + j*P_ncols;
for (k=0; k<__m219; k+=1) {
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
}
return NULL;
}


void *predict_body_2(void *mesg) {
int disp, __zr__,j,k,l;
predict_2_msg_t *msg = (predict_2_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t28 = msg->t28;
double *t30 = msg->t30;
int __s221 = msg->__s221;
int __m222 = msg->__m222;

for (j=0; j<__m222; j+=__s221) {
// 6_2
int __m221 = j + __s221 > __m222 ? __m222 - j : __s221;
double *t40 = t30 + j*P_ncols;
double *t38 = t28 + j*P_ncols;
double *t39 = t29 + j*P_ncols;
for (k=0; k<__m221; k+=1) {
// 6_3
double *t50 = t40 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 6_4
t50[l] = (t48[l]+t49[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s221 = 512;

int __s219 = 512;

int __s217 = 512;

int nparts__s222 = 12;
int __s222;
if (nparts__s222 > 1 && P_ncols > nparts__s222) {
__s222 = P_ncols/nparts__s222;
// this will fail if P_ncols%nparts__s222+__s222 > nparts__s222
// which primarily effects small sizes
if (P_ncols%nparts__s222)
++__s222;
}
else {
__s222 = P_ncols;
nparts__s222 = 1;
}

int nparts__s220 = 12;
int __s220;
if (nparts__s220 > 1 && P_ncols > nparts__s220) {
__s220 = P_ncols/nparts__s220;
// this will fail if P_ncols%nparts__s220+__s220 > nparts__s220
// which primarily effects small sizes
if (P_ncols%nparts__s220)
++__s220;
}
else {
__s220 = P_ncols;
nparts__s220 = 1;
}

int nparts__s218 = 12;
int __s218;
if (nparts__s218 > 1 && P_ncols > nparts__s218) {
__s218 = P_ncols/nparts__s218;
// this will fail if P_ncols%nparts__s218+__s218 > nparts__s218
// which primarily effects small sizes
if (P_ncols%nparts__s218)
++__s218;
}
else {
__s218 = P_ncols;
nparts__s218 = 1;
}

double *t27 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = t27;
double *t16 = t27;
double *t13 = t27;
double *t15 = t27;
double *t14 = t24;
double *t12 = t24;
double *t9 = t24;
double *t11 = t24;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s218);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s218);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s218,ii+=1) {
// 2_1
int __m218 = i + __s218 > P_ncols ? P_ncols - i : __s218;
double *t23 = t24 + i*P_ncols;
double *t22 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t22 = t22;
predict_0[disp].t23 = t23;
predict_0[disp].__s217 = __s217;
predict_0[disp].__m218 = __m218;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s218; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s220);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s220);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s220,ii+=1) {
// 4_1
int __m220 = i + __s220 > P_ncols ? P_ncols - i : __s220;
double *t26 = t27 + i*P_ncols;
double *t25 = t14 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].A = A;
predict_1[disp].t25 = t25;
predict_1[disp].t26 = t26;
predict_1[disp].__s219 = __s219;
predict_1[disp].__m220 = __m220;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s220; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s222);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s222);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s222,ii+=1) {
// 6_1
int __m222 = i + __s222 > P_ncols ? P_ncols - i : __s222;
double *t30 = P + i*P_ncols;
double *t28 = t19 + i*P_ncols;
double *t29 = Q + i*P_ncols;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t29 = t29;
predict_2[disp].t28 = t28;
predict_2[disp].t30 = t30;
predict_2[disp].__s221 = __s221;
predict_2[disp].__m222 = __m222;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s222; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t27);
free(t24);
}
