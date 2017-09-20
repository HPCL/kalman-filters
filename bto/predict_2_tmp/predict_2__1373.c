#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t12;
double *t13;
int __s3324;
int __m3325;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t12 = msg->t12;
double *t13 = msg->t13;
int __s3324 = msg->__s3324;
int __m3325 = msg->__m3325;

for (j=0; j<__m3325; j+=__s3324) {
// 2_2
int __m3324 = j + __s3324 > __m3325 ? __m3325 - j : __s3324;
double *t23 = t13 + j;
double *t22 = t12 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t34 = t23 + k*P_ncols;
double *t33 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3324; ++__zr__) t34[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t41 = t22 + l*P_ncols;
for (p=0; p<__m3324; p+=1) {
// 2_5
t34[p] += (t33[l]*t41[p]);
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

int __s3324 = 512;

int nparts__s3325 = 12;
int __s3325;
if (nparts__s3325 > 1 && P_ncols > nparts__s3325) {
__s3325 = P_ncols/nparts__s3325;
// this will fail if P_ncols%nparts__s3325+__s3325 > nparts__s3325
// which primarily effects small sizes
if (P_ncols%nparts__s3325)
++__s3325;
}
else {
__s3325 = P_ncols;
nparts__s3325 = 1;
}

double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t14;
double *t11 = t14;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3325);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3325);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3325,ii+=1) {
// 2_1
int __m3325 = i + __s3325 > P_ncols ? P_ncols - i : __s3325;
double *t13 = t14 + i;
double *t12 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t12 = t12;
predict_0[disp].t13 = t13;
predict_0[disp].__s3324 = __s3324;
predict_0[disp].__m3325 = __m3325;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3325; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t16 = t17 + i*P_ncols;
double *t15 = t9 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t32 = A + j*P_ncols;
t16[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t16[j] += (t15[k]*t32[k]);
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t20 = P + i*P_ncols;
double *t18 = t17 + i*P_ncols;
double *t19 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t20[j] = (t18[j]+t19[j]);
}
}
free(t17);
free(t14);
}
