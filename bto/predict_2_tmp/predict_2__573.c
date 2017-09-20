#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m1444;
int P_ncols;
double *t30;
double *t31;
int __s1445;
double *t33;
double *t12;
int __s1443;
int __s1444;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t23;
double *t24;
int __s1441;
int __m1442;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t23 = msg->t23;
double *t24 = msg->t24;
int __s1441 = msg->__s1441;
int __m1442 = msg->__m1442;

for (j=0; j<__m1442; j+=__s1441) {
// 2_2
int __m1441 = j + __s1441 > __m1442 ? __m1442 - j : __s1441;
double *t35 = t24 + j;
double *t34 = t23 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t45 = t35 + k*P_ncols;
double *t44 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m1441; ++__zr__) t45[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t55 = t34 + l*P_ncols;
for (p=0; p<__m1441; p+=1) {
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
int __m1444 = msg->__m1444;
int P_ncols = msg->P_ncols;
double *t30 = msg->t30;
double *t31 = msg->t31;
int __s1445 = msg->__s1445;
double *t33 = msg->t33;
double *t12 = msg->t12;
int __s1443 = msg->__s1443;
int __s1444 = msg->__s1444;

double *t27 = malloc(sizeof(double)*P_ncols*__s1444);
for (j=0; j<P_ncols; j+=__s1443) {
// 4_2
int __m1443 = j + __s1443 > P_ncols ? P_ncols - j : __s1443;
double *t38 = t27 + j*__m1444;
double *t37 = t12 + j*P_ncols;
for (k=0; k<__m1443; k+=1) {
// 4_3
double *t48 = t38 + k*__m1444;
double *t47 = t37 + k*P_ncols;
for (l=0; l<__m1444; l+=1) {
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
for (j=0; j<P_ncols; j+=__s1445) {
// 6_2
int __m1445 = j + __s1445 > P_ncols ? P_ncols - j : __s1445;
double *t42 = t31 + j*P_ncols;
double *t40 = t27 + j*__m1444;
double *t41 = t30 + j*P_ncols;
for (k=0; k<__m1445; k+=1) {
// 6_3
double *t52 = t42 + k*P_ncols;
double *t50 = t40 + k*__m1444;
double *t51 = t41 + k*P_ncols;
for (l=0; l<__m1444; l+=1) {
// 6_4
t52[l] = (t50[l]+t51[l]);
}
}
}
free(t27);
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s1445 = 512;

int __s1443 = 512;

int __s1441 = 512;

int nparts__s1442 = 10;
int __s1442;
if (nparts__s1442 > 1 && P_ncols > nparts__s1442) {
__s1442 = P_ncols/nparts__s1442;
// this will fail if P_ncols%nparts__s1442+__s1442 > nparts__s1442
// which primarily effects small sizes
if (P_ncols%nparts__s1442)
++__s1442;
}
else {
__s1442 = P_ncols;
nparts__s1442 = 1;
}

int nparts__s1444 = 10;
int __s1444;
if (nparts__s1444 > 1 && P_ncols > nparts__s1444) {
__s1444 = P_ncols/nparts__s1444;
// this will fail if P_ncols%nparts__s1444+__s1444 > nparts__s1444
// which primarily effects small sizes
if (P_ncols%nparts__s1444)
++__s1444;
}
else {
__s1444 = P_ncols;
nparts__s1444 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = A;
double *t12 = t25;
double *t9 = t25;
double *t11 = t25;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1442);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1442);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1442,ii+=1) {
// 2_1
int __m1442 = i + __s1442 > P_ncols ? P_ncols - i : __s1442;
double *t24 = t25 + i;
double *t23 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t23 = t23;
predict_0[disp].t24 = t24;
predict_0[disp].__s1441 = __s1441;
predict_0[disp].__m1442 = __m1442;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1442; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1444);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1444);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1444,ii+=1) {
// 4_1
int __m1444 = i + __s1444 > P_ncols ? P_ncols - i : __s1444;
double *t31 = P + i;
double *t33 = t16 + i*P_ncols;
double *t30 = Q + i;
predict_1[disp].__m1444 = __m1444;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t30 = t30;
predict_1[disp].t31 = t31;
predict_1[disp].__s1445 = __s1445;
predict_1[disp].t33 = t33;
predict_1[disp].t12 = t12;
predict_1[disp].__s1443 = __s1443;
predict_1[disp].__s1444 = __s1444;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1444; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t25);
}
