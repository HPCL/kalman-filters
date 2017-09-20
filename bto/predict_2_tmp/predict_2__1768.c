#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m4129;
int P_ncols;
double *t19;
double *t27;
double *t21;
int __s4128;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m4129 = msg->__m4129;
int P_ncols = msg->P_ncols;
double *t19 = msg->t19;
double *t27 = msg->t27;
double *t21 = msg->t21;
int __s4128 = msg->__s4128;

for (j=0; j<P_ncols; j+=__s4128) {
// 4_2
int __m4128 = j + __s4128 > P_ncols ? P_ncols - j : __s4128;
double *t32 = t21 + j;
double *t38 = t27 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t44 = t32 + k*__m4128;
double *t43 = t19 + k*P_ncols;
for (l=0; l<__m4128; l+=1) {
// 4_4
double *t52 = t38 + l*P_ncols;
t44[l] = 0.0;
for (p=0; p<__m4129; p+=1) {
// 4_5
t44[l] += (t43[p]*t52[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s4128 = 488;

int __s4127 = 10;

int nparts__s4129 = 10;
int __s4129;
if (nparts__s4129 > 1 && P_ncols > nparts__s4129) {
__s4129 = P_ncols/nparts__s4129;
// this will fail if P_ncols%nparts__s4129+__s4129 > nparts__s4129
// which primarily effects small sizes
if (P_ncols%nparts__s4129)
++__s4129;
}
else {
__s4129 = P_ncols;
nparts__s4129 = 1;
}

double *t22 = malloc(sizeof(double)*nparts__s4129*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t22;
double *t57 = t22;
double *t15 = A;
double *t12 = A;
double *t13 = t18;
double *t9 = t18;
for (i=0; i<P_ncols; i+=__s4127) {
// 2_1
int __m4127 = i + __s4127 > P_ncols ? P_ncols - i : __s4127;
double *t17 = t18 + i;
double *t16 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t29 = t17 + j*P_ncols;
double *t28 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m4127; ++__zr__) t29[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t40 = t16 + k*P_ncols;
for (l=0; l<__m4127; l+=1) {
// 2_4
t29[l] += (t28[k]*t40[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4129);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4129);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4129,ii+=1) {
// 4_1
int __m4129 = i + __s4129 > P_ncols ? P_ncols - i : __s4129;
double *t21 = t22 + ii*P_ncols*P_ncols;
double *t19 = t13 + i;
double *t27 = t15 + i;
predict_0[disp].__m4129 = __m4129;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t19 = t19;
predict_0[disp].t27 = t27;
predict_0[disp].t21 = t21;
predict_0[disp].__s4128 = __s4128;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4129; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s4129,ii+=1) {
// 4_1
int __m4129 = i + __s4129 > P_ncols ? P_ncols - i : __s4129;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s4128) {
int __m4128 = __j + __s4128 > P_ncols ? P_ncols - __j : __s4128;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m4128; __l+=1) {
t57[__j+__k*P_ncols+__l] = t22[ii*P_ncols*P_ncols+__j+__k*__m4128+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s4128) {
int __m4128 = __j + __s4128 > P_ncols ? P_ncols - __j : __s4128;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m4128; __l+=1) {
t57[__j+__k*P_ncols+__l] += t22[ii*P_ncols*P_ncols+__j+__k*__m4128+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t25 = P + i*P_ncols;
double *t23 = t11 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t25[j] = (t23[j]+t24[j]);
}
}
free(t22);
free(t18);
}
