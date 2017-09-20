#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m1089;
double *t32;
double *t33;
int __s1090;
double *t9;
double *t35;
int __s1088;
int __s1089;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t25;
int __m1087;
double *t24;
double *t26;
int __s1086;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t25 = msg->t25;
int __m1087 = msg->__m1087;
double *t24 = msg->t24;
double *t26 = msg->t26;
int __s1086 = msg->__s1086;

for (j=0; j<P_ncols; j+=__s1086) {
// 2_2
int __m1086 = j + __s1086 > P_ncols ? P_ncols - j : __s1086;
double *t37 = t26 + j*P_ncols;
double *t36 = t24 + j*P_ncols;
for (k=0; k<__m1086; k+=1) {
// 2_3
double *t48 = t37 + k*P_ncols;
double *t47 = t36 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t48[__zr__] = 0.0;
for (l=0; l<__m1087; l+=1) {
// 2_4
double *t58 = t25 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
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
int __m1089 = msg->__m1089;
double *t32 = msg->t32;
double *t33 = msg->t33;
int __s1090 = msg->__s1090;
double *t9 = msg->t9;
double *t35 = msg->t35;
int __s1088 = msg->__s1088;
int __s1089 = msg->__s1089;

double *t29 = malloc(sizeof(double)*__s1089*P_ncols);
for (j=0; j<__m1089; j+=__s1088) {
// 4_2
int __m1088 = j + __s1088 > __m1089 ? __m1089 - j : __s1088;
double *t40 = t29 + j;
double *t46 = t35 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t51 = t40 + k*__m1089;
double *t50 = t9 + k*P_ncols;
for (l=0; l<__m1088; l+=1) {
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
for (j=0; j<__m1089; j+=__s1090) {
// 6_2
int __m1090 = j + __s1090 > __m1089 ? __m1089 - j : __s1090;
double *t44 = t33 + j;
double *t42 = t29 + j;
double *t43 = t32 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t55 = t44 + k*P_ncols;
double *t53 = t42 + k*__m1089;
double *t54 = t43 + k*P_ncols;
for (l=0; l<__m1090; l+=1) {
// 6_4
t55[l] = (t53[l]+t54[l]);
}
}
}
free(t29);
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s1090 = 504;

int __s1088 = 512;

int __s1086 = 512;

int nparts__s1089 = 12;
int __s1089;
if (nparts__s1089 > 1 && P_ncols > nparts__s1089) {
__s1089 = P_ncols/nparts__s1089;
// this will fail if P_ncols%nparts__s1089+__s1089 > nparts__s1089
// which primarily effects small sizes
if (P_ncols%nparts__s1089)
++__s1089;
}
else {
__s1089 = P_ncols;
nparts__s1089 = 1;
}

int nparts__s1087 = 12;
int __s1087;
if (nparts__s1087 > 1 && P_ncols > nparts__s1087) {
__s1087 = P_ncols/nparts__s1087;
// this will fail if P_ncols%nparts__s1087+__s1087 > nparts__s1087
// which primarily effects small sizes
if (P_ncols%nparts__s1087)
++__s1087;
}
else {
__s1087 = P_ncols;
nparts__s1087 = 1;
}

double *t27 = malloc(sizeof(double)*nparts__s1087*P_ncols*P_ncols);
double *t9 = t27;
double *t76 = t27;
double *t10 = A;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1087);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1087);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1087,ii+=1) {
// 2_1
int __m1087 = i + __s1087 > P_ncols ? P_ncols - i : __s1087;
double *t26 = t27 + ii*P_ncols*P_ncols;
double *t24 = t10 + i;
double *t25 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t25 = t25;
predict_0[disp].__m1087 = __m1087;
predict_0[disp].t24 = t24;
predict_0[disp].t26 = t26;
predict_0[disp].__s1086 = __s1086;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1087; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1087,ii+=1) {
// 2_1
int __m1087 = i + __s1087 > P_ncols ? P_ncols - i : __s1087;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1086) {
int __m1086 = __j + __s1086 > P_ncols ? P_ncols - __j : __s1086;
for (__k = 0; __k < __m1086; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t76[__j*P_ncols+__k*P_ncols+__l] = t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1086) {
int __m1086 = __j + __s1086 > P_ncols ? P_ncols - __j : __s1086;
for (__k = 0; __k < __m1086; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t76[__j*P_ncols+__k*P_ncols+__l] += t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1089);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1089);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1089,ii+=1) {
// 4_1
int __m1089 = i + __s1089 > P_ncols ? P_ncols - i : __s1089;
double *t33 = P + i;
double *t35 = t17 + i*P_ncols;
double *t32 = Q + i;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m1089 = __m1089;
predict_1[disp].t32 = t32;
predict_1[disp].t33 = t33;
predict_1[disp].__s1090 = __s1090;
predict_1[disp].t9 = t9;
predict_1[disp].t35 = t35;
predict_1[disp].__s1088 = __s1088;
predict_1[disp].__s1089 = __s1089;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1089; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t27);
}
