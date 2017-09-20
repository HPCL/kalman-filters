#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t15;
double *t16;
int __s2580;
int __m2581;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t15 = msg->t15;
double *t16 = msg->t16;
int __s2580 = msg->__s2580;
int __m2581 = msg->__m2581;

for (j=0; j<__m2581; j+=__s2580) {
// 2_2
int __m2580 = j + __s2580 > __m2581 ? __m2581 - j : __s2580;
double *t26 = t16 + j;
double *t25 = t15 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t37 = t26 + k*P_ncols;
double *t36 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2580; ++__zr__) t37[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t48 = t25 + l*P_ncols;
for (p=0; p<__m2580; p+=1) {
// 2_5
t37[p] += (t36[l]*t48[p]);
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

int __s2582 = 12;

int __s2580 = 512;

int nparts__s2581 = 12;
int __s2581;
if (nparts__s2581 > 1 && P_ncols > nparts__s2581) {
__s2581 = P_ncols/nparts__s2581;
// this will fail if P_ncols%nparts__s2581+__s2581 > nparts__s2581
// which primarily effects small sizes
if (P_ncols%nparts__s2581)
++__s2581;
}
else {
__s2581 = P_ncols;
nparts__s2581 = 1;
}

double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t12 = t20;
double *t9 = t17;
double *t11 = t17;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2581);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2581);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2581,ii+=1) {
// 2_1
int __m2581 = i + __s2581 > P_ncols ? P_ncols - i : __s2581;
double *t16 = t17 + i;
double *t15 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t15 = t15;
predict_0[disp].t16 = t16;
predict_0[disp].__s2580 = __s2580;
predict_0[disp].__m2581 = __m2581;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2581; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t19 = t20 + i*P_ncols;
double *t18 = t9 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t35 = A + j*P_ncols;
t19[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t19[j] += (t18[k]*t35[k]);
}
}
}
for (i=0; i<P_ncols; i+=__s2582) {
// 6_1
int __m2582 = i + __s2582 > P_ncols ? P_ncols - i : __s2582;
double *t23 = P + i*P_ncols;
double *t21 = t12 + i*P_ncols;
double *t22 = Q + i*P_ncols;
for (j=0; j<__m2582; j+=1) {
// 6_2
double *t33 = t23 + j*P_ncols;
double *t31 = t21 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t33[k] = (t31[k]+t32[k]);
}
}
}
free(t20);
free(t17);
}
