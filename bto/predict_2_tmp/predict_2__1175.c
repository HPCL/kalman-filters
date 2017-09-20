#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m3020;
int P_ncols;
double *t28;
double *t27;
double *t29;
int __s3019;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
int __m3017;
double *t20;
double *t21;
double *t22;
int __s3016;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m3017 = msg->__m3017;
double *t20 = msg->t20;
double *t21 = msg->t21;
double *t22 = msg->t22;
int __s3016 = msg->__s3016;

for (j=0; j<P_ncols; j+=__s3016) {
// 2_2
int __m3016 = j + __s3016 > P_ncols ? P_ncols - j : __s3016;
double *t32 = t22 + j;
double *t31 = t21 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t42 = t32 + k*__m3016;
double *t41 = t20 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3016; ++__zr__) t42[__zr__] = 0.0;
for (l=0; l<__m3017; l+=1) {
// 2_4
double *t53 = t31 + l*P_ncols;
for (p=0; p<__m3016; p+=1) {
// 2_5
t42[p] += (t41[l]*t53[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m3020 = msg->__m3020;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s3019 = msg->__s3019;

for (j=0; j<P_ncols; j+=__s3019) {
// 6_2
int __m3019 = j + __s3019 > P_ncols ? P_ncols - j : __s3019;
double *t39 = t29 + j*P_ncols;
double *t37 = t27 + j*P_ncols;
double *t38 = t28 + j*P_ncols;
for (k=0; k<__m3019; k+=1) {
// 6_3
double *t49 = t39 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
for (l=0; l<__m3020; l+=1) {
// 6_4
t49[l] = (t47[l]+t48[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s3019 = 504;

int __s3018 = 12;

int __s3016 = 512;

int nparts__s3017 = 12;
int __s3017;
if (nparts__s3017 > 1 && P_ncols > nparts__s3017) {
__s3017 = P_ncols/nparts__s3017;
// this will fail if P_ncols%nparts__s3017+__s3017 > nparts__s3017
// which primarily effects small sizes
if (P_ncols%nparts__s3017)
++__s3017;
}
else {
__s3017 = P_ncols;
nparts__s3017 = 1;
}

int nparts__s3020 = 12;
int __s3020;
if (nparts__s3020 > 1 && P_ncols > nparts__s3020) {
__s3020 = P_ncols/nparts__s3020;
// this will fail if P_ncols%nparts__s3020+__s3020 > nparts__s3020
// which primarily effects small sizes
if (P_ncols%nparts__s3020)
++__s3020;
}
else {
__s3020 = P_ncols;
nparts__s3020 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*nparts__s3017*P_ncols*P_ncols);
double *t17 = t26;
double *t14 = t26;
double *t13 = t26;
double *t12 = t23;
double *t9 = t23;
double *t67 = t23;
double *t10 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3017);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3017);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3017,ii+=1) {
// 2_1
int __m3017 = i + __s3017 > P_ncols ? P_ncols - i : __s3017;
double *t22 = t23 + ii*P_ncols*P_ncols;
double *t20 = t10 + i;
double *t21 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m3017 = __m3017;
predict_0[disp].t20 = t20;
predict_0[disp].t21 = t21;
predict_0[disp].t22 = t22;
predict_0[disp].__s3016 = __s3016;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3017; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s3017,ii+=1) {
// 2_1
int __m3017 = i + __s3017 > P_ncols ? P_ncols - i : __s3017;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s3016) {
int __m3016 = __j + __s3016 > P_ncols ? P_ncols - __j : __s3016;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3016; __l+=1) {
t67[__j+__k*P_ncols+__l] = t23[ii*P_ncols*P_ncols+__j+__k*__m3016+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s3016) {
int __m3016 = __j + __s3016 > P_ncols ? P_ncols - __j : __s3016;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3016; __l+=1) {
t67[__j+__k*P_ncols+__l] += t23[ii*P_ncols*P_ncols+__j+__k*__m3016+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s3018) {
// 4_1
int __m3018 = i + __s3018 > P_ncols ? P_ncols - i : __s3018;
double *t25 = t26 + i*P_ncols;
double *t24 = t12 + i*P_ncols;
for (j=0; j<__m3018; j+=1) {
// 4_2
double *t35 = t25 + j*P_ncols;
double *t34 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t51 = A + k*P_ncols;
t35[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t35[k] += (t34[l]*t51[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3020);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3020);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3020,ii+=1) {
// 6_1
int __m3020 = i + __s3020 > P_ncols ? P_ncols - i : __s3020;
double *t29 = P + i;
double *t27 = t17 + i;
double *t28 = Q + i;
predict_1[disp].__m3020 = __m3020;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s3019 = __s3019;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3020; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t26);
free(t23);
}
