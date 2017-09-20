#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m1725;
int P_ncols;
double *t30;
double *t29;
double *t31;
int __s1724;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *t33;
int __m1723;
double *t12;
double *t27;
int __s1722;
} predict_1_msg_t;

typedef struct { 
int __m1721;
int P_ncols;
double *t23;
double *t8;
double *t24;
int __s1720;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m1721 = msg->__m1721;
int P_ncols = msg->P_ncols;
double *t23 = msg->t23;
double *t8 = msg->t8;
double *t24 = msg->t24;
int __s1720 = msg->__s1720;

for (j=0; j<P_ncols; j+=__s1720) {
// 2_2
int __m1720 = j + __s1720 > P_ncols ? P_ncols - j : __s1720;
double *t35 = t24 + j*P_ncols;
double *t34 = t8 + j*P_ncols;
for (k=0; k<__m1720; k+=1) {
// 2_3
double *t45 = t35 + k*P_ncols;
double *t44 = t34 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m1721; ++__zr__) t45[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t55 = t23 + l*P_ncols;
for (p=0; p<__m1721; p+=1) {
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
double *t33 = msg->t33;
int __m1723 = msg->__m1723;
double *t12 = msg->t12;
double *t27 = msg->t27;
int __s1722 = msg->__s1722;

for (j=0; j<P_ncols; j+=__s1722) {
// 4_2
int __m1722 = j + __s1722 > P_ncols ? P_ncols - j : __s1722;
double *t38 = t27 + j*P_ncols;
double *t37 = t12 + j*P_ncols;
for (k=0; k<__m1722; k+=1) {
// 4_3
double *t48 = t38 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
for (l=0; l<__m1723; l+=1) {
// 4_4
double *t65 = t33 + l*P_ncols;
t48[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t48[l] += (t47[p]*t65[p]);
}
}
}
}
return NULL;
}


void *predict_body_2(void *mesg) {
int disp, __zr__,j,k,l;
predict_2_msg_t *msg = (predict_2_msg_t*)mesg;
int __m1725 = msg->__m1725;
int P_ncols = msg->P_ncols;
double *t30 = msg->t30;
double *t29 = msg->t29;
double *t31 = msg->t31;
int __s1724 = msg->__s1724;

for (j=0; j<P_ncols; j+=__s1724) {
// 6_2
int __m1724 = j + __s1724 > P_ncols ? P_ncols - j : __s1724;
double *t42 = t31 + j*P_ncols;
double *t40 = t29 + j*P_ncols;
double *t41 = t30 + j*P_ncols;
for (k=0; k<__m1724; k+=1) {
// 6_3
double *t52 = t42 + k*P_ncols;
double *t50 = t40 + k*P_ncols;
double *t51 = t41 + k*P_ncols;
for (l=0; l<__m1725; l+=1) {
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
int disp, __zr__,i,ii;

int __s1724 = 512;

int __s1722 = 512;

int __s1720 = 512;

int nparts__s1721 = 12;
int __s1721;
if (nparts__s1721 > 1 && P_ncols > nparts__s1721) {
__s1721 = P_ncols/nparts__s1721;
// this will fail if P_ncols%nparts__s1721+__s1721 > nparts__s1721
// which primarily effects small sizes
if (P_ncols%nparts__s1721)
++__s1721;
}
else {
__s1721 = P_ncols;
nparts__s1721 = 1;
}

int nparts__s1723 = 12;
int __s1723;
if (nparts__s1723 > 1 && P_ncols > nparts__s1723) {
__s1723 = P_ncols/nparts__s1723;
// this will fail if P_ncols%nparts__s1723+__s1723 > nparts__s1723
// which primarily effects small sizes
if (P_ncols%nparts__s1723)
++__s1723;
}
else {
__s1723 = P_ncols;
nparts__s1723 = 1;
}

int nparts__s1725 = 12;
int __s1725;
if (nparts__s1725 > 1 && P_ncols > nparts__s1725) {
__s1725 = P_ncols/nparts__s1725;
// this will fail if P_ncols%nparts__s1725+__s1725 > nparts__s1725
// which primarily effects small sizes
if (P_ncols%nparts__s1725)
++__s1725;
}
else {
__s1725 = P_ncols;
nparts__s1725 = 1;
}

double *t28 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = t28;
double *t17 = t28;
double *t13 = t28;
double *t15 = t28;
double *t12 = t25;
double *t9 = t25;
double *t11 = t25;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1721);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1721);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1721,ii+=1) {
// 2_1
int __m1721 = i + __s1721 > P_ncols ? P_ncols - i : __s1721;
double *t24 = t25 + i;
double *t23 = P + i;
predict_0[disp].__m1721 = __m1721;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t23 = t23;
predict_0[disp].t8 = t8;
predict_0[disp].t24 = t24;
predict_0[disp].__s1720 = __s1720;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1721; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1723);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1723);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1723,ii+=1) {
// 4_1
int __m1723 = i + __s1723 > P_ncols ? P_ncols - i : __s1723;
double *t27 = t28 + i;
double *t33 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t33 = t33;
predict_1[disp].__m1723 = __m1723;
predict_1[disp].t12 = t12;
predict_1[disp].t27 = t27;
predict_1[disp].__s1722 = __s1722;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1723; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s1725);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s1725);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1725,ii+=1) {
// 6_1
int __m1725 = i + __s1725 > P_ncols ? P_ncols - i : __s1725;
double *t31 = P + i;
double *t29 = t20 + i;
double *t30 = Q + i;
predict_2[disp].__m1725 = __m1725;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t30 = t30;
predict_2[disp].t29 = t29;
predict_2[disp].t31 = t31;
predict_2[disp].__s1724 = __s1724;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s1725; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t28);
free(t25);
}
