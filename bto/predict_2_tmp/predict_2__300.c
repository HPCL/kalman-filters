#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m848;
int P_ncols;
double *t31;
double *t30;
double *t32;
int __s847;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *t34;
int __m846;
double *t12;
double *t28;
int __s845;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t24;
int __m844;
double *t23;
double *t25;
int __s843;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t24 = msg->t24;
int __m844 = msg->__m844;
double *t23 = msg->t23;
double *t25 = msg->t25;
int __s843 = msg->__s843;

for (j=0; j<P_ncols; j+=__s843) {
// 2_2
int __m843 = j + __s843 > P_ncols ? P_ncols - j : __s843;
double *t36 = t25 + j*P_ncols;
double *t35 = t23 + j*P_ncols;
for (k=0; k<__m843; k+=1) {
// 2_3
double *t46 = t36 + k*P_ncols;
double *t45 = t35 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t46[__zr__] = 0.0;
for (l=0; l<__m844; l+=1) {
// 2_4
double *t56 = t24 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t46[p] += (t45[l]*t56[p]);
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
double *t34 = msg->t34;
int __m846 = msg->__m846;
double *t12 = msg->t12;
double *t28 = msg->t28;
int __s845 = msg->__s845;

for (j=0; j<P_ncols; j+=__s845) {
// 4_2
int __m845 = j + __s845 > P_ncols ? P_ncols - j : __s845;
double *t39 = t28 + j*P_ncols;
double *t38 = t12 + j*P_ncols;
for (k=0; k<__m845; k+=1) {
// 4_3
double *t49 = t39 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
for (l=0; l<__m846; l+=1) {
// 4_4
double *t66 = t34 + l*P_ncols;
t49[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t49[l] += (t48[p]*t66[p]);
}
}
}
}
return NULL;
}


void *predict_body_2(void *mesg) {
int disp, __zr__,j,k,l;
predict_2_msg_t *msg = (predict_2_msg_t*)mesg;
int __m848 = msg->__m848;
int P_ncols = msg->P_ncols;
double *t31 = msg->t31;
double *t30 = msg->t30;
double *t32 = msg->t32;
int __s847 = msg->__s847;

for (j=0; j<P_ncols; j+=__s847) {
// 6_2
int __m847 = j + __s847 > P_ncols ? P_ncols - j : __s847;
double *t43 = t32 + j*P_ncols;
double *t41 = t30 + j*P_ncols;
double *t42 = t31 + j*P_ncols;
for (k=0; k<__m847; k+=1) {
// 6_3
double *t53 = t43 + k*P_ncols;
double *t51 = t41 + k*P_ncols;
double *t52 = t42 + k*P_ncols;
for (l=0; l<__m848; l+=1) {
// 6_4
t53[l] = (t51[l]+t52[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s847 = 512;

int __s845 = 512;

int __s843 = 512;

int nparts__s844 = 12;
int __s844;
if (nparts__s844 > 1 && P_ncols > nparts__s844) {
__s844 = P_ncols/nparts__s844;
// this will fail if P_ncols%nparts__s844+__s844 > nparts__s844
// which primarily effects small sizes
if (P_ncols%nparts__s844)
++__s844;
}
else {
__s844 = P_ncols;
nparts__s844 = 1;
}

int nparts__s846 = 12;
int __s846;
if (nparts__s846 > 1 && P_ncols > nparts__s846) {
__s846 = P_ncols/nparts__s846;
// this will fail if P_ncols%nparts__s846+__s846 > nparts__s846
// which primarily effects small sizes
if (P_ncols%nparts__s846)
++__s846;
}
else {
__s846 = P_ncols;
nparts__s846 = 1;
}

int nparts__s848 = 12;
int __s848;
if (nparts__s848 > 1 && P_ncols > nparts__s848) {
__s848 = P_ncols/nparts__s848;
// this will fail if P_ncols%nparts__s848+__s848 > nparts__s848
// which primarily effects small sizes
if (P_ncols%nparts__s848)
++__s848;
}
else {
__s848 = P_ncols;
nparts__s848 = 1;
}

double *t29 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t26 = malloc(sizeof(double)*nparts__s844*P_ncols*P_ncols);
double *t20 = t29;
double *t17 = t29;
double *t13 = t29;
double *t15 = t29;
double *t12 = t26;
double *t9 = t26;
double *t74 = t26;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s844);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s844);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s844,ii+=1) {
// 2_1
int __m844 = i + __s844 > P_ncols ? P_ncols - i : __s844;
double *t25 = t26 + ii*P_ncols*P_ncols;
double *t23 = t10 + i;
double *t24 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t24 = t24;
predict_0[disp].__m844 = __m844;
predict_0[disp].t23 = t23;
predict_0[disp].t25 = t25;
predict_0[disp].__s843 = __s843;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s844; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s844,ii+=1) {
// 2_1
int __m844 = i + __s844 > P_ncols ? P_ncols - i : __s844;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s843) {
int __m843 = __j + __s843 > P_ncols ? P_ncols - __j : __s843;
for (__k = 0; __k < __m843; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t74[__j*P_ncols+__k*P_ncols+__l] = t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s843) {
int __m843 = __j + __s843 > P_ncols ? P_ncols - __j : __s843;
for (__k = 0; __k < __m843; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t74[__j*P_ncols+__k*P_ncols+__l] += t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s846);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s846);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s846,ii+=1) {
// 4_1
int __m846 = i + __s846 > P_ncols ? P_ncols - i : __s846;
double *t28 = t29 + i;
double *t34 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t34 = t34;
predict_1[disp].__m846 = __m846;
predict_1[disp].t12 = t12;
predict_1[disp].t28 = t28;
predict_1[disp].__s845 = __s845;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s846; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s848);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s848);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s848,ii+=1) {
// 6_1
int __m848 = i + __s848 > P_ncols ? P_ncols - i : __s848;
double *t32 = P + i;
double *t30 = t20 + i;
double *t31 = Q + i;
predict_2[disp].__m848 = __m848;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t31 = t31;
predict_2[disp].t30 = t30;
predict_2[disp].t32 = t32;
predict_2[disp].__s847 = __s847;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s848; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t29);
free(t26);
}
