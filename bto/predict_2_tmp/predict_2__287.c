#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m822;
int P_ncols;
double *t32;
double *t31;
double *t33;
int __s821;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
int __m820;
double *t29;
double *t35;
double *t12;
int __s819;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t39;
double *t25;
double *t24;
int __s817;
int __m818;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t39 = msg->t39;
double *t25 = msg->t25;
double *t24 = msg->t24;
int __s817 = msg->__s817;
int __m818 = msg->__m818;

for (j=0; j<__m818; j+=__s817) {
// 2_2
int __m817 = j + __s817 > __m818 ? __m818 - j : __s817;
double *t36 = t24 + j;
double *t37 = t25 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t50 = t39 + k*P_ncols;
double *t49 = t36 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t50[__zr__] = 0.0;
for (l=0; l<__m817; l+=1) {
// 2_4
double *t60 = t37 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t50[p] += (t49[l]*t60[p]);
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
int __m820 = msg->__m820;
double *t29 = msg->t29;
double *t35 = msg->t35;
double *t12 = msg->t12;
int __s819 = msg->__s819;

for (j=0; j<P_ncols; j+=__s819) {
// 4_2
int __m819 = j + __s819 > P_ncols ? P_ncols - j : __s819;
double *t40 = t12 + j;
double *t48 = t35 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t53 = t29 + k*P_ncols;
double *t52 = t40 + k*P_ncols;
for (l=0; l<__m820; l+=1) {
// 4_4
double *t70 = t48 + l*P_ncols;
t53[l] = 0.0;
for (p=0; p<__m819; p+=1) {
// 4_5
t53[l] += (t52[p]*t70[p]);
}
}
}
}
return NULL;
}


void *predict_body_2(void *mesg) {
int disp, __zr__,j,k,l;
predict_2_msg_t *msg = (predict_2_msg_t*)mesg;
int __m822 = msg->__m822;
int P_ncols = msg->P_ncols;
double *t32 = msg->t32;
double *t31 = msg->t31;
double *t33 = msg->t33;
int __s821 = msg->__s821;

for (j=0; j<P_ncols; j+=__s821) {
// 6_2
int __m821 = j + __s821 > P_ncols ? P_ncols - j : __s821;
double *t46 = t33 + j*P_ncols;
double *t44 = t31 + j*P_ncols;
double *t45 = t32 + j*P_ncols;
for (k=0; k<__m821; k+=1) {
// 6_3
double *t57 = t46 + k*P_ncols;
double *t55 = t44 + k*P_ncols;
double *t56 = t45 + k*P_ncols;
for (l=0; l<__m822; l+=1) {
// 6_4
t57[l] = (t55[l]+t56[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s821 = 512;

int __s819 = 512;

int __s817 = 512;

int nparts__s818 = 12;
int __s818;
if (nparts__s818 > 1 && P_ncols > nparts__s818) {
__s818 = P_ncols/nparts__s818;
// this will fail if P_ncols%nparts__s818+__s818 > nparts__s818
// which primarily effects small sizes
if (P_ncols%nparts__s818)
++__s818;
}
else {
__s818 = P_ncols;
nparts__s818 = 1;
}

int nparts__s820 = 12;
int __s820;
if (nparts__s820 > 1 && P_ncols > nparts__s820) {
__s820 = P_ncols/nparts__s820;
// this will fail if P_ncols%nparts__s820+__s820 > nparts__s820
// which primarily effects small sizes
if (P_ncols%nparts__s820)
++__s820;
}
else {
__s820 = P_ncols;
nparts__s820 = 1;
}

int nparts__s822 = 12;
int __s822;
if (nparts__s822 > 1 && P_ncols > nparts__s822) {
__s822 = P_ncols/nparts__s822;
// this will fail if P_ncols%nparts__s822+__s822 > nparts__s822
// which primarily effects small sizes
if (P_ncols%nparts__s822)
++__s822;
}
else {
__s822 = P_ncols;
nparts__s822 = 1;
}

double *t30 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t27 = malloc(sizeof(double)*nparts__s818*P_ncols*P_ncols);
double *t21 = t30;
double *t18 = t30;
double *t16 = t30;
double *t12 = t27;
double *t78 = t27;
double *t10 = A;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s818);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s818);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s818,ii+=1) {
// 2_1
int __m818 = i + __s818 > P_ncols ? P_ncols - i : __s818;
double *t39 = t27 + ii*P_ncols*P_ncols;
double *t24 = t10 + i;
double *t25 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t39 = t39;
predict_0[disp].t25 = t25;
predict_0[disp].t24 = t24;
predict_0[disp].__s817 = __s817;
predict_0[disp].__m818 = __m818;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s818; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s818,ii+=1) {
// 2_1
int __m818 = i + __s818 > P_ncols ? P_ncols - i : __s818;
if ((ii == 0)) {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t78[__k*P_ncols+__l] = t27[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
} else {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t78[__k*P_ncols+__l] += t27[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s820);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s820);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s820,ii+=1) {
// 4_1
int __m820 = i + __s820 > P_ncols ? P_ncols - i : __s820;
double *t29 = t30 + i;
double *t35 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m820 = __m820;
predict_1[disp].t29 = t29;
predict_1[disp].t35 = t35;
predict_1[disp].t12 = t12;
predict_1[disp].__s819 = __s819;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s820; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s822);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s822);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s822,ii+=1) {
// 6_1
int __m822 = i + __s822 > P_ncols ? P_ncols - i : __s822;
double *t33 = P + i;
double *t31 = t21 + i;
double *t32 = Q + i;
predict_2[disp].__m822 = __m822;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t32 = t32;
predict_2[disp].t31 = t31;
predict_2[disp].t33 = t33;
predict_2[disp].__s821 = __s821;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s822; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t30);
free(t27);
}
