#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t28;
int __m1065;
double *t12;
double *t22;
int __s1064;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t18;
int __m1063;
double *t17;
double *t19;
int __s1062;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t18 = msg->t18;
int __m1063 = msg->__m1063;
double *t17 = msg->t17;
double *t19 = msg->t19;
int __s1062 = msg->__s1062;

for (j=0; j<P_ncols; j+=__s1062) {
// 2_2
int __m1062 = j + __s1062 > P_ncols ? P_ncols - j : __s1062;
double *t30 = t19 + j*P_ncols;
double *t29 = t17 + j*P_ncols;
for (k=0; k<__m1062; k+=1) {
// 2_3
double *t40 = t30 + k*P_ncols;
double *t39 = t29 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t40[__zr__] = 0.0;
for (l=0; l<__m1063; l+=1) {
// 2_4
double *t46 = t18 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t40[p] += (t39[l]*t46[p]);
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
double *t28 = msg->t28;
int __m1065 = msg->__m1065;
double *t12 = msg->t12;
double *t22 = msg->t22;
int __s1064 = msg->__s1064;

for (j=0; j<P_ncols; j+=__s1064) {
// 4_2
int __m1064 = j + __s1064 > P_ncols ? P_ncols - j : __s1064;
double *t33 = t22 + j*P_ncols;
double *t32 = t12 + j*P_ncols;
for (k=0; k<__m1064; k+=1) {
// 4_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (l=0; l<__m1065; l+=1) {
// 4_4
double *t52 = t28 + l*P_ncols;
t43[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t43[l] += (t42[p]*t52[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j;

int __s1064 = 512;

int __s1062 = 512;

int nparts__s1063 = 12;
int __s1063;
if (nparts__s1063 > 1 && P_ncols > nparts__s1063) {
__s1063 = P_ncols/nparts__s1063;
// this will fail if P_ncols%nparts__s1063+__s1063 > nparts__s1063
// which primarily effects small sizes
if (P_ncols%nparts__s1063)
++__s1063;
}
else {
__s1063 = P_ncols;
nparts__s1063 = 1;
}

int nparts__s1065 = 12;
int __s1065;
if (nparts__s1065 > 1 && P_ncols > nparts__s1065) {
__s1065 = P_ncols/nparts__s1065;
// this will fail if P_ncols%nparts__s1065+__s1065 > nparts__s1065
// which primarily effects small sizes
if (P_ncols%nparts__s1065)
++__s1065;
}
else {
__s1065 = P_ncols;
nparts__s1065 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*nparts__s1063*P_ncols*P_ncols);
double *t13 = t23;
double *t15 = t23;
double *t12 = t20;
double *t9 = t20;
double *t60 = t20;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1063);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1063);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1063,ii+=1) {
// 2_1
int __m1063 = i + __s1063 > P_ncols ? P_ncols - i : __s1063;
double *t19 = t20 + ii*P_ncols*P_ncols;
double *t17 = t10 + i;
double *t18 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t18 = t18;
predict_0[disp].__m1063 = __m1063;
predict_0[disp].t17 = t17;
predict_0[disp].t19 = t19;
predict_0[disp].__s1062 = __s1062;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1063; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1063,ii+=1) {
// 2_1
int __m1063 = i + __s1063 > P_ncols ? P_ncols - i : __s1063;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1062) {
int __m1062 = __j + __s1062 > P_ncols ? P_ncols - __j : __s1062;
for (__k = 0; __k < __m1062; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t60[__j*P_ncols+__k*P_ncols+__l] = t20[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1062) {
int __m1062 = __j + __s1062 > P_ncols ? P_ncols - __j : __s1062;
for (__k = 0; __k < __m1062; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t60[__j*P_ncols+__k*P_ncols+__l] += t20[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1065);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1065);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1065,ii+=1) {
// 4_1
int __m1065 = i + __s1065 > P_ncols ? P_ncols - i : __s1065;
double *t22 = t23 + i;
double *t28 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].__m1065 = __m1065;
predict_1[disp].t12 = t12;
predict_1[disp].t22 = t22;
predict_1[disp].__s1064 = __s1064;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1065; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t26 = P + i*P_ncols;
double *t24 = t13 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t26[j] = (t24[j]+t25[j]);
}
}
free(t23);
free(t20);
}
