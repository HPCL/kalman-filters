#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t26;
double *t13;
double *t12;
int __s2528;
int __m2529;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t26 = msg->t26;
double *t13 = msg->t13;
double *t12 = msg->t12;
int __s2528 = msg->__s2528;
int __m2529 = msg->__m2529;

for (j=0; j<__m2529; j+=__s2528) {
// 2_2
int __m2528 = j + __s2528 > __m2529 ? __m2529 - j : __s2528;
double *t23 = t12 + j;
double *t24 = t13 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t36 = t26 + k*P_ncols;
double *t35 = t23 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t36[__zr__] = 0.0;
for (l=0; l<__m2528; l+=1) {
// 2_4
double *t43 = t24 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t36[p] += (t35[l]*t43[p]);
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

int __s2528 = 512;

int nparts__s2529 = 12;
int __s2529;
if (nparts__s2529 > 1 && P_ncols > nparts__s2529) {
__s2529 = P_ncols/nparts__s2529;
// this will fail if P_ncols%nparts__s2529+__s2529 > nparts__s2529
// which primarily effects small sizes
if (P_ncols%nparts__s2529)
++__s2529;
}
else {
__s2529 = P_ncols;
nparts__s2529 = 1;
}

double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = malloc(sizeof(double)*nparts__s2529*P_ncols*P_ncols);
double *t49 = t15;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2529);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2529);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2529,ii+=1) {
// 2_1
int __m2529 = i + __s2529 > P_ncols ? P_ncols - i : __s2529;
double *t26 = t15 + ii*P_ncols*P_ncols;
double *t12 = t10 + i;
double *t13 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t26 = t26;
predict_0[disp].t13 = t13;
predict_0[disp].t12 = t12;
predict_0[disp].__s2528 = __s2528;
predict_0[disp].__m2529 = __m2529;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2529; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2529,ii+=1) {
// 2_1
int __m2529 = i + __s2529 > P_ncols ? P_ncols - i : __s2529;
if ((ii == 0)) {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t49[__k*P_ncols+__l] = t15[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
} else {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t49[__k*P_ncols+__l] += t15[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
}
}
}

for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t17 = t18 + i*P_ncols;
double *t16 = t49 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t34 = A + j*P_ncols;
t17[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t17[j] += (t16[k]*t34[k]);
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t21 = P + i*P_ncols;
double *t19 = t18 + i*P_ncols;
double *t20 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t21[j] = (t19[j]+t20[j]);
}
}
free(t18);
free(t15);
}
