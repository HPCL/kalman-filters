#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t32;
double *t31;
double *t33;
int __s2190;
int __m2191;
} predict_2_msg_t;

typedef struct { 
int __m2189;
int P_ncols;
double *t35;
double *t27;
double *t29;
int __s2188;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t24;
int __m2187;
double *t23;
double *t25;
int __s2186;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t24 = msg->t24;
int __m2187 = msg->__m2187;
double *t23 = msg->t23;
double *t25 = msg->t25;
int __s2186 = msg->__s2186;

for (j=0; j<P_ncols; j+=__s2186) {
// 2_2
int __m2186 = j + __s2186 > P_ncols ? P_ncols - j : __s2186;
double *t37 = t25 + j*P_ncols;
double *t36 = t23 + j*P_ncols;
for (k=0; k<__m2186; k+=1) {
// 2_3
double *t47 = t37 + k*P_ncols;
double *t46 = t36 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t47[__zr__] = 0.0;
for (l=0; l<__m2187; l+=1) {
// 2_4
double *t57 = t24 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
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
int __m2189 = msg->__m2189;
int P_ncols = msg->P_ncols;
double *t35 = msg->t35;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s2188 = msg->__s2188;

for (j=0; j<P_ncols; j+=__s2188) {
// 4_2
int __m2188 = j + __s2188 > P_ncols ? P_ncols - j : __s2188;
double *t40 = t29 + j*P_ncols;
double *t39 = t27 + j*P_ncols;
for (k=0; k<__m2188; k+=1) {
// 4_3
double *t50 = t40 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t67 = t35 + l*P_ncols;
t50[l] = 0.0;
for (p=0; p<__m2189; p+=1) {
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
double *t32 = msg->t32;
double *t31 = msg->t31;
double *t33 = msg->t33;
int __s2190 = msg->__s2190;
int __m2191 = msg->__m2191;

for (j=0; j<__m2191; j+=__s2190) {
// 6_2
int __m2190 = j + __s2190 > __m2191 ? __m2191 - j : __s2190;
double *t44 = t33 + j*P_ncols;
double *t42 = t31 + j*P_ncols;
double *t43 = t32 + j*P_ncols;
for (k=0; k<__m2190; k+=1) {
// 6_3
double *t54 = t44 + k*P_ncols;
double *t52 = t42 + k*P_ncols;
double *t53 = t43 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
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

int __s2190 = 512;

int __s2188 = 512;

int __s2186 = 504;

int nparts__s2191 = 12;
int __s2191;
if (nparts__s2191 > 1 && P_ncols > nparts__s2191) {
__s2191 = P_ncols/nparts__s2191;
// this will fail if P_ncols%nparts__s2191+__s2191 > nparts__s2191
// which primarily effects small sizes
if (P_ncols%nparts__s2191)
++__s2191;
}
else {
__s2191 = P_ncols;
nparts__s2191 = 1;
}

int nparts__s2187 = 12;
int __s2187;
if (nparts__s2187 > 1 && P_ncols > nparts__s2187) {
__s2187 = P_ncols/nparts__s2187;
// this will fail if P_ncols%nparts__s2187+__s2187 > nparts__s2187
// which primarily effects small sizes
if (P_ncols%nparts__s2187)
++__s2187;
}
else {
__s2187 = P_ncols;
nparts__s2187 = 1;
}

int nparts__s2189 = 12;
int __s2189;
if (nparts__s2189 > 1 && P_ncols > nparts__s2189) {
__s2189 = P_ncols/nparts__s2189;
// this will fail if P_ncols%nparts__s2189+__s2189 > nparts__s2189
// which primarily effects small sizes
if (P_ncols%nparts__s2189)
++__s2189;
}
else {
__s2189 = P_ncols;
nparts__s2189 = 1;
}

double *t30 = malloc(sizeof(double)*nparts__s2189*P_ncols*P_ncols);
double *t26 = malloc(sizeof(double)*nparts__s2187*P_ncols*P_ncols);
double *t20 = t30;
double *t17 = t30;
double *t13 = t30;
double *t76 = t30;
double *t14 = t26;
double *t12 = t26;
double *t9 = t26;
double *t75 = t26;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2187);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2187);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2187,ii+=1) {
// 2_1
int __m2187 = i + __s2187 > P_ncols ? P_ncols - i : __s2187;
double *t25 = t26 + ii*P_ncols*P_ncols;
double *t23 = t10 + i;
double *t24 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t24 = t24;
predict_0[disp].__m2187 = __m2187;
predict_0[disp].t23 = t23;
predict_0[disp].t25 = t25;
predict_0[disp].__s2186 = __s2186;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2187; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2187,ii+=1) {
// 2_1
int __m2187 = i + __s2187 > P_ncols ? P_ncols - i : __s2187;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2186) {
int __m2186 = __j + __s2186 > P_ncols ? P_ncols - __j : __s2186;
for (__k = 0; __k < __m2186; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t75[__j*P_ncols+__k*P_ncols+__l] = t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2186) {
int __m2186 = __j + __s2186 > P_ncols ? P_ncols - __j : __s2186;
for (__k = 0; __k < __m2186; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t75[__j*P_ncols+__k*P_ncols+__l] += t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2189);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2189);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2189,ii+=1) {
// 4_1
int __m2189 = i + __s2189 > P_ncols ? P_ncols - i : __s2189;
double *t29 = t30 + ii*P_ncols*P_ncols;
double *t27 = t14 + i;
double *t35 = t16 + i;
predict_1[disp].__m2189 = __m2189;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t35 = t35;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s2188 = __s2188;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2189; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2189,ii+=1) {
// 4_1
int __m2189 = i + __s2189 > P_ncols ? P_ncols - i : __s2189;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2188) {
int __m2188 = __j + __s2188 > P_ncols ? P_ncols - __j : __s2188;
for (__k = 0; __k < __m2188; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t76[__j*P_ncols+__k*P_ncols+__l] = t30[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2188) {
int __m2188 = __j + __s2188 > P_ncols ? P_ncols - __j : __s2188;
for (__k = 0; __k < __m2188; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t76[__j*P_ncols+__k*P_ncols+__l] += t30[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s2191);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s2191);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2191,ii+=1) {
// 6_1
int __m2191 = i + __s2191 > P_ncols ? P_ncols - i : __s2191;
double *t33 = P + i*P_ncols;
double *t31 = t20 + i*P_ncols;
double *t32 = Q + i*P_ncols;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t32 = t32;
predict_2[disp].t31 = t31;
predict_2[disp].t33 = t33;
predict_2[disp].__s2190 = __s2190;
predict_2[disp].__m2191 = __m2191;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s2191; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t30);
free(t26);
}
