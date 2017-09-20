#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t25;
int __m1604;
double *t10;
double *t19;
int __s1603;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t25 = msg->t25;
int __m1604 = msg->__m1604;
double *t10 = msg->t10;
double *t19 = msg->t19;
int __s1603 = msg->__s1603;

for (j=0; j<P_ncols; j+=__s1603) {
// 4_2
int __m1603 = j + __s1603 > P_ncols ? P_ncols - j : __s1603;
double *t30 = t19 + j*P_ncols;
double *t29 = t10 + j*P_ncols;
for (k=0; k<__m1603; k+=1) {
// 4_3
double *t41 = t30 + k*P_ncols;
double *t40 = t29 + k*P_ncols;
for (l=0; l<__m1604; l+=1) {
// 4_4
double *t49 = t25 + l*P_ncols;
t41[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t41[l] += (t40[p]*t49[p]);
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

int __s1603 = 512;

int __s1602 = 2;

int nparts__s1604 = 12;
int __s1604;
if (nparts__s1604 > 1 && P_ncols > nparts__s1604) {
__s1604 = P_ncols/nparts__s1604;
// this will fail if P_ncols%nparts__s1604+__s1604 > nparts__s1604
// which primarily effects small sizes
if (P_ncols%nparts__s1604)
++__s1604;
}
else {
__s1604 = P_ncols;
nparts__s1604 = 1;
}

double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t20;
double *t13 = t20;
double *t10 = t17;
double *t9 = t17;
double *t8 = A;
double *t14 = A;
for (i=0; i<P_ncols; i+=__s1602) {
// 2_1
int __m1602 = i + __s1602 > P_ncols ? P_ncols - i : __s1602;
double *t16 = t17 + i*P_ncols;
double *t15 = t8 + i*P_ncols;
for (j=0; j<__m1602; j+=1) {
// 2_2
double *t27 = t16 + j*P_ncols;
double *t26 = t15 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t27[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t37 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t27[l] += (t26[k]*t37[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1604);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1604);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1604,ii+=1) {
// 4_1
int __m1604 = i + __s1604 > P_ncols ? P_ncols - i : __s1604;
double *t19 = t20 + i;
double *t25 = t14 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t25 = t25;
predict_0[disp].__m1604 = __m1604;
predict_0[disp].t10 = t10;
predict_0[disp].t19 = t19;
predict_0[disp].__s1603 = __s1603;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1604; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t23 = P + i*P_ncols;
double *t21 = t11 + i*P_ncols;
double *t22 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t23[j] = (t21[j]+t22[j]);
}
}
free(t20);
free(t17);
}
