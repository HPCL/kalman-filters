#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t30;
double *t29;
double *t31;
int __s833;
int __m834;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
int __m832;
double *t27;
double *t33;
double *t10;
int __s831;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m832 = msg->__m832;
double *t27 = msg->t27;
double *t33 = msg->t33;
double *t10 = msg->t10;
int __s831 = msg->__s831;

for (j=0; j<P_ncols; j+=__s831) {
// 4_2
int __m831 = j + __s831 > P_ncols ? P_ncols - j : __s831;
double *t37 = t10 + j;
double *t45 = t33 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t51 = t27 + k*P_ncols;
double *t50 = t37 + k*P_ncols;
for (l=0; l<__m832; l+=1) {
// 4_4
double *t67 = t45 + l*P_ncols;
t51[l] = 0.0;
for (p=0; p<__m831; p+=1) {
// 4_5
t51[l] += (t50[p]*t67[p]);
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
double *t30 = msg->t30;
double *t29 = msg->t29;
double *t31 = msg->t31;
int __s833 = msg->__s833;
int __m834 = msg->__m834;

for (j=0; j<__m834; j+=__s833) {
// 6_2
int __m833 = j + __s833 > __m834 ? __m834 - j : __s833;
double *t43 = t31 + j*P_ncols;
double *t41 = t29 + j*P_ncols;
double *t42 = t30 + j*P_ncols;
for (k=0; k<__m833; k+=1) {
// 6_3
double *t55 = t43 + k*P_ncols;
double *t53 = t41 + k*P_ncols;
double *t54 = t42 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
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
int disp, __zr__,i,ii,j,k,l;

int __s833 = 512;

int __s831 = 512;

int __s830 = 12;

int nparts__s834 = 12;
int __s834;
if (nparts__s834 > 1 && P_ncols > nparts__s834) {
__s834 = P_ncols/nparts__s834;
// this will fail if P_ncols%nparts__s834+__s834 > nparts__s834
// which primarily effects small sizes
if (P_ncols%nparts__s834)
++__s834;
}
else {
__s834 = P_ncols;
nparts__s834 = 1;
}

int nparts__s832 = 12;
int __s832;
if (nparts__s832 > 1 && P_ncols > nparts__s832) {
__s832 = P_ncols/nparts__s832;
// this will fail if P_ncols%nparts__s832+__s832 > nparts__s832
// which primarily effects small sizes
if (P_ncols%nparts__s832)
++__s832;
}
else {
__s832 = P_ncols;
nparts__s832 = 1;
}

double *t28 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = t28;
double *t16 = t28;
double *t14 = t28;
double *t10 = t25;
double *t8 = A;
double *t15 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s830) {
// 2_1
int __m830 = i + __s830 > P_ncols ? P_ncols - i : __s830;
double *t22 = t8 + i;
double *t23 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t35 = t25 + j*P_ncols;
double *t34 = t22 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t35[__zr__] = 0.0;
for (k=0; k<__m830; k+=1) {
// 2_3
double *t47 = t23 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t35[l] += (t34[k]*t47[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s832);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s832);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s832,ii+=1) {
// 4_1
int __m832 = i + __s832 > P_ncols ? P_ncols - i : __s832;
double *t27 = t28 + i;
double *t33 = t15 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m832 = __m832;
predict_0[disp].t27 = t27;
predict_0[disp].t33 = t33;
predict_0[disp].t10 = t10;
predict_0[disp].__s831 = __s831;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s832; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s834);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s834);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s834,ii+=1) {
// 6_1
int __m834 = i + __s834 > P_ncols ? P_ncols - i : __s834;
double *t31 = P + i*P_ncols;
double *t29 = t19 + i*P_ncols;
double *t30 = Q + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t30 = t30;
predict_1[disp].t29 = t29;
predict_1[disp].t31 = t31;
predict_1[disp].__s833 = __s833;
predict_1[disp].__m834 = __m834;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s834; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t28);
free(t25);
}
