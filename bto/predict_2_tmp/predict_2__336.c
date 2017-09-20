#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t31;
int __m916;
double *t12;
double *t25;
int __s915;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t21;
int __m914;
double *t20;
double *t22;
int __s913;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
int __m914 = msg->__m914;
double *t20 = msg->t20;
double *t22 = msg->t22;
int __s913 = msg->__s913;

for (j=0; j<P_ncols; j+=__s913) {
// 2_2
int __m913 = j + __s913 > P_ncols ? P_ncols - j : __s913;
double *t33 = t22 + j*P_ncols;
double *t32 = t20 + j*P_ncols;
for (k=0; k<__m913; k+=1) {
// 2_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<__m914; l+=1) {
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
int __m916 = msg->__m916;
double *t12 = msg->t12;
double *t25 = msg->t25;
int __s915 = msg->__s915;

for (j=0; j<P_ncols; j+=__s915) {
// 4_2
int __m915 = j + __s915 > P_ncols ? P_ncols - j : __s915;
double *t36 = t25 + j*P_ncols;
double *t35 = t12 + j*P_ncols;
for (k=0; k<__m915; k+=1) {
// 4_3
double *t46 = t36 + k*P_ncols;
double *t45 = t35 + k*P_ncols;
for (l=0; l<__m916; l+=1) {
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

int __s917 = 12;

int __s915 = 512;

int __s913 = 512;

int nparts__s914 = 12;
int __s914;
if (nparts__s914 > 1 && P_ncols > nparts__s914) {
__s914 = P_ncols/nparts__s914;
// this will fail if P_ncols%nparts__s914+__s914 > nparts__s914
// which primarily effects small sizes
if (P_ncols%nparts__s914)
++__s914;
}
else {
__s914 = P_ncols;
nparts__s914 = 1;
}

int nparts__s916 = 12;
int __s916;
if (nparts__s916 > 1 && P_ncols > nparts__s916) {
__s916 = P_ncols/nparts__s916;
// this will fail if P_ncols%nparts__s916+__s916 > nparts__s916
// which primarily effects small sizes
if (P_ncols%nparts__s916)
++__s916;
}
else {
__s916 = P_ncols;
nparts__s916 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*nparts__s914*P_ncols*P_ncols);
double *t17 = t26;
double *t13 = t26;
double *t15 = t26;
double *t12 = t23;
double *t9 = t23;
double *t67 = t23;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s914);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s914);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s914,ii+=1) {
// 2_1
int __m914 = i + __s914 > P_ncols ? P_ncols - i : __s914;
double *t22 = t23 + ii*P_ncols*P_ncols;
double *t20 = t10 + i;
double *t21 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].__m914 = __m914;
predict_0[disp].t20 = t20;
predict_0[disp].t22 = t22;
predict_0[disp].__s913 = __s913;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s914; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s914,ii+=1) {
// 2_1
int __m914 = i + __s914 > P_ncols ? P_ncols - i : __s914;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s913) {
int __m913 = __j + __s913 > P_ncols ? P_ncols - __j : __s913;
for (__k = 0; __k < __m913; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t67[__j*P_ncols+__k*P_ncols+__l] = t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s913) {
int __m913 = __j + __s913 > P_ncols ? P_ncols - __j : __s913;
for (__k = 0; __k < __m913; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t67[__j*P_ncols+__k*P_ncols+__l] += t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s916);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s916);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s916,ii+=1) {
// 4_1
int __m916 = i + __s916 > P_ncols ? P_ncols - i : __s916;
double *t25 = t26 + i;
double *t31 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t31 = t31;
predict_1[disp].__m916 = __m916;
predict_1[disp].t12 = t12;
predict_1[disp].t25 = t25;
predict_1[disp].__s915 = __s915;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s916; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s917) {
// 6_1
int __m917 = i + __s917 > P_ncols ? P_ncols - i : __s917;
double *t29 = P + i*P_ncols;
double *t27 = t17 + i*P_ncols;
double *t28 = Q + i*P_ncols;
for (j=0; j<__m917; j+=1) {
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
