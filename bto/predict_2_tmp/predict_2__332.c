#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t30;
double *t16;
double *t15;
int __s908;
int __m909;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t30 = msg->t30;
double *t16 = msg->t16;
double *t15 = msg->t15;
int __s908 = msg->__s908;
int __m909 = msg->__m909;

for (j=0; j<__m909; j+=__s908) {
// 2_2
int __m908 = j + __s908 > __m909 ? __m909 - j : __s908;
double *t27 = t15 + j;
double *t28 = t16 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t39 = t30 + k*P_ncols;
double *t38 = t27 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t39[__zr__] = 0.0;
for (l=0; l<__m908; l+=1) {
// 2_4
double *t46 = t28 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t39[p] += (t38[l]*t46[p]);
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

int __s910 = 2;

int __s908 = 512;

int nparts__s909 = 10;
int __s909;
if (nparts__s909 > 1 && P_ncols > nparts__s909) {
__s909 = P_ncols/nparts__s909;
// this will fail if P_ncols%nparts__s909+__s909 > nparts__s909
// which primarily effects small sizes
if (P_ncols%nparts__s909)
++__s909;
}
else {
__s909 = P_ncols;
nparts__s909 = 1;
}

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*nparts__s909*P_ncols*P_ncols);
double *t13 = t21;
double *t56 = t18;
double *t10 = A;
double *t8 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s909);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s909);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s909,ii+=1) {
// 2_1
int __m909 = i + __s909 > P_ncols ? P_ncols - i : __s909;
double *t30 = t18 + ii*P_ncols*P_ncols;
double *t15 = t10 + i;
double *t16 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t30 = t30;
predict_0[disp].t16 = t16;
predict_0[disp].t15 = t15;
predict_0[disp].__s908 = __s908;
predict_0[disp].__m909 = __m909;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s909; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s909,ii+=1) {
// 2_1
int __m909 = i + __s909 > P_ncols ? P_ncols - i : __s909;
if ((ii == 0)) {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t56[__k*P_ncols+__l] = t18[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
} else {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t56[__k*P_ncols+__l] += t18[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s910) {
// 4_1
int __m910 = i + __s910 > P_ncols ? P_ncols - i : __s910;
double *t20 = t21 + i;
double *t26 = t14 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t32 = t20 + j*P_ncols;
double *t31 = t56 + j*P_ncols;
for (k=0; k<__m910; k+=1) {
// 4_3
double *t44 = t26 + k*P_ncols;
t32[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t32[k] += (t31[l]*t44[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t24 = P + i*P_ncols;
double *t22 = t13 + i*P_ncols;
double *t23 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t24[j] = (t22[j]+t23[j]);
}
}
free(t21);
free(t18);
}
