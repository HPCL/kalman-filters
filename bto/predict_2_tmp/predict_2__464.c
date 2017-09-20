#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t32;
double *t26;
int __s1221;
int __m1222;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t22;
int __m1220;
double *t21;
double *t23;
int __s1219;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t22 = msg->t22;
int __m1220 = msg->__m1220;
double *t21 = msg->t21;
double *t23 = msg->t23;
int __s1219 = msg->__s1219;

for (j=0; j<P_ncols; j+=__s1219) {
// 2_2
int __m1219 = j + __s1219 > P_ncols ? P_ncols - j : __s1219;
double *t34 = t23 + j*P_ncols;
double *t33 = t21 + j*P_ncols;
for (k=0; k<__m1219; k+=1) {
// 2_3
double *t45 = t34 + k*P_ncols;
double *t44 = t33 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t45[__zr__] = 0.0;
for (l=0; l<__m1220; l+=1) {
// 2_4
double *t55 = t22 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t45[p] += (t44[l]*t55[p]);
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
double *t32 = msg->t32;
double *t26 = msg->t26;
int __s1221 = msg->__s1221;
int __m1222 = msg->__m1222;

for (j=0; j<__m1222; j+=__s1221) {
// 4_2
int __m1221 = j + __s1221 > __m1222 ? __m1222 - j : __s1221;
double *t37 = t26 + j;
double *t43 = t32 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t48 = t37 + k*P_ncols;
double *t47 = t9 + k*P_ncols;
for (l=0; l<__m1221; l+=1) {
// 4_4
double *t61 = t43 + l*P_ncols;
t48[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t48[l] += (t47[p]*t61[p]);
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

int __s1223 = 12;

int __s1221 = 512;

int __s1219 = 512;

int nparts__s1222 = 12;
int __s1222;
if (nparts__s1222 > 1 && P_ncols > nparts__s1222) {
__s1222 = P_ncols/nparts__s1222;
// this will fail if P_ncols%nparts__s1222+__s1222 > nparts__s1222
// which primarily effects small sizes
if (P_ncols%nparts__s1222)
++__s1222;
}
else {
__s1222 = P_ncols;
nparts__s1222 = 1;
}

int nparts__s1220 = 12;
int __s1220;
if (nparts__s1220 > 1 && P_ncols > nparts__s1220) {
__s1220 = P_ncols/nparts__s1220;
// this will fail if P_ncols%nparts__s1220+__s1220 > nparts__s1220
// which primarily effects small sizes
if (P_ncols%nparts__s1220)
++__s1220;
}
else {
__s1220 = P_ncols;
nparts__s1220 = 1;
}

double *t27 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t24 = malloc(sizeof(double)*nparts__s1220*P_ncols*P_ncols);
double *t18 = t27;
double *t13 = t27;
double *t16 = t27;
double *t9 = t24;
double *t69 = t24;
double *t10 = A;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1220);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1220);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1220,ii+=1) {
// 2_1
int __m1220 = i + __s1220 > P_ncols ? P_ncols - i : __s1220;
double *t23 = t24 + ii*P_ncols*P_ncols;
double *t21 = t10 + i;
double *t22 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t22 = t22;
predict_0[disp].__m1220 = __m1220;
predict_0[disp].t21 = t21;
predict_0[disp].t23 = t23;
predict_0[disp].__s1219 = __s1219;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1220; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1220,ii+=1) {
// 2_1
int __m1220 = i + __s1220 > P_ncols ? P_ncols - i : __s1220;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1219) {
int __m1219 = __j + __s1219 > P_ncols ? P_ncols - __j : __s1219;
for (__k = 0; __k < __m1219; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] = t24[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1219) {
int __m1219 = __j + __s1219 > P_ncols ? P_ncols - __j : __s1219;
for (__k = 0; __k < __m1219; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] += t24[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1222);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1222);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1222,ii+=1) {
// 4_1
int __m1222 = i + __s1222 > P_ncols ? P_ncols - i : __s1222;
double *t26 = t27 + i;
double *t32 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t32 = t32;
predict_1[disp].t26 = t26;
predict_1[disp].__s1221 = __s1221;
predict_1[disp].__m1222 = __m1222;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1222; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s1223) {
// 6_1
int __m1223 = i + __s1223 > P_ncols ? P_ncols - i : __s1223;
double *t30 = P + i*P_ncols;
double *t28 = t18 + i*P_ncols;
double *t29 = Q + i*P_ncols;
for (j=0; j<__m1223; j+=1) {
// 6_2
double *t41 = t30 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
double *t40 = t29 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t41[k] = (t39[k]+t40[k]);
}
}
}
free(t27);
free(t24);
}
