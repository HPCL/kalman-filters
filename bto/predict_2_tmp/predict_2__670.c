#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m1581;
double *t24;
double *t30;
double *t10;
int __s1580;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m1581 = msg->__m1581;
double *t24 = msg->t24;
double *t30 = msg->t30;
double *t10 = msg->t10;
int __s1580 = msg->__s1580;

for (j=0; j<P_ncols; j+=__s1580) {
// 4_2
int __m1580 = j + __s1580 > P_ncols ? P_ncols - j : __s1580;
double *t34 = t10 + j;
double *t42 = t30 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t48 = t24 + k*P_ncols;
double *t47 = t34 + k*P_ncols;
for (l=0; l<__m1581; l+=1) {
// 4_4
double *t60 = t42 + l*P_ncols;
t48[l] = 0.0;
for (p=0; p<__m1580; p+=1) {
// 4_5
t48[l] += (t47[p]*t60[p]);
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

int __s1582 = 2;

int __s1580 = 512;

int __s1579 = 2;

int nparts__s1581 = 12;
int __s1581;
if (nparts__s1581 > 1 && P_ncols > nparts__s1581) {
__s1581 = P_ncols/nparts__s1581;
// this will fail if P_ncols%nparts__s1581+__s1581 > nparts__s1581
// which primarily effects small sizes
if (P_ncols%nparts__s1581)
++__s1581;
}
else {
__s1581 = P_ncols;
nparts__s1581 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t25;
double *t14 = t25;
double *t10 = t22;
double *t8 = A;
double *t15 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s1579) {
// 2_1
int __m1579 = i + __s1579 > P_ncols ? P_ncols - i : __s1579;
double *t19 = t8 + i;
double *t20 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t32 = t22 + j*P_ncols;
double *t31 = t19 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t32[__zr__] = 0.0;
for (k=0; k<__m1579; k+=1) {
// 2_3
double *t44 = t20 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t32[l] += (t31[k]*t44[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1581);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1581);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1581,ii+=1) {
// 4_1
int __m1581 = i + __s1581 > P_ncols ? P_ncols - i : __s1581;
double *t24 = t25 + i;
double *t30 = t15 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m1581 = __m1581;
predict_0[disp].t24 = t24;
predict_0[disp].t30 = t30;
predict_0[disp].t10 = t10;
predict_0[disp].__s1580 = __s1580;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1581; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s1582) {
// 6_1
int __m1582 = i + __s1582 > P_ncols ? P_ncols - i : __s1582;
double *t28 = P + i;
double *t26 = t16 + i;
double *t27 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t40 = t28 + j*P_ncols;
double *t38 = t26 + j*P_ncols;
double *t39 = t27 + j*P_ncols;
for (k=0; k<__m1582; k+=1) {
// 6_3
t40[k] = (t38[k]+t39[k]);
}
}
}
free(t25);
free(t22);
}
