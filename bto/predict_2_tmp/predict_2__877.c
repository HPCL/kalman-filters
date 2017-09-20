#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2207;
int P_ncols;
double *t29;
double *t28;
double *t30;
int __s2206;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t25;
double *t26;
int __s2204;
int __m2205;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t22;
int __m2203;
double *P;
double *t23;
int __s2202;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t22 = msg->t22;
int __m2203 = msg->__m2203;
double *P = msg->P;
double *t23 = msg->t23;
int __s2202 = msg->__s2202;

for (j=0; j<P_ncols; j+=__s2202) {
// 2_2
int __m2202 = j + __s2202 > P_ncols ? P_ncols - j : __s2202;
double *t33 = t23 + j;
double *t32 = P + j;
for (k=0; k<__m2203; k+=1) {
// 2_3
double *t43 = t33 + k*P_ncols;
double *t42 = t22 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2202; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t53 = t32 + l*P_ncols;
for (p=0; p<__m2202; p+=1) {
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
int __s2204 = msg->__s2204;
int __m2205 = msg->__m2205;

for (j=0; j<__m2205; j+=__s2204) {
// 4_2
int __m2204 = j + __s2204 > __m2205 ? __m2205 - j : __s2204;
double *t36 = t26 + j*P_ncols;
double *t35 = t25 + j*P_ncols;
for (k=0; k<__m2204; k+=1) {
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
int __m2207 = msg->__m2207;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t28 = msg->t28;
double *t30 = msg->t30;
int __s2206 = msg->__s2206;

for (j=0; j<P_ncols; j+=__s2206) {
// 6_2
int __m2206 = j + __s2206 > P_ncols ? P_ncols - j : __s2206;
double *t40 = t30 + j*P_ncols;
double *t38 = t28 + j*P_ncols;
double *t39 = t29 + j*P_ncols;
for (k=0; k<__m2206; k+=1) {
// 6_3
double *t50 = t40 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<__m2207; l+=1) {
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

int __s2206 = 512;

int __s2204 = 512;

int __s2202 = 512;

int nparts__s2205 = 12;
int __s2205;
if (nparts__s2205 > 1 && P_ncols > nparts__s2205) {
__s2205 = P_ncols/nparts__s2205;
// this will fail if P_ncols%nparts__s2205+__s2205 > nparts__s2205
// which primarily effects small sizes
if (P_ncols%nparts__s2205)
++__s2205;
}
else {
__s2205 = P_ncols;
nparts__s2205 = 1;
}

int nparts__s2203 = 12;
int __s2203;
if (nparts__s2203 > 1 && P_ncols > nparts__s2203) {
__s2203 = P_ncols/nparts__s2203;
// this will fail if P_ncols%nparts__s2203+__s2203 > nparts__s2203
// which primarily effects small sizes
if (P_ncols%nparts__s2203)
++__s2203;
}
else {
__s2203 = P_ncols;
nparts__s2203 = 1;
}

int nparts__s2207 = 12;
int __s2207;
if (nparts__s2207 > 1 && P_ncols > nparts__s2207) {
__s2207 = P_ncols/nparts__s2207;
// this will fail if P_ncols%nparts__s2207+__s2207 > nparts__s2207
// which primarily effects small sizes
if (P_ncols%nparts__s2207)
++__s2207;
}
else {
__s2207 = P_ncols;
nparts__s2207 = 1;
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2203);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2203);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2203,ii+=1) {
// 2_1
int __m2203 = i + __s2203 > P_ncols ? P_ncols - i : __s2203;
double *t23 = t24 + i*P_ncols;
double *t22 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t22 = t22;
predict_0[disp].__m2203 = __m2203;
predict_0[disp].P = P;
predict_0[disp].t23 = t23;
predict_0[disp].__s2202 = __s2202;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2203; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2205);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2205);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2205,ii+=1) {
// 4_1
int __m2205 = i + __s2205 > P_ncols ? P_ncols - i : __s2205;
double *t26 = t27 + i*P_ncols;
double *t25 = t14 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].A = A;
predict_1[disp].t25 = t25;
predict_1[disp].t26 = t26;
predict_1[disp].__s2204 = __s2204;
predict_1[disp].__m2205 = __m2205;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2205; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s2207);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s2207);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2207,ii+=1) {
// 6_1
int __m2207 = i + __s2207 > P_ncols ? P_ncols - i : __s2207;
double *t30 = P + i;
double *t28 = t19 + i;
double *t29 = Q + i;
predict_2[disp].__m2207 = __m2207;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t29 = t29;
predict_2[disp].t28 = t28;
predict_2[disp].t30 = t30;
predict_2[disp].__s2206 = __s2206;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s2207; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t27);
free(t24);
}
