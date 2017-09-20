#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t32;
double *t31;
double *t33;
int __s2864;
int __m2865;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *t9;
double *t35;
double *t29;
int __s2862;
int __m2863;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
int __m2861;
double *t24;
double *t25;
double *t26;
int __s2860;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m2861 = msg->__m2861;
double *t24 = msg->t24;
double *t25 = msg->t25;
double *t26 = msg->t26;
int __s2860 = msg->__s2860;

for (j=0; j<P_ncols; j+=__s2860) {
// 2_2
int __m2860 = j + __s2860 > P_ncols ? P_ncols - j : __s2860;
double *t37 = t26 + j;
double *t36 = t25 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t48 = t37 + k*__m2860;
double *t47 = t24 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2860; ++__zr__) t48[__zr__] = 0.0;
for (l=0; l<__m2861; l+=1) {
// 2_4
double *t58 = t36 + l*P_ncols;
for (p=0; p<__m2860; p+=1) {
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
int P_ncols = msg->P_ncols;
double *t9 = msg->t9;
double *t35 = msg->t35;
double *t29 = msg->t29;
int __s2862 = msg->__s2862;
int __m2863 = msg->__m2863;

for (j=0; j<__m2863; j+=__s2862) {
// 4_2
int __m2862 = j + __s2862 > __m2863 ? __m2863 - j : __s2862;
double *t40 = t29 + j;
double *t46 = t35 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t51 = t40 + k*P_ncols;
double *t50 = t9 + k*P_ncols;
for (l=0; l<__m2862; l+=1) {
// 4_4
double *t68 = t46 + l*P_ncols;
t51[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
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
int __s2864 = msg->__s2864;
int __m2865 = msg->__m2865;

for (j=0; j<__m2865; j+=__s2864) {
// 6_2
int __m2864 = j + __s2864 > __m2865 ? __m2865 - j : __s2864;
double *t44 = t33 + j;
double *t42 = t31 + j;
double *t43 = t32 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t55 = t44 + k*P_ncols;
double *t53 = t42 + k*P_ncols;
double *t54 = t43 + k*P_ncols;
for (l=0; l<__m2864; l+=1) {
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

int __s2864 = 512;

int __s2862 = 504;

int __s2860 = 512;

int nparts__s2865 = 10;
int __s2865;
if (nparts__s2865 > 1 && P_ncols > nparts__s2865) {
__s2865 = P_ncols/nparts__s2865;
// this will fail if P_ncols%nparts__s2865+__s2865 > nparts__s2865
// which primarily effects small sizes
if (P_ncols%nparts__s2865)
++__s2865;
}
else {
__s2865 = P_ncols;
nparts__s2865 = 1;
}

int nparts__s2863 = 10;
int __s2863;
if (nparts__s2863 > 1 && P_ncols > nparts__s2863) {
__s2863 = P_ncols/nparts__s2863;
// this will fail if P_ncols%nparts__s2863+__s2863 > nparts__s2863
// which primarily effects small sizes
if (P_ncols%nparts__s2863)
++__s2863;
}
else {
__s2863 = P_ncols;
nparts__s2863 = 1;
}

int nparts__s2861 = 10;
int __s2861;
if (nparts__s2861 > 1 && P_ncols > nparts__s2861) {
__s2861 = P_ncols/nparts__s2861;
// this will fail if P_ncols%nparts__s2861+__s2861 > nparts__s2861
// which primarily effects small sizes
if (P_ncols%nparts__s2861)
++__s2861;
}
else {
__s2861 = P_ncols;
nparts__s2861 = 1;
}

double *t30 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t27 = malloc(sizeof(double)*nparts__s2861*P_ncols*P_ncols);
double *t21 = t30;
double *t18 = t30;
double *t13 = t30;
double *t16 = t30;
double *t9 = t27;
double *t76 = t27;
double *t10 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2861);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2861);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2861,ii+=1) {
// 2_1
int __m2861 = i + __s2861 > P_ncols ? P_ncols - i : __s2861;
double *t26 = t27 + ii*P_ncols*P_ncols;
double *t24 = t10 + i;
double *t25 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m2861 = __m2861;
predict_0[disp].t24 = t24;
predict_0[disp].t25 = t25;
predict_0[disp].t26 = t26;
predict_0[disp].__s2860 = __s2860;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2861; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2861,ii+=1) {
// 2_1
int __m2861 = i + __s2861 > P_ncols ? P_ncols - i : __s2861;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2860) {
int __m2860 = __j + __s2860 > P_ncols ? P_ncols - __j : __s2860;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m2860; __l+=1) {
t76[__j+__k*P_ncols+__l] = t27[ii*P_ncols*P_ncols+__j+__k*__m2860+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2860) {
int __m2860 = __j + __s2860 > P_ncols ? P_ncols - __j : __s2860;
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < __m2860; __l+=1) {
t76[__j+__k*P_ncols+__l] += t27[ii*P_ncols*P_ncols+__j+__k*__m2860+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2863);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2863);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2863,ii+=1) {
// 4_1
int __m2863 = i + __s2863 > P_ncols ? P_ncols - i : __s2863;
double *t29 = t30 + i;
double *t35 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t35 = t35;
predict_1[disp].t29 = t29;
predict_1[disp].__s2862 = __s2862;
predict_1[disp].__m2863 = __m2863;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2863; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s2865);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s2865);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2865,ii+=1) {
// 6_1
int __m2865 = i + __s2865 > P_ncols ? P_ncols - i : __s2865;
double *t33 = P + i;
double *t31 = t21 + i;
double *t32 = Q + i;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t32 = t32;
predict_2[disp].t31 = t31;
predict_2[disp].t33 = t33;
predict_2[disp].__s2864 = __s2864;
predict_2[disp].__m2865 = __m2865;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s2865; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t30);
free(t27);
}
