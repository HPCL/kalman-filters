#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m1957;
int P_ncols;
double *t29;
double *t21;
double *t23;
int __s1956;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m1957 = msg->__m1957;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t21 = msg->t21;
double *t23 = msg->t23;
int __s1956 = msg->__s1956;

for (j=0; j<P_ncols; j+=__s1956) {
// 4_2
int __m1956 = j + __s1956 > P_ncols ? P_ncols - j : __s1956;
double *t34 = t23 + j*P_ncols;
double *t33 = t21 + j*P_ncols;
for (k=0; k<__m1956; k+=1) {
// 4_3
double *t45 = t34 + k*P_ncols;
double *t44 = t33 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t57 = t29 + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<__m1957; p+=1) {
// 4_5
t45[l] += (t44[p]*t57[p]);
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

int __s1958 = 12;

int __s1956 = 512;

int __s1955 = 12;

int nparts__s1957 = 10;
int __s1957;
if (nparts__s1957 > 1 && P_ncols > nparts__s1957) {
__s1957 = P_ncols/nparts__s1957;
// this will fail if P_ncols%nparts__s1957+__s1957 > nparts__s1957
// which primarily effects small sizes
if (P_ncols%nparts__s1957)
++__s1957;
}
else {
__s1957 = P_ncols;
nparts__s1957 = 1;
}

double *t24 = malloc(sizeof(double)*nparts__s1957*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t24;
double *t11 = t24;
double *t62 = t24;
double *t14 = A;
double *t12 = t20;
double *t10 = t20;
double *t9 = t20;
for (i=0; i<P_ncols; i+=__s1955) {
// 2_1
int __m1955 = i + __s1955 > P_ncols ? P_ncols - i : __s1955;
double *t19 = t20 + i;
double *t18 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t31 = t19 + j*P_ncols;
double *t30 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m1955; ++__zr__) t31[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t41 = t18 + k*P_ncols;
for (l=0; l<__m1955; l+=1) {
// 2_4
t31[l] += (t30[k]*t41[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1957);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1957);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1957,ii+=1) {
// 4_1
int __m1957 = i + __s1957 > P_ncols ? P_ncols - i : __s1957;
double *t23 = t24 + ii*P_ncols*P_ncols;
double *t21 = t12 + i;
double *t29 = t14 + i;
predict_0[disp].__m1957 = __m1957;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t29 = t29;
predict_0[disp].t21 = t21;
predict_0[disp].t23 = t23;
predict_0[disp].__s1956 = __s1956;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1957; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1957,ii+=1) {
// 4_1
int __m1957 = i + __s1957 > P_ncols ? P_ncols - i : __s1957;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1956) {
int __m1956 = __j + __s1956 > P_ncols ? P_ncols - __j : __s1956;
for (__k = 0; __k < __m1956; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t62[__j*P_ncols+__k*P_ncols+__l] = t24[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1956) {
int __m1956 = __j + __s1956 > P_ncols ? P_ncols - __j : __s1956;
for (__k = 0; __k < __m1956; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t62[__j*P_ncols+__k*P_ncols+__l] += t24[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s1958) {
// 6_1
int __m1958 = i + __s1958 > P_ncols ? P_ncols - i : __s1958;
double *t27 = P + i*P_ncols;
double *t25 = t15 + i*P_ncols;
double *t26 = Q + i*P_ncols;
for (j=0; j<__m1958; j+=1) {
// 6_2
double *t38 = t27 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
double *t37 = t26 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t38[k] = (t36[k]+t37[k]);
}
}
}
free(t24);
free(t20);
}
