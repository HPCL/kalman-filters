#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t18;
int __m3959;
double *P;
double *t19;
int __s3958;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t18 = msg->t18;
int __m3959 = msg->__m3959;
double *P = msg->P;
double *t19 = msg->t19;
int __s3958 = msg->__s3958;

for (j=0; j<P_ncols; j+=__s3958) {
// 2_2
int __m3958 = j + __s3958 > P_ncols ? P_ncols - j : __s3958;
double *t30 = t19 + j;
double *t29 = P + j;
for (k=0; k<__m3959; k+=1) {
// 2_3
double *t40 = t30 + k*P_ncols;
double *t39 = t18 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3958; ++__zr__) t40[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t51 = t29 + l*P_ncols;
for (p=0; p<__m3958; p+=1) {
// 2_5
t40[p] += (t39[l]*t51[p]);
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

int __s3961 = 10;

int __s3960 = 10;

int __s3958 = 504;

int nparts__s3959 = 10;
int __s3959;
if (nparts__s3959 > 1 && P_ncols > nparts__s3959) {
__s3959 = P_ncols/nparts__s3959;
// this will fail if P_ncols%nparts__s3959+__s3959 > nparts__s3959
// which primarily effects small sizes
if (P_ncols%nparts__s3959)
++__s3959;
}
else {
__s3959 = P_ncols;
nparts__s3959 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t23;
double *t13 = t23;
double *t9 = t20;
double *t11 = t20;
double *t10 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3959);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3959);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3959,ii+=1) {
// 2_1
int __m3959 = i + __s3959 > P_ncols ? P_ncols - i : __s3959;
double *t19 = t20 + i*P_ncols;
double *t18 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t18 = t18;
predict_0[disp].__m3959 = __m3959;
predict_0[disp].P = P;
predict_0[disp].t19 = t19;
predict_0[disp].__s3958 = __s3958;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3959; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s3960) {
// 4_1
int __m3960 = i + __s3960 > P_ncols ? P_ncols - i : __s3960;
double *t22 = t23 + i;
double *t28 = t14 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t33 = t22 + j*P_ncols;
double *t32 = t9 + j*P_ncols;
for (k=0; k<__m3960; k+=1) {
// 4_3
double *t49 = t28 + k*P_ncols;
t33[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t33[k] += (t32[l]*t49[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s3961) {
// 6_1
int __m3961 = i + __s3961 > P_ncols ? P_ncols - i : __s3961;
double *t26 = P + i;
double *t24 = t15 + i;
double *t25 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t37 = t26 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
for (k=0; k<__m3961; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t23);
free(t20);
}
