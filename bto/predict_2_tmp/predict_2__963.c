#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t26;
int __m2469;
double *t10;
double *t20;
int __s2468;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t26 = msg->t26;
int __m2469 = msg->__m2469;
double *t10 = msg->t10;
double *t20 = msg->t20;
int __s2468 = msg->__s2468;

for (j=0; j<P_ncols; j+=__s2468) {
// 4_2
int __m2468 = j + __s2468 > P_ncols ? P_ncols - j : __s2468;
double *t31 = t20 + j*P_ncols;
double *t30 = t10 + j*P_ncols;
for (k=0; k<__m2468; k+=1) {
// 4_3
double *t42 = t31 + k*P_ncols;
double *t41 = t30 + k*P_ncols;
for (l=0; l<__m2469; l+=1) {
// 4_4
double *t50 = t26 + l*P_ncols;
t42[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t42[l] += (t41[p]*t50[p]);
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

int __s2468 = 504;

int __s2467 = 2;

int nparts__s2469 = 12;
int __s2469;
if (nparts__s2469 > 1 && P_ncols > nparts__s2469) {
__s2469 = P_ncols/nparts__s2469;
// this will fail if P_ncols%nparts__s2469+__s2469 > nparts__s2469
// which primarily effects small sizes
if (P_ncols%nparts__s2469)
++__s2469;
}
else {
__s2469 = P_ncols;
nparts__s2469 = 1;
}

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t21;
double *t13 = t21;
double *t10 = t18;
double *t8 = A;
double *t14 = A;
for (i=0; i<P_ncols; i+=__s2467) {
// 2_1
int __m2467 = i + __s2467 > P_ncols ? P_ncols - i : __s2467;
double *t15 = t8 + i;
double *t16 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t28 = t18 + j*P_ncols;
double *t27 = t15 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t28[__zr__] = 0.0;
for (k=0; k<__m2467; k+=1) {
// 2_3
double *t38 = t16 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t28[l] += (t27[k]*t38[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2469);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2469);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2469,ii+=1) {
// 4_1
int __m2469 = i + __s2469 > P_ncols ? P_ncols - i : __s2469;
double *t20 = t21 + i;
double *t26 = t14 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t26 = t26;
predict_0[disp].__m2469 = __m2469;
predict_0[disp].t10 = t10;
predict_0[disp].t20 = t20;
predict_0[disp].__s2468 = __s2468;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2469; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t24 = P + i*P_ncols;
double *t22 = t11 + i*P_ncols;
double *t23 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t24[j] = (t22[j]+t23[j]);
}
}
free(t21);
free(t18);
}
