#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t31;
int __m1808;
double *t12;
double *t25;
int __s1807;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t21;
int __m1806;
double *t20;
double *t22;
int __s1805;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
int __m1806 = msg->__m1806;
double *t20 = msg->t20;
double *t22 = msg->t22;
int __s1805 = msg->__s1805;

for (j=0; j<P_ncols; j+=__s1805) {
// 2_2
int __m1805 = j + __s1805 > P_ncols ? P_ncols - j : __s1805;
double *t33 = t22 + j*P_ncols;
double *t32 = t20 + j*P_ncols;
for (k=0; k<__m1805; k+=1) {
// 2_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<__m1806; l+=1) {
// 2_4
double *t53 = t21 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t43[p] += (t42[l]*t53[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t31 = msg->t31;
int __m1808 = msg->__m1808;
double *t12 = msg->t12;
double *t25 = msg->t25;
int __s1807 = msg->__s1807;

for (j=0; j<P_ncols; j+=__s1807) {
// 4_2
int __m1807 = j + __s1807 > P_ncols ? P_ncols - j : __s1807;
double *t36 = t25 + j*P_ncols;
double *t35 = t12 + j*P_ncols;
for (k=0; k<__m1807; k+=1) {
// 4_3
double *t46 = t36 + k*P_ncols;
double *t45 = t35 + k*P_ncols;
for (l=0; l<__m1808; l+=1) {
// 4_4
double *t59 = t31 + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t46[l] += (t45[p]*t59[p]);
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

int __s1809 = 12;

int __s1807 = 512;

int __s1805 = 512;

int nparts__s1806 = 12;
int __s1806;
if (nparts__s1806 > 1 && P_ncols > nparts__s1806) {
__s1806 = P_ncols/nparts__s1806;
// this will fail if P_ncols%nparts__s1806+__s1806 > nparts__s1806
// which primarily effects small sizes
if (P_ncols%nparts__s1806)
++__s1806;
}
else {
__s1806 = P_ncols;
nparts__s1806 = 1;
}

int nparts__s1808 = 10;
int __s1808;
if (nparts__s1808 > 1 && P_ncols > nparts__s1808) {
__s1808 = P_ncols/nparts__s1808;
// this will fail if P_ncols%nparts__s1808+__s1808 > nparts__s1808
// which primarily effects small sizes
if (P_ncols%nparts__s1808)
++__s1808;
}
else {
__s1808 = P_ncols;
nparts__s1808 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*nparts__s1806*P_ncols*P_ncols);
double *t17 = t26;
double *t13 = t26;
double *t15 = t26;
double *t12 = t23;
double *t9 = t23;
double *t67 = t23;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1806);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1806);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1806,ii+=1) {
// 2_1
int __m1806 = i + __s1806 > P_ncols ? P_ncols - i : __s1806;
double *t22 = t23 + ii*P_ncols*P_ncols;
double *t20 = t10 + i;
double *t21 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].__m1806 = __m1806;
predict_0[disp].t20 = t20;
predict_0[disp].t22 = t22;
predict_0[disp].__s1805 = __s1805;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1806; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1806,ii+=1) {
// 2_1
int __m1806 = i + __s1806 > P_ncols ? P_ncols - i : __s1806;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1805) {
int __m1805 = __j + __s1805 > P_ncols ? P_ncols - __j : __s1805;
for (__k = 0; __k < __m1805; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t67[__j*P_ncols+__k*P_ncols+__l] = t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1805) {
int __m1805 = __j + __s1805 > P_ncols ? P_ncols - __j : __s1805;
for (__k = 0; __k < __m1805; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t67[__j*P_ncols+__k*P_ncols+__l] += t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1808);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1808);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1808,ii+=1) {
// 4_1
int __m1808 = i + __s1808 > P_ncols ? P_ncols - i : __s1808;
double *t25 = t26 + i;
double *t31 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t31 = t31;
predict_1[disp].__m1808 = __m1808;
predict_1[disp].t12 = t12;
predict_1[disp].t25 = t25;
predict_1[disp].__s1807 = __s1807;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1808; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s1809) {
// 6_1
int __m1809 = i + __s1809 > P_ncols ? P_ncols - i : __s1809;
double *t29 = P + i*P_ncols;
double *t27 = t17 + i*P_ncols;
double *t28 = Q + i*P_ncols;
for (j=0; j<__m1809; j+=1) {
// 6_2
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t40[k] = (t38[k]+t39[k]);
}
}
}
free(t26);
free(t23);
}
