#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2179;
int P_ncols;
double *t32;
double *t24;
double *t26;
int __s2178;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t21;
int __m2177;
double *t20;
double *t22;
int __s2176;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
int __m2177 = msg->__m2177;
double *t20 = msg->t20;
double *t22 = msg->t22;
int __s2176 = msg->__s2176;

for (j=0; j<P_ncols; j+=__s2176) {
// 2_2
int __m2176 = j + __s2176 > P_ncols ? P_ncols - j : __s2176;
double *t34 = t22 + j*P_ncols;
double *t33 = t20 + j*P_ncols;
for (k=0; k<__m2176; k+=1) {
// 2_3
double *t44 = t34 + k*P_ncols;
double *t43 = t33 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t44[__zr__] = 0.0;
for (l=0; l<__m2177; l+=1) {
// 2_4
double *t54 = t21 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
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
int __m2179 = msg->__m2179;
int P_ncols = msg->P_ncols;
double *t32 = msg->t32;
double *t24 = msg->t24;
double *t26 = msg->t26;
int __s2178 = msg->__s2178;

for (j=0; j<P_ncols; j+=__s2178) {
// 4_2
int __m2178 = j + __s2178 > P_ncols ? P_ncols - j : __s2178;
double *t37 = t26 + j*P_ncols;
double *t36 = t24 + j*P_ncols;
for (k=0; k<__m2178; k+=1) {
// 4_3
double *t47 = t37 + k*P_ncols;
double *t46 = t36 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t60 = t32 + l*P_ncols;
t47[l] = 0.0;
for (p=0; p<__m2179; p+=1) {
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

int __s2180 = 12;

int __s2178 = 512;

int __s2176 = 504;

int nparts__s2177 = 12;
int __s2177;
if (nparts__s2177 > 1 && P_ncols > nparts__s2177) {
__s2177 = P_ncols/nparts__s2177;
// this will fail if P_ncols%nparts__s2177+__s2177 > nparts__s2177
// which primarily effects small sizes
if (P_ncols%nparts__s2177)
++__s2177;
}
else {
__s2177 = P_ncols;
nparts__s2177 = 1;
}

int nparts__s2179 = 12;
int __s2179;
if (nparts__s2179 > 1 && P_ncols > nparts__s2179) {
__s2179 = P_ncols/nparts__s2179;
// this will fail if P_ncols%nparts__s2179+__s2179 > nparts__s2179
// which primarily effects small sizes
if (P_ncols%nparts__s2179)
++__s2179;
}
else {
__s2179 = P_ncols;
nparts__s2179 = 1;
}

double *t27 = malloc(sizeof(double)*nparts__s2179*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*nparts__s2177*P_ncols*P_ncols);
double *t17 = t27;
double *t13 = t27;
double *t69 = t27;
double *t14 = t23;
double *t12 = t23;
double *t9 = t23;
double *t68 = t23;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2177);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2177);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2177,ii+=1) {
// 2_1
int __m2177 = i + __s2177 > P_ncols ? P_ncols - i : __s2177;
double *t22 = t23 + ii*P_ncols*P_ncols;
double *t20 = t10 + i;
double *t21 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].__m2177 = __m2177;
predict_0[disp].t20 = t20;
predict_0[disp].t22 = t22;
predict_0[disp].__s2176 = __s2176;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2177; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2177,ii+=1) {
// 2_1
int __m2177 = i + __s2177 > P_ncols ? P_ncols - i : __s2177;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2176) {
int __m2176 = __j + __s2176 > P_ncols ? P_ncols - __j : __s2176;
for (__k = 0; __k < __m2176; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t68[__j*P_ncols+__k*P_ncols+__l] = t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2176) {
int __m2176 = __j + __s2176 > P_ncols ? P_ncols - __j : __s2176;
for (__k = 0; __k < __m2176; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t68[__j*P_ncols+__k*P_ncols+__l] += t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2179);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2179);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2179,ii+=1) {
// 4_1
int __m2179 = i + __s2179 > P_ncols ? P_ncols - i : __s2179;
double *t26 = t27 + ii*P_ncols*P_ncols;
double *t24 = t14 + i;
double *t32 = t16 + i;
predict_1[disp].__m2179 = __m2179;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t32 = t32;
predict_1[disp].t24 = t24;
predict_1[disp].t26 = t26;
predict_1[disp].__s2178 = __s2178;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2179; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2179,ii+=1) {
// 4_1
int __m2179 = i + __s2179 > P_ncols ? P_ncols - i : __s2179;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2178) {
int __m2178 = __j + __s2178 > P_ncols ? P_ncols - __j : __s2178;
for (__k = 0; __k < __m2178; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] = t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2178) {
int __m2178 = __j + __s2178 > P_ncols ? P_ncols - __j : __s2178;
for (__k = 0; __k < __m2178; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] += t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s2180) {
// 6_1
int __m2180 = i + __s2180 > P_ncols ? P_ncols - i : __s2180;
double *t30 = P + i*P_ncols;
double *t28 = t17 + i*P_ncols;
double *t29 = Q + i*P_ncols;
for (j=0; j<__m2180; j+=1) {
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
free(t23);
}
