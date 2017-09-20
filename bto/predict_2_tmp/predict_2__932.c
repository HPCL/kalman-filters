#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t18;
double *t19;
int __s2365;
int __m2366;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t18 = msg->t18;
double *t19 = msg->t19;
int __s2365 = msg->__s2365;
int __m2366 = msg->__m2366;

for (j=0; j<__m2366; j+=__s2365) {
// 2_2
int __m2365 = j + __s2365 > __m2366 ? __m2366 - j : __s2365;
double *t30 = t19 + j;
double *t29 = t18 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t40 = t30 + k*P_ncols;
double *t39 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2365; ++__zr__) t40[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t51 = t29 + l*P_ncols;
for (p=0; p<__m2365; p+=1) {
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

int __s2368 = 12;

int __s2367 = 12;

int __s2365 = 512;

int nparts__s2366 = 12;
int __s2366;
if (nparts__s2366 > 1 && P_ncols > nparts__s2366) {
__s2366 = P_ncols/nparts__s2366;
// this will fail if P_ncols%nparts__s2366+__s2366 > nparts__s2366
// which primarily effects small sizes
if (P_ncols%nparts__s2366)
++__s2366;
}
else {
__s2366 = P_ncols;
nparts__s2366 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t23;
double *t13 = t23;
double *t14 = A;
double *t9 = t20;
double *t11 = t20;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2366);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2366);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2366,ii+=1) {
// 2_1
int __m2366 = i + __s2366 > P_ncols ? P_ncols - i : __s2366;
double *t19 = t20 + i;
double *t18 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t18 = t18;
predict_0[disp].t19 = t19;
predict_0[disp].__s2365 = __s2365;
predict_0[disp].__m2366 = __m2366;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2366; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s2367) {
// 4_1
int __m2367 = i + __s2367 > P_ncols ? P_ncols - i : __s2367;
double *t22 = t23 + i;
double *t28 = t14 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t33 = t22 + j*P_ncols;
double *t32 = t9 + j*P_ncols;
for (k=0; k<__m2367; k+=1) {
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
for (i=0; i<P_ncols; i+=__s2368) {
// 6_1
int __m2368 = i + __s2368 > P_ncols ? P_ncols - i : __s2368;
double *t26 = P + i*P_ncols;
double *t24 = t15 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<__m2368; j+=1) {
// 6_2
double *t37 = t26 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t23);
free(t20);
}
