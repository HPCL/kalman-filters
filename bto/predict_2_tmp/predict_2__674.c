#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m1591;
double *t21;
double *t27;
double *t10;
int __s1590;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m1591 = msg->__m1591;
double *t21 = msg->t21;
double *t27 = msg->t27;
double *t10 = msg->t10;
int __s1590 = msg->__s1590;

for (j=0; j<P_ncols; j+=__s1590) {
// 4_2
int __m1590 = j + __s1590 > P_ncols ? P_ncols - j : __s1590;
double *t31 = t10 + j;
double *t39 = t27 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t45 = t21 + k*P_ncols;
double *t44 = t31 + k*P_ncols;
for (l=0; l<__m1591; l+=1) {
// 4_4
double *t53 = t39 + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<__m1590; p+=1) {
// 4_5
t45[l] += (t44[p]*t53[p]);
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

int __s1590 = 512;

int __s1589 = 2;

int nparts__s1591 = 12;
int __s1591;
if (nparts__s1591 > 1 && P_ncols > nparts__s1591) {
__s1591 = P_ncols/nparts__s1591;
// this will fail if P_ncols%nparts__s1591+__s1591 > nparts__s1591
// which primarily effects small sizes
if (P_ncols%nparts__s1591)
++__s1591;
}
else {
__s1591 = P_ncols;
nparts__s1591 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t22;
double *t10 = t19;
double *t8 = A;
double *t15 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s1589) {
// 2_1
int __m1589 = i + __s1589 > P_ncols ? P_ncols - i : __s1589;
double *t16 = t8 + i;
double *t17 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t29 = t19 + j*P_ncols;
double *t28 = t16 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t29[__zr__] = 0.0;
for (k=0; k<__m1589; k+=1) {
// 2_3
double *t41 = t17 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t29[l] += (t28[k]*t41[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1591);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1591);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1591,ii+=1) {
// 4_1
int __m1591 = i + __s1591 > P_ncols ? P_ncols - i : __s1591;
double *t21 = t22 + i;
double *t27 = t15 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m1591 = __m1591;
predict_0[disp].t21 = t21;
predict_0[disp].t27 = t27;
predict_0[disp].t10 = t10;
predict_0[disp].__s1590 = __s1590;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1591; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t25 = P + i*P_ncols;
double *t23 = t14 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t25[j] = (t23[j]+t24[j]);
}
}
free(t22);
free(t19);
}
