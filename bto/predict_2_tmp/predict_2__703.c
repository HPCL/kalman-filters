#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t35;
double *t28;
double *t20;
int __s1644;
int __m1645;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t35 = msg->t35;
double *t28 = msg->t28;
double *t20 = msg->t20;
int __s1644 = msg->__s1644;
int __m1645 = msg->__m1645;

for (j=0; j<__m1645; j+=__s1644) {
// 4_2
int __m1644 = j + __s1644 > __m1645 ? __m1645 - j : __s1644;
double *t32 = t20 + j;
double *t40 = t28 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t46 = t35 + k*P_ncols;
double *t45 = t32 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t54 = t40 + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<__m1644; p+=1) {
// 4_5
t46[l] += (t45[p]*t54[p]);
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

int __s1644 = 512;

int __s1643 = 2;

int nparts__s1645 = 12;
int __s1645;
if (nparts__s1645 > 1 && P_ncols > nparts__s1645) {
__s1645 = P_ncols/nparts__s1645;
// this will fail if P_ncols%nparts__s1645+__s1645 > nparts__s1645
// which primarily effects small sizes
if (P_ncols%nparts__s1645)
++__s1645;
}
else {
__s1645 = P_ncols;
nparts__s1645 = 1;
}

double *t23 = malloc(sizeof(double)*nparts__s1645*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t59 = t23;
double *t13 = t19;
double *t10 = t19;
double *t8 = A;
double *t15 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s1643) {
// 2_1
int __m1643 = i + __s1643 > P_ncols ? P_ncols - i : __s1643;
double *t16 = t8 + i;
double *t17 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t30 = t19 + j*P_ncols;
double *t29 = t16 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t30[__zr__] = 0.0;
for (k=0; k<__m1643; k+=1) {
// 2_3
double *t42 = t17 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t30[l] += (t29[k]*t42[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1645);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1645);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1645,ii+=1) {
// 4_1
int __m1645 = i + __s1645 > P_ncols ? P_ncols - i : __s1645;
double *t35 = t23 + ii*P_ncols*P_ncols;
double *t20 = t13 + i;
double *t28 = t15 + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t35 = t35;
predict_0[disp].t28 = t28;
predict_0[disp].t20 = t20;
predict_0[disp].__s1644 = __s1644;
predict_0[disp].__m1645 = __m1645;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1645; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1645,ii+=1) {
// 4_1
int __m1645 = i + __s1645 > P_ncols ? P_ncols - i : __s1645;
if ((ii == 0)) {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t59[__k*P_ncols+__l] = t23[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
} else {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t59[__k*P_ncols+__l] += t23[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
}
}
}

for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t26 = P + i*P_ncols;
double *t24 = t59 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t26[j] = (t24[j]+t25[j]);
}
}
free(t23);
free(t19);
}
