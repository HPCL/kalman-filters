#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t22;
double *t30;
double *t24;
int __s1506;
int __m1507;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t22 = msg->t22;
double *t30 = msg->t30;
double *t24 = msg->t24;
int __s1506 = msg->__s1506;
int __m1507 = msg->__m1507;

for (j=0; j<__m1507; j+=__s1506) {
// 4_2
int __m1506 = j + __s1506 > __m1507 ? __m1507 - j : __s1506;
double *t35 = t24 + j;
double *t41 = t30 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t47 = t35 + k*P_ncols;
double *t46 = t22 + k*P_ncols;
for (l=0; l<__m1506; l+=1) {
// 4_4
double *t59 = t41 + l*P_ncols;
t47[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t47[l] += (t46[p]*t59[p]);
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

int __s1508 = 10;

int __s1506 = 512;

int __s1505 = 2;

int nparts__s1507 = 12;
int __s1507;
if (nparts__s1507 > 1 && P_ncols > nparts__s1507) {
__s1507 = P_ncols/nparts__s1507;
// this will fail if P_ncols%nparts__s1507+__s1507 > nparts__s1507
// which primarily effects small sizes
if (P_ncols%nparts__s1507)
++__s1507;
}
else {
__s1507 = P_ncols;
nparts__s1507 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t25;
double *t11 = t25;
double *t14 = t25;
double *t8 = A;
double *t15 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s1505) {
// 2_1
int __m1505 = i + __s1505 > P_ncols ? P_ncols - i : __s1505;
double *t19 = t8 + i;
double *t20 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t32 = t22 + j*P_ncols;
double *t31 = t19 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t32[__zr__] = 0.0;
for (k=0; k<__m1505; k+=1) {
// 2_3
double *t43 = t20 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t32[l] += (t31[k]*t43[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1507);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1507);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1507,ii+=1) {
// 4_1
int __m1507 = i + __s1507 > P_ncols ? P_ncols - i : __s1507;
double *t24 = t25 + i;
double *t30 = t15 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t22 = t22;
predict_0[disp].t30 = t30;
predict_0[disp].t24 = t24;
predict_0[disp].__s1506 = __s1506;
predict_0[disp].__m1507 = __m1507;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1507; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s1508) {
// 6_1
int __m1508 = i + __s1508 > P_ncols ? P_ncols - i : __s1508;
double *t28 = P + i;
double *t26 = t16 + i;
double *t27 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t39 = t28 + j*P_ncols;
double *t37 = t26 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
for (k=0; k<__m1508; k+=1) {
// 6_3
t39[k] = (t37[k]+t38[k]);
}
}
}
free(t25);
free(t22);
}
