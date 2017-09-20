#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t19;
int __m3705;
double *P;
double *t18;
int __s3704;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t19 = msg->t19;
int __m3705 = msg->__m3705;
double *P = msg->P;
double *t18 = msg->t18;
int __s3704 = msg->__s3704;

for (j=0; j<P_ncols; j+=__s3704) {
// 2_2
int __m3704 = j + __s3704 > P_ncols ? P_ncols - j : __s3704;
double *t29 = t18 + j;
double *t30 = P + j*P_ncols;
for (k=0; k<__m3705; k+=1) {
// 2_3
double *t41 = t19 + k*P_ncols;
double *t40 = t29 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t41[__zr__] = 0.0;
for (l=0; l<__m3704; l+=1) {
// 2_4
double *t52 = t30 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t41[p] += (t40[l]*t52[p]);
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

int __s3706 = 10;

int __s3704 = 512;

int nparts__s3705 = 10;
int __s3705;
if (nparts__s3705 > 1 && P_ncols > nparts__s3705) {
__s3705 = P_ncols/nparts__s3705;
// this will fail if P_ncols%nparts__s3705+__s3705 > nparts__s3705
// which primarily effects small sizes
if (P_ncols%nparts__s3705)
++__s3705;
}
else {
__s3705 = P_ncols;
nparts__s3705 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*__s3706);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t20;
double *t10 = A;
double *t8 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3705);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3705);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3705,ii+=1) {
// 2_1
int __m3705 = i + __s3705 > P_ncols ? P_ncols - i : __s3705;
double *t19 = t20 + i*P_ncols;
double *t18 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t19 = t19;
predict_0[disp].__m3705 = __m3705;
predict_0[disp].P = P;
predict_0[disp].t18 = t18;
predict_0[disp].__s3704 = __s3704;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3705; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s3706) {
// 4_1
int __m3706 = i + __s3706 > P_ncols ? P_ncols - i : __s3706;
double *t26 = P + i;
double *t28 = t14 + i*P_ncols;
double *t25 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t34 = t22 + j*__m3706;
double *t33 = t11 + j*P_ncols;
for (k=0; k<__m3706; k+=1) {
// 4_3
double *t50 = t28 + k*P_ncols;
t34[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t34[k] += (t33[l]*t50[l]);
}
}
}
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t38 = t26 + j*P_ncols;
double *t36 = t22 + j*__m3706;
double *t37 = t25 + j*P_ncols;
for (k=0; k<__m3706; k+=1) {
// 6_3
t38[k] = (t36[k]+t37[k]);
}
}
}
free(t22);
free(t20);
}
