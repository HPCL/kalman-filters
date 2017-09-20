#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m310;
int xh_ncols;
double *t21;
int A2_ncols;
double *A2;
double *t22;
int xhn_nrows;
} predict1_1_msg_t;

typedef struct { 
int P_ncols;
double *t31;
double *t32;
int __m311;
double *A;
double *P;
double *t24;
int __s311;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t31 = msg->t31;
double *t32 = msg->t32;
int __m311 = msg->__m311;
double *A = msg->A;
double *P = msg->P;
double *t24 = msg->t24;
int __s311 = msg->__s311;

double *t28 = malloc(sizeof(double)*__s311*P_ncols);
double *t25 = malloc(sizeof(double)*__s311*P_ncols);
for (j=0; j<__m311; j+=1) {
// 5_2
double *t38 = t25 + j*P_ncols;
double *t37 = t24 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t38[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 5_3
double *t52 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 5_4
t38[l] += (t37[k]*t52[l]);
}
}
}
for (j=0; j<__m311; j+=1) {
// 7_2
double *t41 = t28 + j*P_ncols;
double *t40 = t25 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 7_3
double *t62 = A + k*P_ncols;
t41[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 7_4
t41[k] += (t40[l]*t62[l]);
}
}
}
for (j=0; j<__m311; j+=1) {
// 9_2
double *t45 = t32 + j*P_ncols;
double *t43 = t28 + j*P_ncols;
double *t44 = t31 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 9_3
t45[k] = (t43[k]+t44[k]);
}
}
free(t28);
free(t25);
return NULL;
}


void *predict1_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict1_1_msg_t *msg = (predict1_1_msg_t*)mesg;
int __m310 = msg->__m310;
int xh_ncols = msg->xh_ncols;
double *t21 = msg->t21;
int A2_ncols = msg->A2_ncols;
double *A2 = msg->A2;
double *t22 = msg->t22;
int xhn_nrows = msg->xhn_nrows;

for (j=0; j<xhn_nrows; j+=1) {
// 2_2
double *t35 = t22 + j*xh_ncols;
double *t34 = A2 + j*A2_ncols;
for (__zr__ = 0; __zr__ < __m310; ++__zr__) t35[__zr__] = 0.0;
for (k=0; k<A2_ncols; k+=1) {
// 2_3
double *t48 = t21 + k*xh_ncols;
for (l=0; l<__m310; l+=1) {
// 2_4
t35[l] += (t34[k]*t48[l]);
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int A2_nrows, int A2_ncols, double* A2, int Q_nrows, int Q_ncols, double* Q, int xh_nrows, int xh_ncols, double* xh, int P_nrows, int P_ncols, double* P, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii;

int nparts__s310 = 12;
int __s310;
if (nparts__s310 > 1 && xh_ncols > nparts__s310) {
__s310 = xh_ncols/nparts__s310;
// this will fail if xh_ncols%nparts__s310+__s310 > nparts__s310
// which primarily effects small sizes
if (xh_ncols%nparts__s310)
++__s310;
}
else {
__s310 = xh_ncols;
nparts__s310 = 1;
}

int nparts__s311 = 6;
int __s311;
if (nparts__s311 > 1 && P_ncols > nparts__s311) {
__s311 = P_ncols/nparts__s311;
// this will fail if P_ncols%nparts__s311+__s311 > nparts__s311
// which primarily effects small sizes
if (P_ncols%nparts__s311)
++__s311;
}
else {
__s311 = P_ncols;
nparts__s311 = 1;
}

double *t14 = A;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s311);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s311);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s311,ii+=1) {
// 5_1
int __m311 = i + __s311 > P_ncols ? P_ncols - i : __s311;
double *t32 = P + i*P_ncols;
double *t24 = t14 + i*P_ncols;
double *t31 = Q + i*P_ncols;
predict1_0[disp].P_ncols = P_ncols;
predict1_0[disp].t31 = t31;
predict1_0[disp].t32 = t32;
predict1_0[disp].__m311 = __m311;
predict1_0[disp].A = A;
predict1_0[disp].P = P;
predict1_0[disp].t24 = t24;
predict1_0[disp].__s311 = __s311;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s311; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
predict1_1_msg_t *predict1_1 = malloc(sizeof(predict1_1_msg_t)*nparts__s310);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s310);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s310,ii+=1) {
// 2_1
int __m310 = i + __s310 > xh_ncols ? xh_ncols - i : __s310;
double *t22 = xhn + i;
double *t21 = xh + i;
predict1_1[disp].__m310 = __m310;
predict1_1[disp].xh_ncols = xh_ncols;
predict1_1[disp].t21 = t21;
predict1_1[disp].A2_ncols = A2_ncols;
predict1_1[disp].A2 = A2;
predict1_1[disp].t22 = t22;
predict1_1[disp].xhn_nrows = xhn_nrows;

pthread_create(&threads_1[disp], NULL, predict1_body_1, (void *)(predict1_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s310; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict1_1);
}
