#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2657;
int P_ncols;
double *t31;
double *t30;
double *t32;
int __s2656;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *t34;
int __m2655;
double *t12;
double *t28;
int __s2654;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t24;
int __m2653;
double *t23;
double *t25;
int __s2652;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t24 = msg->t24;
int __m2653 = msg->__m2653;
double *t23 = msg->t23;
double *t25 = msg->t25;
int __s2652 = msg->__s2652;

for (j=0; j<P_ncols; j+=__s2652) {
// 2_2
int __m2652 = j + __s2652 > P_ncols ? P_ncols - j : __s2652;
double *t36 = t25 + j*P_ncols;
double *t35 = t23 + j*P_ncols;
for (k=0; k<__m2652; k+=1) {
// 2_3
double *t46 = t36 + k*P_ncols;
double *t45 = t35 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t46[__zr__] = 0.0;
for (l=0; l<__m2653; l+=1) {
// 2_4
double *t56 = t24 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t46[p] += (t45[l]*t56[p]);
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
double *t34 = msg->t34;
int __m2655 = msg->__m2655;
double *t12 = msg->t12;
double *t28 = msg->t28;
int __s2654 = msg->__s2654;

for (j=0; j<P_ncols; j+=__s2654) {
// 4_2
int __m2654 = j + __s2654 > P_ncols ? P_ncols - j : __s2654;
double *t39 = t28 + j*P_ncols;
double *t38 = t12 + j*P_ncols;
for (k=0; k<__m2654; k+=1) {
// 4_3
double *t49 = t39 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
for (l=0; l<__m2655; l+=1) {
// 4_4
double *t66 = t34 + l*P_ncols;
t49[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t49[l] += (t48[p]*t66[p]);
}
}
}
}
return NULL;
}


void *predict_body_2(void *mesg) {
int disp, __zr__,j,k,l;
predict_2_msg_t *msg = (predict_2_msg_t*)mesg;
int __m2657 = msg->__m2657;
int P_ncols = msg->P_ncols;
double *t31 = msg->t31;
double *t30 = msg->t30;
double *t32 = msg->t32;
int __s2656 = msg->__s2656;

for (j=0; j<P_ncols; j+=__s2656) {
// 6_2
int __m2656 = j + __s2656 > P_ncols ? P_ncols - j : __s2656;
double *t43 = t32 + j*P_ncols;
double *t41 = t30 + j*P_ncols;
double *t42 = t31 + j*P_ncols;
for (k=0; k<__m2656; k+=1) {
// 6_3
double *t53 = t43 + k*P_ncols;
double *t51 = t41 + k*P_ncols;
double *t52 = t42 + k*P_ncols;
for (l=0; l<__m2657; l+=1) {
// 6_4
t53[l] = (t51[l]+t52[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s2656 = 504;

int __s2654 = 504;

int __s2652 = 512;

int nparts__s2653 = 10;
int __s2653;
if (nparts__s2653 > 1 && P_ncols > nparts__s2653) {
__s2653 = P_ncols/nparts__s2653;
// this will fail if P_ncols%nparts__s2653+__s2653 > nparts__s2653
// which primarily effects small sizes
if (P_ncols%nparts__s2653)
++__s2653;
}
else {
__s2653 = P_ncols;
nparts__s2653 = 1;
}

int nparts__s2655 = 10;
int __s2655;
if (nparts__s2655 > 1 && P_ncols > nparts__s2655) {
__s2655 = P_ncols/nparts__s2655;
// this will fail if P_ncols%nparts__s2655+__s2655 > nparts__s2655
// which primarily effects small sizes
if (P_ncols%nparts__s2655)
++__s2655;
}
else {
__s2655 = P_ncols;
nparts__s2655 = 1;
}

int nparts__s2657 = 10;
int __s2657;
if (nparts__s2657 > 1 && P_ncols > nparts__s2657) {
__s2657 = P_ncols/nparts__s2657;
// this will fail if P_ncols%nparts__s2657+__s2657 > nparts__s2657
// which primarily effects small sizes
if (P_ncols%nparts__s2657)
++__s2657;
}
else {
__s2657 = P_ncols;
nparts__s2657 = 1;
}

double *t29 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t26 = malloc(sizeof(double)*nparts__s2653*P_ncols*P_ncols);
double *t20 = t29;
double *t17 = t29;
double *t13 = t29;
double *t15 = t29;
double *t12 = t26;
double *t9 = t26;
double *t74 = t26;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2653);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2653);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2653,ii+=1) {
// 2_1
int __m2653 = i + __s2653 > P_ncols ? P_ncols - i : __s2653;
double *t25 = t26 + ii*P_ncols*P_ncols;
double *t23 = t10 + i;
double *t24 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t24 = t24;
predict_0[disp].__m2653 = __m2653;
predict_0[disp].t23 = t23;
predict_0[disp].t25 = t25;
predict_0[disp].__s2652 = __s2652;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2653; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2653,ii+=1) {
// 2_1
int __m2653 = i + __s2653 > P_ncols ? P_ncols - i : __s2653;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2652) {
int __m2652 = __j + __s2652 > P_ncols ? P_ncols - __j : __s2652;
for (__k = 0; __k < __m2652; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t74[__j*P_ncols+__k*P_ncols+__l] = t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2652) {
int __m2652 = __j + __s2652 > P_ncols ? P_ncols - __j : __s2652;
for (__k = 0; __k < __m2652; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t74[__j*P_ncols+__k*P_ncols+__l] += t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2655);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2655);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2655,ii+=1) {
// 4_1
int __m2655 = i + __s2655 > P_ncols ? P_ncols - i : __s2655;
double *t28 = t29 + i;
double *t34 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t34 = t34;
predict_1[disp].__m2655 = __m2655;
predict_1[disp].t12 = t12;
predict_1[disp].t28 = t28;
predict_1[disp].__s2654 = __s2654;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2655; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s2657);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s2657);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2657,ii+=1) {
// 6_1
int __m2657 = i + __s2657 > P_ncols ? P_ncols - i : __s2657;
double *t32 = P + i;
double *t30 = t20 + i;
double *t31 = Q + i;
predict_2[disp].__m2657 = __m2657;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t31 = t31;
predict_2[disp].t30 = t30;
predict_2[disp].t32 = t32;
predict_2[disp].__s2656 = __s2656;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s2657; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t29);
free(t26);
}
