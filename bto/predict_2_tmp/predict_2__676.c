#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t23;
int __m1593;
double *t8;
double *t17;
int __s1592;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t23 = msg->t23;
int __m1593 = msg->__m1593;
double *t8 = msg->t8;
double *t17 = msg->t17;
int __s1592 = msg->__s1592;

for (j=0; j<P_ncols; j+=__s1592) {
// 4_2
int __m1592 = j + __s1592 > P_ncols ? P_ncols - j : __s1592;
double *t29 = t17 + j*P_ncols;
double *t28 = t8 + j*P_ncols;
for (k=0; k<__m1592; k+=1) {
// 4_3
double *t39 = t29 + k*P_ncols;
double *t38 = t28 + k*P_ncols;
for (l=0; l<__m1593; l+=1) {
// 4_4
double *t44 = t23 + l*P_ncols;
t39[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t39[l] += (t38[p]*t44[p]);
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

int __s1592 = 512;

int nparts__s1593 = 12;
int __s1593;
if (nparts__s1593 > 1 && P_ncols > nparts__s1593) {
__s1593 = P_ncols/nparts__s1593;
// this will fail if P_ncols%nparts__s1593+__s1593 > nparts__s1593
// which primarily effects small sizes
if (P_ncols%nparts__s1593)
++__s1593;
}
else {
__s1593 = P_ncols;
nparts__s1593 = 1;
}

double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t18;
double *t11 = t18;
double *t12 = A;
double *t8 = t15;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t14 = t15 + i*P_ncols;
double *t13 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t14[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t25 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t14[k] += (t13[j]*t25[k]);
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1593);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1593);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1593,ii+=1) {
// 4_1
int __m1593 = i + __s1593 > P_ncols ? P_ncols - i : __s1593;
double *t17 = t18 + i;
double *t23 = t12 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t23 = t23;
predict_0[disp].__m1593 = __m1593;
predict_0[disp].t8 = t8;
predict_0[disp].t17 = t17;
predict_0[disp].__s1592 = __s1592;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1593; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t21 = P + i*P_ncols;
double *t19 = t9 + i*P_ncols;
double *t20 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t21[j] = (t19[j]+t20[j]);
}
}
free(t18);
free(t15);
}
