#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2966;
int P_ncols;
double *t31;
double *t23;
double *t25;
int __s2965;
} predict_1_msg_t;

typedef struct { 
int __m2964;
int P_ncols;
double *t21;
double *t20;
double *t8;
int __s2963;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2964 = msg->__m2964;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
double *t20 = msg->t20;
double *t8 = msg->t8;
int __s2963 = msg->__s2963;

for (j=0; j<P_ncols; j+=__s2963) {
// 2_2
int __m2963 = j + __s2963 > P_ncols ? P_ncols - j : __s2963;
double *t32 = t8 + j;
double *t33 = t20 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t44 = t21 + k*P_ncols;
double *t43 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2964; ++__zr__) t44[__zr__] = 0.0;
for (l=0; l<__m2963; l+=1) {
// 2_4
double *t54 = t33 + l*P_ncols;
for (p=0; p<__m2964; p+=1) {
// 2_5
t44[p] += (t43[l]*t54[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m2966 = msg->__m2966;
int P_ncols = msg->P_ncols;
double *t31 = msg->t31;
double *t23 = msg->t23;
double *t25 = msg->t25;
int __s2965 = msg->__s2965;

for (j=0; j<P_ncols; j+=__s2965) {
// 4_2
int __m2965 = j + __s2965 > P_ncols ? P_ncols - j : __s2965;
double *t37 = t25 + j*P_ncols;
double *t36 = t23 + j*P_ncols;
for (k=0; k<__m2965; k+=1) {
// 4_3
double *t47 = t37 + k*P_ncols;
double *t46 = t36 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t60 = t31 + l*P_ncols;
t47[l] = 0.0;
for (p=0; p<__m2966; p+=1) {
// 4_5
t47[l] += (t46[p]*t60[p]);
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

int __s2967 = 12;

int __s2965 = 496;

int __s2963 = 512;

int nparts__s2964 = 12;
int __s2964;
if (nparts__s2964 > 1 && P_ncols > nparts__s2964) {
__s2964 = P_ncols/nparts__s2964;
// this will fail if P_ncols%nparts__s2964+__s2964 > nparts__s2964
// which primarily effects small sizes
if (P_ncols%nparts__s2964)
++__s2964;
}
else {
__s2964 = P_ncols;
nparts__s2964 = 1;
}

int nparts__s2966 = 12;
int __s2966;
if (nparts__s2966 > 1 && P_ncols > nparts__s2966) {
__s2966 = P_ncols/nparts__s2966;
// this will fail if P_ncols%nparts__s2966+__s2966 > nparts__s2966
// which primarily effects small sizes
if (P_ncols%nparts__s2966)
++__s2966;
}
else {
__s2966 = P_ncols;
nparts__s2966 = 1;
}

double *t26 = malloc(sizeof(double)*nparts__s2966*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = t26;
double *t13 = t26;
double *t68 = t26;
double *t14 = t22;
double *t12 = t22;
double *t11 = t22;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2964);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2964);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2964,ii+=1) {
// 2_1
int __m2964 = i + __s2964 > P_ncols ? P_ncols - i : __s2964;
double *t21 = t22 + i;
double *t20 = P + i;
predict_0[disp].__m2964 = __m2964;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].t20 = t20;
predict_0[disp].t8 = t8;
predict_0[disp].__s2963 = __s2963;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2964; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2966);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2966);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2966,ii+=1) {
// 4_1
int __m2966 = i + __s2966 > P_ncols ? P_ncols - i : __s2966;
double *t25 = t26 + ii*P_ncols*P_ncols;
double *t23 = t14 + i;
double *t31 = t16 + i;
predict_1[disp].__m2966 = __m2966;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t31 = t31;
predict_1[disp].t23 = t23;
predict_1[disp].t25 = t25;
predict_1[disp].__s2965 = __s2965;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2966; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2966,ii+=1) {
// 4_1
int __m2966 = i + __s2966 > P_ncols ? P_ncols - i : __s2966;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2965) {
int __m2965 = __j + __s2965 > P_ncols ? P_ncols - __j : __s2965;
for (__k = 0; __k < __m2965; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t68[__j*P_ncols+__k*P_ncols+__l] = t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2965) {
int __m2965 = __j + __s2965 > P_ncols ? P_ncols - __j : __s2965;
for (__k = 0; __k < __m2965; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t68[__j*P_ncols+__k*P_ncols+__l] += t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s2967) {
// 6_1
int __m2967 = i + __s2967 > P_ncols ? P_ncols - i : __s2967;
double *t29 = P + i*P_ncols;
double *t27 = t17 + i*P_ncols;
double *t28 = Q + i*P_ncols;
for (j=0; j<__m2967; j+=1) {
// 6_2
double *t41 = t29 + j*P_ncols;
double *t39 = t27 + j*P_ncols;
double *t40 = t28 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t41[k] = (t39[k]+t40[k]);
}
}
}
free(t26);
free(t22);
}
