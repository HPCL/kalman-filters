#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m3222;
double *t31;
double *t30;
double *t32;
int __s3221;
} predict_2_msg_t;

typedef struct { 
int __m3220;
int P_ncols;
double *t34;
double *t26;
double *t28;
int __s3219;
} predict_1_msg_t;

typedef struct { 
int __m3218;
int P_ncols;
double *t24;
double *t23;
double *t8;
int __s3217;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m3218 = msg->__m3218;
int P_ncols = msg->P_ncols;
double *t24 = msg->t24;
double *t23 = msg->t23;
double *t8 = msg->t8;
int __s3217 = msg->__s3217;

for (j=0; j<P_ncols; j+=__s3217) {
// 2_2
int __m3217 = j + __s3217 > P_ncols ? P_ncols - j : __s3217;
double *t35 = t8 + j;
double *t36 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t47 = t24 + k*P_ncols;
double *t46 = t35 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m3218; ++__zr__) t47[__zr__] = 0.0;
for (l=0; l<__m3217; l+=1) {
// 2_4
double *t57 = t36 + l*P_ncols;
for (p=0; p<__m3218; p+=1) {
// 2_5
t47[p] += (t46[l]*t57[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m3220 = msg->__m3220;
int P_ncols = msg->P_ncols;
double *t34 = msg->t34;
double *t26 = msg->t26;
double *t28 = msg->t28;
int __s3219 = msg->__s3219;

for (j=0; j<P_ncols; j+=__s3219) {
// 4_2
int __m3219 = j + __s3219 > P_ncols ? P_ncols - j : __s3219;
double *t40 = t28 + j*P_ncols;
double *t39 = t26 + j*P_ncols;
for (k=0; k<__m3219; k+=1) {
// 4_3
double *t50 = t40 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t67 = t34 + l*P_ncols;
t50[l] = 0.0;
for (p=0; p<__m3220; p+=1) {
// 4_5
t50[l] += (t49[p]*t67[p]);
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
int __m3222 = msg->__m3222;
double *t31 = msg->t31;
double *t30 = msg->t30;
double *t32 = msg->t32;
int __s3221 = msg->__s3221;

for (j=0; j<P_ncols; j+=__s3221) {
// 6_2
int __m3221 = j + __s3221 > P_ncols ? P_ncols - j : __s3221;
double *t44 = t32 + j;
double *t42 = t30 + j;
double *t43 = t31 + j;
for (k=0; k<__m3222; k+=1) {
// 6_3
double *t54 = t44 + k*P_ncols;
double *t52 = t42 + k*P_ncols;
double *t53 = t43 + k*P_ncols;
for (l=0; l<__m3221; l+=1) {
// 6_4
t54[l] = (t52[l]+t53[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s3221 = 504;

int __s3219 = 504;

int __s3217 = 512;

int nparts__s3218 = 12;
int __s3218;
if (nparts__s3218 > 1 && P_ncols > nparts__s3218) {
__s3218 = P_ncols/nparts__s3218;
// this will fail if P_ncols%nparts__s3218+__s3218 > nparts__s3218
// which primarily effects small sizes
if (P_ncols%nparts__s3218)
++__s3218;
}
else {
__s3218 = P_ncols;
nparts__s3218 = 1;
}

int nparts__s3220 = 12;
int __s3220;
if (nparts__s3220 > 1 && P_ncols > nparts__s3220) {
__s3220 = P_ncols/nparts__s3220;
// this will fail if P_ncols%nparts__s3220+__s3220 > nparts__s3220
// which primarily effects small sizes
if (P_ncols%nparts__s3220)
++__s3220;
}
else {
__s3220 = P_ncols;
nparts__s3220 = 1;
}

int nparts__s3222 = 12;
int __s3222;
if (nparts__s3222 > 1 && P_ncols > nparts__s3222) {
__s3222 = P_ncols/nparts__s3222;
// this will fail if P_ncols%nparts__s3222+__s3222 > nparts__s3222
// which primarily effects small sizes
if (P_ncols%nparts__s3222)
++__s3222;
}
else {
__s3222 = P_ncols;
nparts__s3222 = 1;
}

double *t29 = malloc(sizeof(double)*nparts__s3220*P_ncols*P_ncols);
double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = t29;
double *t17 = t29;
double *t13 = t29;
double *t75 = t29;
double *t14 = t25;
double *t12 = t25;
double *t11 = t25;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3218);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3218);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3218,ii+=1) {
// 2_1
int __m3218 = i + __s3218 > P_ncols ? P_ncols - i : __s3218;
double *t24 = t25 + i;
double *t23 = P + i;
predict_0[disp].__m3218 = __m3218;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t24 = t24;
predict_0[disp].t23 = t23;
predict_0[disp].t8 = t8;
predict_0[disp].__s3217 = __s3217;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3218; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3220);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3220);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3220,ii+=1) {
// 4_1
int __m3220 = i + __s3220 > P_ncols ? P_ncols - i : __s3220;
double *t28 = t29 + ii*P_ncols*P_ncols;
double *t26 = t14 + i;
double *t34 = t16 + i;
predict_1[disp].__m3220 = __m3220;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t34 = t34;
predict_1[disp].t26 = t26;
predict_1[disp].t28 = t28;
predict_1[disp].__s3219 = __s3219;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3220; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s3220,ii+=1) {
// 4_1
int __m3220 = i + __s3220 > P_ncols ? P_ncols - i : __s3220;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s3219) {
int __m3219 = __j + __s3219 > P_ncols ? P_ncols - __j : __s3219;
for (__k = 0; __k < __m3219; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t75[__j*P_ncols+__k*P_ncols+__l] = t29[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s3219) {
int __m3219 = __j + __s3219 > P_ncols ? P_ncols - __j : __s3219;
for (__k = 0; __k < __m3219; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t75[__j*P_ncols+__k*P_ncols+__l] += t29[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s3222);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s3222);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3222,ii+=1) {
// 6_1
int __m3222 = i + __s3222 > P_ncols ? P_ncols - i : __s3222;
double *t32 = P + i*P_ncols;
double *t30 = t20 + i*P_ncols;
double *t31 = Q + i*P_ncols;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].__m3222 = __m3222;
predict_2[disp].t31 = t31;
predict_2[disp].t30 = t30;
predict_2[disp].t32 = t32;
predict_2[disp].__s3221 = __s3221;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s3222; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t29);
free(t25);
}
