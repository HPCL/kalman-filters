#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2752;
int P_ncols;
double *t28;
double *t27;
double *t29;
int __s2751;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t31;
int __m2750;
double *t10;
double *t25;
int __s2749;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t31 = msg->t31;
int __m2750 = msg->__m2750;
double *t10 = msg->t10;
double *t25 = msg->t25;
int __s2749 = msg->__s2749;

for (j=0; j<P_ncols; j+=__s2749) {
// 4_2
int __m2749 = j + __s2749 > P_ncols ? P_ncols - j : __s2749;
double *t36 = t25 + j*P_ncols;
double *t35 = t10 + j*P_ncols;
for (k=0; k<__m2749; k+=1) {
// 4_3
double *t47 = t36 + k*P_ncols;
double *t46 = t35 + k*P_ncols;
for (l=0; l<__m2750; l+=1) {
// 4_4
double *t63 = t31 + l*P_ncols;
t47[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t47[l] += (t46[p]*t63[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m2752 = msg->__m2752;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s2751 = msg->__s2751;

for (j=0; j<P_ncols; j+=__s2751) {
// 6_2
int __m2751 = j + __s2751 > P_ncols ? P_ncols - j : __s2751;
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m2751; k+=1) {
// 6_3
double *t51 = t40 + k*P_ncols;
double *t49 = t38 + k*P_ncols;
double *t50 = t39 + k*P_ncols;
for (l=0; l<__m2752; l+=1) {
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

int __s2751 = 504;

int __s2749 = 504;

int __s2748 = 2;

int nparts__s2750 = 10;
int __s2750;
if (nparts__s2750 > 1 && P_ncols > nparts__s2750) {
__s2750 = P_ncols/nparts__s2750;
// this will fail if P_ncols%nparts__s2750+__s2750 > nparts__s2750
// which primarily effects small sizes
if (P_ncols%nparts__s2750)
++__s2750;
}
else {
__s2750 = P_ncols;
nparts__s2750 = 1;
}

int nparts__s2752 = 10;
int __s2752;
if (nparts__s2752 > 1 && P_ncols > nparts__s2752) {
__s2752 = P_ncols/nparts__s2752;
// this will fail if P_ncols%nparts__s2752+__s2752 > nparts__s2752
// which primarily effects small sizes
if (P_ncols%nparts__s2752)
++__s2752;
}
else {
__s2752 = P_ncols;
nparts__s2752 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t26;
double *t15 = t26;
double *t11 = t26;
double *t13 = t26;
double *t10 = t23;
double *t9 = t23;
double *t8 = A;
double *t14 = A;
for (i=0; i<P_ncols; i+=__s2748) {
// 2_1
int __m2748 = i + __s2748 > P_ncols ? P_ncols - i : __s2748;
double *t22 = t23 + i*P_ncols;
double *t21 = t8 + i*P_ncols;
for (j=0; j<__m2748; j+=1) {
// 2_2
double *t33 = t22 + j*P_ncols;
double *t32 = t21 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t33[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t43 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t33[l] += (t32[k]*t43[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2750);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2750);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2750,ii+=1) {
// 4_1
int __m2750 = i + __s2750 > P_ncols ? P_ncols - i : __s2750;
double *t25 = t26 + i;
double *t31 = t14 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t31 = t31;
predict_0[disp].__m2750 = __m2750;
predict_0[disp].t10 = t10;
predict_0[disp].t25 = t25;
predict_0[disp].__s2749 = __s2749;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2750; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2752);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2752);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2752,ii+=1) {
// 6_1
int __m2752 = i + __s2752 > P_ncols ? P_ncols - i : __s2752;
double *t29 = P + i;
double *t27 = t18 + i;
double *t28 = Q + i;
predict_1[disp].__m2752 = __m2752;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s2751 = __s2751;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2752; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t26);
free(t23);
}
