#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t29;
int __m1666;
double *t10;
double *t23;
int __s1665;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
int __m1666 = msg->__m1666;
double *t10 = msg->t10;
double *t23 = msg->t23;
int __s1665 = msg->__s1665;

for (j=0; j<P_ncols; j+=__s1665) {
// 4_2
int __m1665 = j + __s1665 > P_ncols ? P_ncols - j : __s1665;
double *t34 = t23 + j*P_ncols;
double *t33 = t10 + j*P_ncols;
for (k=0; k<__m1665; k+=1) {
// 4_3
double *t45 = t34 + k*P_ncols;
double *t44 = t33 + k*P_ncols;
for (l=0; l<__m1666; l+=1) {
// 4_4
double *t57 = t29 + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t45[l] += (t44[p]*t57[p]);
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

int __s1667 = 2;

int __s1665 = 512;

int __s1664 = 2;

int nparts__s1666 = 12;
int __s1666;
if (nparts__s1666 > 1 && P_ncols > nparts__s1666) {
__s1666 = P_ncols/nparts__s1666;
// this will fail if P_ncols%nparts__s1666+__s1666 > nparts__s1666
// which primarily effects small sizes
if (P_ncols%nparts__s1666)
++__s1666;
}
else {
__s1666 = P_ncols;
nparts__s1666 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t24;
double *t11 = t24;
double *t13 = t24;
double *t10 = t21;
double *t8 = A;
double *t14 = A;
for (i=0; i<P_ncols; i+=__s1664) {
// 2_1
int __m1664 = i + __s1664 > P_ncols ? P_ncols - i : __s1664;
double *t18 = t8 + i;
double *t19 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t31 = t21 + j*P_ncols;
double *t30 = t18 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t31[__zr__] = 0.0;
for (k=0; k<__m1664; k+=1) {
// 2_3
double *t41 = t19 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t31[l] += (t30[k]*t41[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1666);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1666);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1666,ii+=1) {
// 4_1
int __m1666 = i + __s1666 > P_ncols ? P_ncols - i : __s1666;
double *t23 = t24 + i;
double *t29 = t14 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t29 = t29;
predict_0[disp].__m1666 = __m1666;
predict_0[disp].t10 = t10;
predict_0[disp].t23 = t23;
predict_0[disp].__s1665 = __s1665;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1666; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s1667) {
// 6_1
int __m1667 = i + __s1667 > P_ncols ? P_ncols - i : __s1667;
double *t27 = P + i;
double *t25 = t15 + i;
double *t26 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t38 = t27 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
double *t37 = t26 + j*P_ncols;
for (k=0; k<__m1667; k+=1) {
// 6_3
t38[k] = (t36[k]+t37[k]);
}
}
}
free(t24);
free(t21);
}
