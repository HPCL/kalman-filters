#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m418;
int P_ncols;
double *t29;
double *t28;
double *t30;
int __s417;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t22;
int __m415;
double *P;
double *t21;
int __s414;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t22 = msg->t22;
int __m415 = msg->__m415;
double *P = msg->P;
double *t21 = msg->t21;
int __s414 = msg->__s414;

for (j=0; j<P_ncols; j+=__s414) {
// 2_2
int __m414 = j + __s414 > P_ncols ? P_ncols - j : __s414;
double *t33 = t21 + j;
double *t34 = P + j*P_ncols;
for (k=0; k<__m415; k+=1) {
// 2_3
double *t45 = t22 + k*P_ncols;
double *t44 = t33 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t45[__zr__] = 0.0;
for (l=0; l<__m414; l+=1) {
// 2_4
double *t56 = t34 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t45[p] += (t44[l]*t56[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m418 = msg->__m418;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t28 = msg->t28;
double *t30 = msg->t30;
int __s417 = msg->__s417;

for (j=0; j<P_ncols; j+=__s417) {
// 6_2
int __m417 = j + __s417 > P_ncols ? P_ncols - j : __s417;
double *t42 = t30 + j*P_ncols;
double *t40 = t28 + j*P_ncols;
double *t41 = t29 + j*P_ncols;
for (k=0; k<__m417; k+=1) {
// 6_3
double *t52 = t42 + k*P_ncols;
double *t50 = t40 + k*P_ncols;
double *t51 = t41 + k*P_ncols;
for (l=0; l<__m418; l+=1) {
// 6_4
t52[l] = (t50[l]+t51[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s417 = 512;

int __s416 = 10;

int __s414 = 512;

int nparts__s415 = 10;
int __s415;
if (nparts__s415 > 1 && P_ncols > nparts__s415) {
__s415 = P_ncols/nparts__s415;
// this will fail if P_ncols%nparts__s415+__s415 > nparts__s415
// which primarily effects small sizes
if (P_ncols%nparts__s415)
++__s415;
}
else {
__s415 = P_ncols;
nparts__s415 = 1;
}

int nparts__s418 = 10;
int __s418;
if (nparts__s418 > 1 && P_ncols > nparts__s418) {
__s418 = P_ncols/nparts__s418;
// this will fail if P_ncols%nparts__s418+__s418 > nparts__s418
// which primarily effects small sizes
if (P_ncols%nparts__s418)
++__s418;
}
else {
__s418 = P_ncols;
nparts__s418 = 1;
}

double *t27 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t27;
double *t15 = t27;
double *t12 = t23;
double *t11 = t23;
double *t10 = A;
double *t8 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s415);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s415);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s415,ii+=1) {
// 2_1
int __m415 = i + __s415 > P_ncols ? P_ncols - i : __s415;
double *t22 = t23 + i*P_ncols;
double *t21 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t22 = t22;
predict_0[disp].__m415 = __m415;
predict_0[disp].P = P;
predict_0[disp].t21 = t21;
predict_0[disp].__s414 = __s414;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s415; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s416) {
// 4_1
int __m416 = i + __s416 > P_ncols ? P_ncols - i : __s416;
double *t24 = t12 + i;
double *t32 = t14 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t38 = t27 + j*P_ncols;
double *t37 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t54 = t32 + k*P_ncols;
t38[k] = 0.0;
for (l=0; l<__m416; l+=1) {
// 4_4
t38[k] += (t37[l]*t54[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s418);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s418);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s418,ii+=1) {
// 6_1
int __m418 = i + __s418 > P_ncols ? P_ncols - i : __s418;
double *t30 = P + i;
double *t28 = t18 + i;
double *t29 = Q + i;
predict_1[disp].__m418 = __m418;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t29 = t29;
predict_1[disp].t28 = t28;
predict_1[disp].t30 = t30;
predict_1[disp].__s417 = __s417;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s418; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t27);
free(t23);
}
