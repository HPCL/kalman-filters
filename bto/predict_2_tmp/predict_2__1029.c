#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m2635;
double *t32;
double *t31;
double *t33;
int __s2634;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
int __m2633;
double *t29;
double *t35;
double *t12;
int __s2632;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t25;
int __m2631;
double *t24;
double *t26;
int __s2630;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t25 = msg->t25;
int __m2631 = msg->__m2631;
double *t24 = msg->t24;
double *t26 = msg->t26;
int __s2630 = msg->__s2630;

for (j=0; j<P_ncols; j+=__s2630) {
// 2_2
int __m2630 = j + __s2630 > P_ncols ? P_ncols - j : __s2630;
double *t37 = t26 + j*P_ncols;
double *t36 = t24 + j*P_ncols;
for (k=0; k<__m2630; k+=1) {
// 2_3
double *t49 = t37 + k*P_ncols;
double *t48 = t36 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t49[__zr__] = 0.0;
for (l=0; l<__m2631; l+=1) {
// 2_4
double *t59 = t25 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t49[p] += (t48[l]*t59[p]);
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
int __m2633 = msg->__m2633;
double *t29 = msg->t29;
double *t35 = msg->t35;
double *t12 = msg->t12;
int __s2632 = msg->__s2632;

for (j=0; j<P_ncols; j+=__s2632) {
// 4_2
int __m2632 = j + __s2632 > P_ncols ? P_ncols - j : __s2632;
double *t39 = t12 + j;
double *t47 = t35 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t52 = t29 + k*P_ncols;
double *t51 = t39 + k*P_ncols;
for (l=0; l<__m2633; l+=1) {
// 4_4
double *t69 = t47 + l*P_ncols;
t52[l] = 0.0;
for (p=0; p<__m2632; p+=1) {
// 4_5
t52[l] += (t51[p]*t69[p]);
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
int __m2635 = msg->__m2635;
double *t32 = msg->t32;
double *t31 = msg->t31;
double *t33 = msg->t33;
int __s2634 = msg->__s2634;

for (j=0; j<P_ncols; j+=__s2634) {
// 6_2
int __m2634 = j + __s2634 > P_ncols ? P_ncols - j : __s2634;
double *t45 = t33 + j;
double *t43 = t31 + j;
double *t44 = t32 + j;
for (k=0; k<__m2635; k+=1) {
// 6_3
double *t56 = t45 + k*P_ncols;
double *t54 = t43 + k*P_ncols;
double *t55 = t44 + k*P_ncols;
for (l=0; l<__m2634; l+=1) {
// 6_4
t56[l] = (t54[l]+t55[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s2634 = 512;

int __s2632 = 504;

int __s2630 = 512;

int nparts__s2631 = 10;
int __s2631;
if (nparts__s2631 > 1 && P_ncols > nparts__s2631) {
__s2631 = P_ncols/nparts__s2631;
// this will fail if P_ncols%nparts__s2631+__s2631 > nparts__s2631
// which primarily effects small sizes
if (P_ncols%nparts__s2631)
++__s2631;
}
else {
__s2631 = P_ncols;
nparts__s2631 = 1;
}

int nparts__s2633 = 12;
int __s2633;
if (nparts__s2633 > 1 && P_ncols > nparts__s2633) {
__s2633 = P_ncols/nparts__s2633;
// this will fail if P_ncols%nparts__s2633+__s2633 > nparts__s2633
// which primarily effects small sizes
if (P_ncols%nparts__s2633)
++__s2633;
}
else {
__s2633 = P_ncols;
nparts__s2633 = 1;
}

int nparts__s2635 = 10;
int __s2635;
if (nparts__s2635 > 1 && P_ncols > nparts__s2635) {
__s2635 = P_ncols/nparts__s2635;
// this will fail if P_ncols%nparts__s2635+__s2635 > nparts__s2635
// which primarily effects small sizes
if (P_ncols%nparts__s2635)
++__s2635;
}
else {
__s2635 = P_ncols;
nparts__s2635 = 1;
}

double *t30 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t27 = malloc(sizeof(double)*nparts__s2631*P_ncols*P_ncols);
double *t21 = t30;
double *t18 = t30;
double *t16 = t30;
double *t12 = t27;
double *t9 = t27;
double *t77 = t27;
double *t10 = A;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2631);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2631);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2631,ii+=1) {
// 2_1
int __m2631 = i + __s2631 > P_ncols ? P_ncols - i : __s2631;
double *t26 = t27 + ii*P_ncols*P_ncols;
double *t24 = t10 + i;
double *t25 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t25 = t25;
predict_0[disp].__m2631 = __m2631;
predict_0[disp].t24 = t24;
predict_0[disp].t26 = t26;
predict_0[disp].__s2630 = __s2630;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2631; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2631,ii+=1) {
// 2_1
int __m2631 = i + __s2631 > P_ncols ? P_ncols - i : __s2631;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2630) {
int __m2630 = __j + __s2630 > P_ncols ? P_ncols - __j : __s2630;
for (__k = 0; __k < __m2630; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t77[__j*P_ncols+__k*P_ncols+__l] = t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2630) {
int __m2630 = __j + __s2630 > P_ncols ? P_ncols - __j : __s2630;
for (__k = 0; __k < __m2630; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t77[__j*P_ncols+__k*P_ncols+__l] += t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2633);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2633);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2633,ii+=1) {
// 4_1
int __m2633 = i + __s2633 > P_ncols ? P_ncols - i : __s2633;
double *t29 = t30 + i;
double *t35 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m2633 = __m2633;
predict_1[disp].t29 = t29;
predict_1[disp].t35 = t35;
predict_1[disp].t12 = t12;
predict_1[disp].__s2632 = __s2632;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2633; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s2635);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s2635);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2635,ii+=1) {
// 6_1
int __m2635 = i + __s2635 > P_ncols ? P_ncols - i : __s2635;
double *t33 = P + i*P_ncols;
double *t31 = t21 + i*P_ncols;
double *t32 = Q + i*P_ncols;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].__m2635 = __m2635;
predict_2[disp].t32 = t32;
predict_2[disp].t31 = t31;
predict_2[disp].t33 = t33;
predict_2[disp].__s2634 = __s2634;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s2635; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t30);
free(t27);
}
