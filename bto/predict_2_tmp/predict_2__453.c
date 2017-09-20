#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t29;
double *t28;
double *t30;
int __s1196;
int __m1197;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t22;
int __m1194;
double *t21;
double *t23;
int __s1193;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t22 = msg->t22;
int __m1194 = msg->__m1194;
double *t21 = msg->t21;
double *t23 = msg->t23;
int __s1193 = msg->__s1193;

for (j=0; j<P_ncols; j+=__s1193) {
// 2_2
int __m1193 = j + __s1193 > P_ncols ? P_ncols - j : __s1193;
double *t34 = t23 + j*P_ncols;
double *t33 = t21 + j*P_ncols;
for (k=0; k<__m1193; k+=1) {
// 2_3
double *t44 = t34 + k*P_ncols;
double *t43 = t33 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t44[__zr__] = 0.0;
for (l=0; l<__m1194; l+=1) {
// 2_4
double *t55 = t22 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t44[p] += (t43[l]*t55[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t28 = msg->t28;
double *t30 = msg->t30;
int __s1196 = msg->__s1196;
int __m1197 = msg->__m1197;

for (j=0; j<__m1197; j+=__s1196) {
// 6_2
int __m1196 = j + __s1196 > __m1197 ? __m1197 - j : __s1196;
double *t41 = t30 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
double *t40 = t29 + j*P_ncols;
for (k=0; k<__m1196; k+=1) {
// 6_3
double *t51 = t41 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
double *t50 = t40 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 6_4
t51[l] = (t49[l]+t50[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s1196 = 512;

int __s1195 = 12;

int __s1193 = 504;

int nparts__s1197 = 12;
int __s1197;
if (nparts__s1197 > 1 && P_ncols > nparts__s1197) {
__s1197 = P_ncols/nparts__s1197;
// this will fail if P_ncols%nparts__s1197+__s1197 > nparts__s1197
// which primarily effects small sizes
if (P_ncols%nparts__s1197)
++__s1197;
}
else {
__s1197 = P_ncols;
nparts__s1197 = 1;
}

int nparts__s1194 = 12;
int __s1194;
if (nparts__s1194 > 1 && P_ncols > nparts__s1194) {
__s1194 = P_ncols/nparts__s1194;
// this will fail if P_ncols%nparts__s1194+__s1194 > nparts__s1194
// which primarily effects small sizes
if (P_ncols%nparts__s1194)
++__s1194;
}
else {
__s1194 = P_ncols;
nparts__s1194 = 1;
}

double *t27 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t24 = malloc(sizeof(double)*nparts__s1194*P_ncols*P_ncols);
double *t18 = t27;
double *t15 = t27;
double *t13 = t27;
double *t9 = t24;
double *t69 = t24;
double *t10 = A;
double *t8 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1194);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1194);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1194,ii+=1) {
// 2_1
int __m1194 = i + __s1194 > P_ncols ? P_ncols - i : __s1194;
double *t23 = t24 + ii*P_ncols*P_ncols;
double *t21 = t10 + i;
double *t22 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t22 = t22;
predict_0[disp].__m1194 = __m1194;
predict_0[disp].t21 = t21;
predict_0[disp].t23 = t23;
predict_0[disp].__s1193 = __s1193;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1194; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1194,ii+=1) {
// 2_1
int __m1194 = i + __s1194 > P_ncols ? P_ncols - i : __s1194;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1193) {
int __m1193 = __j + __s1193 > P_ncols ? P_ncols - __j : __s1193;
for (__k = 0; __k < __m1193; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] = t24[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1193) {
int __m1193 = __j + __s1193 > P_ncols ? P_ncols - __j : __s1193;
for (__k = 0; __k < __m1193; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] += t24[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s1195) {
// 4_1
int __m1195 = i + __s1195 > P_ncols ? P_ncols - i : __s1195;
double *t26 = t27 + i;
double *t32 = t14 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t37 = t26 + j*P_ncols;
double *t36 = t9 + j*P_ncols;
for (k=0; k<__m1195; k+=1) {
// 4_3
double *t53 = t32 + k*P_ncols;
t37[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t37[k] += (t36[l]*t53[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1197);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1197);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1197,ii+=1) {
// 6_1
int __m1197 = i + __s1197 > P_ncols ? P_ncols - i : __s1197;
double *t30 = P + i*P_ncols;
double *t28 = t18 + i*P_ncols;
double *t29 = Q + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t29 = t29;
predict_1[disp].t28 = t28;
predict_1[disp].t30 = t30;
predict_1[disp].__s1196 = __s1196;
predict_1[disp].__m1197 = __m1197;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1197; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t27);
free(t24);
}
