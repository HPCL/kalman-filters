#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t9;
double *t29;
double *t23;
int __s1283;
int __m1284;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t19;
int __m1282;
double *t18;
double *t20;
int __s1281;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t19 = msg->t19;
int __m1282 = msg->__m1282;
double *t18 = msg->t18;
double *t20 = msg->t20;
int __s1281 = msg->__s1281;

for (j=0; j<P_ncols; j+=__s1281) {
// 2_2
int __m1281 = j + __s1281 > P_ncols ? P_ncols - j : __s1281;
double *t31 = t20 + j*P_ncols;
double *t30 = t18 + j*P_ncols;
for (k=0; k<__m1281; k+=1) {
// 2_3
double *t42 = t31 + k*P_ncols;
double *t41 = t30 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t42[__zr__] = 0.0;
for (l=0; l<__m1282; l+=1) {
// 2_4
double *t48 = t19 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t42[p] += (t41[l]*t48[p]);
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
double *t29 = msg->t29;
double *t23 = msg->t23;
int __s1283 = msg->__s1283;
int __m1284 = msg->__m1284;

for (j=0; j<__m1284; j+=__s1283) {
// 4_2
int __m1283 = j + __s1283 > __m1284 ? __m1284 - j : __s1283;
double *t34 = t23 + j;
double *t40 = t29 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t45 = t34 + k*P_ncols;
double *t44 = t9 + k*P_ncols;
for (l=0; l<__m1283; l+=1) {
// 4_4
double *t54 = t40 + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t45[l] += (t44[p]*t54[p]);
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

int __s1283 = 512;

int __s1281 = 512;

int nparts__s1284 = 12;
int __s1284;
if (nparts__s1284 > 1 && P_ncols > nparts__s1284) {
__s1284 = P_ncols/nparts__s1284;
// this will fail if P_ncols%nparts__s1284+__s1284 > nparts__s1284
// which primarily effects small sizes
if (P_ncols%nparts__s1284)
++__s1284;
}
else {
__s1284 = P_ncols;
nparts__s1284 = 1;
}

int nparts__s1282 = 12;
int __s1282;
if (nparts__s1282 > 1 && P_ncols > nparts__s1282) {
__s1282 = P_ncols/nparts__s1282;
// this will fail if P_ncols%nparts__s1282+__s1282 > nparts__s1282
// which primarily effects small sizes
if (P_ncols%nparts__s1282)
++__s1282;
}
else {
__s1282 = P_ncols;
nparts__s1282 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*nparts__s1282*P_ncols*P_ncols);
double *t13 = t24;
double *t16 = t24;
double *t9 = t21;
double *t62 = t21;
double *t10 = A;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1282);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1282);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1282,ii+=1) {
// 2_1
int __m1282 = i + __s1282 > P_ncols ? P_ncols - i : __s1282;
double *t20 = t21 + ii*P_ncols*P_ncols;
double *t18 = t10 + i;
double *t19 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t19 = t19;
predict_0[disp].__m1282 = __m1282;
predict_0[disp].t18 = t18;
predict_0[disp].t20 = t20;
predict_0[disp].__s1281 = __s1281;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1282; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1282,ii+=1) {
// 2_1
int __m1282 = i + __s1282 > P_ncols ? P_ncols - i : __s1282;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1281) {
int __m1281 = __j + __s1281 > P_ncols ? P_ncols - __j : __s1281;
for (__k = 0; __k < __m1281; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t62[__j*P_ncols+__k*P_ncols+__l] = t21[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1281) {
int __m1281 = __j + __s1281 > P_ncols ? P_ncols - __j : __s1281;
for (__k = 0; __k < __m1281; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t62[__j*P_ncols+__k*P_ncols+__l] += t21[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1284);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1284);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1284,ii+=1) {
// 4_1
int __m1284 = i + __s1284 > P_ncols ? P_ncols - i : __s1284;
double *t23 = t24 + i;
double *t29 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t29 = t29;
predict_1[disp].t23 = t23;
predict_1[disp].__s1283 = __s1283;
predict_1[disp].__m1284 = __m1284;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1284; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t27 = P + i*P_ncols;
double *t25 = t13 + i*P_ncols;
double *t26 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t27[j] = (t25[j]+t26[j]);
}
}
free(t24);
free(t21);
}
