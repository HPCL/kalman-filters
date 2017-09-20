#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t27;
double *t26;
double *t28;
int __s240;
int __m241;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t23;
double *t24;
int __s238;
int __m239;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t23 = msg->t23;
double *t24 = msg->t24;
int __s238 = msg->__s238;
int __m239 = msg->__m239;

for (j=0; j<__m239; j+=__s238) {
// 4_2
int __m238 = j + __s238 > __m239 ? __m239 - j : __s238;
double *t34 = t24 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
for (k=0; k<__m238; k+=1) {
// 4_3
double *t45 = t34 + k*P_ncols;
double *t44 = t33 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t61 = A + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t45[l] += (t44[p]*t61[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t27 = msg->t27;
double *t26 = msg->t26;
double *t28 = msg->t28;
int __s240 = msg->__s240;
int __m241 = msg->__m241;

for (j=0; j<__m241; j+=__s240) {
// 6_2
int __m240 = j + __s240 > __m241 ? __m241 - j : __s240;
double *t38 = t28 + j*P_ncols;
double *t36 = t26 + j*P_ncols;
double *t37 = t27 + j*P_ncols;
for (k=0; k<__m240; k+=1) {
// 6_3
double *t49 = t38 + k*P_ncols;
double *t47 = t36 + k*P_ncols;
double *t48 = t37 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 6_4
t49[l] = (t47[l]+t48[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s240 = 512;

int __s238 = 512;

int __s237 = 2;

int nparts__s241 = 10;
int __s241;
if (nparts__s241 > 1 && P_ncols > nparts__s241) {
__s241 = P_ncols/nparts__s241;
// this will fail if P_ncols%nparts__s241+__s241 > nparts__s241
// which primarily effects small sizes
if (P_ncols%nparts__s241)
++__s241;
}
else {
__s241 = P_ncols;
nparts__s241 = 1;
}

int nparts__s239 = 10;
int __s239;
if (nparts__s239 > 1 && P_ncols > nparts__s239) {
__s239 = P_ncols/nparts__s239;
// this will fail if P_ncols%nparts__s239+__s239 > nparts__s239
// which primarily effects small sizes
if (P_ncols%nparts__s239)
++__s239;
}
else {
__s239 = P_ncols;
nparts__s239 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = t25;
double *t14 = t25;
double *t11 = t25;
double *t13 = t25;
double *t12 = t22;
double *t10 = t22;
double *t9 = t22;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s237) {
// 2_1
int __m237 = i + __s237 > P_ncols ? P_ncols - i : __s237;
double *t21 = t22 + i*P_ncols;
double *t20 = t8 + i*P_ncols;
for (j=0; j<__m237; j+=1) {
// 2_2
double *t31 = t21 + j*P_ncols;
double *t30 = t20 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t31[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t41 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t31[l] += (t30[k]*t41[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s239);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s239);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s239,ii+=1) {
// 4_1
int __m239 = i + __s239 > P_ncols ? P_ncols - i : __s239;
double *t24 = t25 + i*P_ncols;
double *t23 = t12 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t23 = t23;
predict_0[disp].t24 = t24;
predict_0[disp].__s238 = __s238;
predict_0[disp].__m239 = __m239;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s239; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s241);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s241);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s241,ii+=1) {
// 6_1
int __m241 = i + __s241 > P_ncols ? P_ncols - i : __s241;
double *t28 = P + i*P_ncols;
double *t26 = t17 + i*P_ncols;
double *t27 = Q + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t27 = t27;
predict_1[disp].t26 = t26;
predict_1[disp].t28 = t28;
predict_1[disp].__s240 = __s240;
predict_1[disp].__m241 = __m241;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s241; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t25);
free(t22);
}
