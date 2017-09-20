#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2501;
int P_ncols;
double *t18;
double *t17;
double *t8;
int __s2500;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2501 = msg->__m2501;
int P_ncols = msg->P_ncols;
double *t18 = msg->t18;
double *t17 = msg->t17;
double *t8 = msg->t8;
int __s2500 = msg->__s2500;

for (j=0; j<P_ncols; j+=__s2500) {
// 2_2
int __m2500 = j + __s2500 > P_ncols ? P_ncols - j : __s2500;
double *t27 = t8 + j;
double *t28 = t17 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t39 = t18 + k*P_ncols;
double *t38 = t27 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2501; ++__zr__) t39[__zr__] = 0.0;
for (l=0; l<__m2500; l+=1) {
// 2_4
double *t50 = t28 + l*P_ncols;
for (p=0; p<__m2501; p+=1) {
// 2_5
t39[p] += (t38[l]*t50[p]);
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

int __s2503 = 12;

int __s2502 = 2;

int __s2500 = 512;

int nparts__s2501 = 12;
int __s2501;
if (nparts__s2501 > 1 && P_ncols > nparts__s2501) {
__s2501 = P_ncols/nparts__s2501;
// this will fail if P_ncols%nparts__s2501+__s2501 > nparts__s2501
// which primarily effects small sizes
if (P_ncols%nparts__s2501)
++__s2501;
}
else {
__s2501 = P_ncols;
nparts__s2501 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t22;
double *t13 = t22;
double *t12 = t19;
double *t11 = t19;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2501);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2501);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2501,ii+=1) {
// 2_1
int __m2501 = i + __s2501 > P_ncols ? P_ncols - i : __s2501;
double *t18 = t19 + i;
double *t17 = P + i;
predict_0[disp].__m2501 = __m2501;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t18 = t18;
predict_0[disp].t17 = t17;
predict_0[disp].t8 = t8;
predict_0[disp].__s2500 = __s2500;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2501; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s2502) {
// 4_1
int __m2502 = i + __s2502 > P_ncols ? P_ncols - i : __s2502;
double *t21 = t22 + i*P_ncols;
double *t20 = t12 + i*P_ncols;
for (j=0; j<__m2502; j+=1) {
// 4_2
double *t32 = t21 + j*P_ncols;
double *t31 = t20 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t48 = A + k*P_ncols;
t32[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t32[k] += (t31[l]*t48[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s2503) {
// 6_1
int __m2503 = i + __s2503 > P_ncols ? P_ncols - i : __s2503;
double *t25 = P + i*P_ncols;
double *t23 = t14 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<__m2503; j+=1) {
// 6_2
double *t36 = t25 + j*P_ncols;
double *t34 = t23 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t36[k] = (t34[k]+t35[k]);
}
}
}
free(t22);
free(t19);
}
