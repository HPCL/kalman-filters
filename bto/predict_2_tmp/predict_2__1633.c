#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t32;
double *t31;
double *t33;
int __s3873;
int __m3874;
} predict_2_msg_t;

typedef struct { 
int __m3872;
int P_ncols;
double *t27;
double *t35;
double *t29;
int __s3871;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t24;
int __m3870;
double *P;
double *t25;
int __s3869;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t24 = msg->t24;
int __m3870 = msg->__m3870;
double *P = msg->P;
double *t25 = msg->t25;
int __s3869 = msg->__s3869;

for (j=0; j<P_ncols; j+=__s3869) {
// 2_2
int __m3869 = j + __s3869 > P_ncols ? P_ncols - j : __s3869;
double *t37 = t25 + j;
double *t36 = P + j;
for (k=0; k<__m3870; k+=1) {
// 2_3
double *t48 = t37 + k*P_ncols;
double *t47 = t24 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3869; ++__zr__) t48[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t58 = t36 + l*P_ncols;
for (p=0; p<__m3869; p+=1) {
// 2_5
t48[p] += (t47[l]*t58[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m3872 = msg->__m3872;
int P_ncols = msg->P_ncols;
double *t27 = msg->t27;
double *t35 = msg->t35;
double *t29 = msg->t29;
int __s3871 = msg->__s3871;

for (j=0; j<P_ncols; j+=__s3871) {
// 4_2
int __m3871 = j + __s3871 > P_ncols ? P_ncols - j : __s3871;
double *t40 = t29 + j;
double *t46 = t35 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t51 = t40 + k*__m3871;
double *t50 = t27 + k*P_ncols;
for (l=0; l<__m3871; l+=1) {
// 4_4
double *t68 = t46 + l*P_ncols;
t51[l] = 0.0;
for (p=0; p<__m3872; p+=1) {
// 4_5
t51[l] += (t50[p]*t68[p]);
}
}
}
}
return NULL;
}


void *predict_body_2(void *mesg) {
int disp, __zr__,j,k,l;
predict_2_msg_t *msg = (predict_2_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t32 = msg->t32;
double *t31 = msg->t31;
double *t33 = msg->t33;
int __s3873 = msg->__s3873;
int __m3874 = msg->__m3874;

for (j=0; j<__m3874; j+=__s3873) {
// 6_2
int __m3873 = j + __s3873 > __m3874 ? __m3874 - j : __s3873;
double *t44 = t33 + j;
double *t42 = t31 + j;
double *t43 = t32 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t55 = t44 + k*P_ncols;
double *t53 = t42 + k*P_ncols;
double *t54 = t43 + k*P_ncols;
for (l=0; l<__m3873; l+=1) {
// 6_4
t55[l] = (t53[l]+t54[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s3873 = 496;

int __s3871 = 512;

int __s3869 = 512;

int nparts__s3874 = 10;
int __s3874;
if (nparts__s3874 > 1 && P_ncols > nparts__s3874) {
__s3874 = P_ncols/nparts__s3874;
// this will fail if P_ncols%nparts__s3874+__s3874 > nparts__s3874
// which primarily effects small sizes
if (P_ncols%nparts__s3874)
++__s3874;
}
else {
__s3874 = P_ncols;
nparts__s3874 = 1;
}

int nparts__s3870 = 10;
int __s3870;
if (nparts__s3870 > 1 && P_ncols > nparts__s3870) {
__s3870 = P_ncols/nparts__s3870;
// this will fail if P_ncols%nparts__s3870+__s3870 > nparts__s3870
// which primarily effects small sizes
if (P_ncols%nparts__s3870)
++__s3870;
}
else {
__s3870 = P_ncols;
nparts__s3870 = 1;
}

int nparts__s3872 = 10;
int __s3872;
if (nparts__s3872 > 1 && P_ncols > nparts__s3872) {
__s3872 = P_ncols/nparts__s3872;
// this will fail if P_ncols%nparts__s3872+__s3872 > nparts__s3872
// which primarily effects small sizes
if (P_ncols%nparts__s3872)
++__s3872;
}
else {
__s3872 = P_ncols;
nparts__s3872 = 1;
}

double *t30 = malloc(sizeof(double)*nparts__s3872*P_ncols*P_ncols);
double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = t30;
double *t18 = t30;
double *t13 = t30;
double *t76 = t30;
double *t15 = t26;
double *t9 = t26;
double *t11 = t26;
double *t10 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3870);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3870);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3870,ii+=1) {
// 2_1
int __m3870 = i + __s3870 > P_ncols ? P_ncols - i : __s3870;
double *t25 = t26 + i*P_ncols;
double *t24 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t24 = t24;
predict_0[disp].__m3870 = __m3870;
predict_0[disp].P = P;
predict_0[disp].t25 = t25;
predict_0[disp].__s3869 = __s3869;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3870; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3872);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3872);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3872,ii+=1) {
// 4_1
int __m3872 = i + __s3872 > P_ncols ? P_ncols - i : __s3872;
double *t29 = t30 + ii*P_ncols*P_ncols;
double *t27 = t15 + i;
double *t35 = t17 + i;
predict_1[disp].__m3872 = __m3872;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t27 = t27;
predict_1[disp].t35 = t35;
predict_1[disp].t29 = t29;
predict_1[disp].__s3871 = __s3871;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3872; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s3872,ii+=1) {
// 4_1
int __m3872 = i + __s3872 > P_ncols ? P_ncols - i : __s3872;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s3871) {
int __m3871 = __j + __s3871 > P_ncols ? P_ncols - __j : __s3871;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3871; __l+=1) {
t76[__j+__k*P_ncols+__l] = t30[ii*P_ncols*P_ncols+__j+__k*__m3871+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s3871) {
int __m3871 = __j + __s3871 > P_ncols ? P_ncols - __j : __s3871;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m3871; __l+=1) {
t76[__j+__k*P_ncols+__l] += t30[ii*P_ncols*P_ncols+__j+__k*__m3871+__l];
}
}
}
}
}
}

predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s3874);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s3874);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3874,ii+=1) {
// 6_1
int __m3874 = i + __s3874 > P_ncols ? P_ncols - i : __s3874;
double *t33 = P + i;
double *t31 = t21 + i;
double *t32 = Q + i;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t32 = t32;
predict_2[disp].t31 = t31;
predict_2[disp].t33 = t33;
predict_2[disp].__s3873 = __s3873;
predict_2[disp].__m3874 = __m3874;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s3874; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t30);
free(t26);
}
