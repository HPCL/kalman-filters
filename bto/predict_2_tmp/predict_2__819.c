#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m1970;
int P_ncols;
double *t30;
double *t29;
double *t31;
int __s1969;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *t33;
int __m1968;
double *t12;
double *t27;
int __s1967;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *P;
double *t23;
double *t24;
int __s1965;
int __m1966;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t23 = msg->t23;
double *t24 = msg->t24;
int __s1965 = msg->__s1965;
int __m1966 = msg->__m1966;

for (j=0; j<__m1966; j+=__s1965) {
// 2_2
int __m1965 = j + __s1965 > __m1966 ? __m1966 - j : __s1965;
double *t35 = t24 + j*P_ncols;
double *t34 = t23 + j*P_ncols;
for (k=0; k<__m1965; k+=1) {
// 2_3
double *t45 = t35 + k*P_ncols;
double *t44 = t34 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t45[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t55 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
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
int __m1968 = msg->__m1968;
double *t12 = msg->t12;
double *t27 = msg->t27;
int __s1967 = msg->__s1967;

for (j=0; j<P_ncols; j+=__s1967) {
// 4_2
int __m1967 = j + __s1967 > P_ncols ? P_ncols - j : __s1967;
double *t38 = t27 + j*P_ncols;
double *t37 = t12 + j*P_ncols;
for (k=0; k<__m1967; k+=1) {
// 4_3
double *t48 = t38 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
for (l=0; l<__m1968; l+=1) {
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
int __m1970 = msg->__m1970;
int P_ncols = msg->P_ncols;
double *t30 = msg->t30;
double *t29 = msg->t29;
double *t31 = msg->t31;
int __s1969 = msg->__s1969;

for (j=0; j<P_ncols; j+=__s1969) {
// 6_2
int __m1969 = j + __s1969 > P_ncols ? P_ncols - j : __s1969;
double *t42 = t31 + j*P_ncols;
double *t40 = t29 + j*P_ncols;
double *t41 = t30 + j*P_ncols;
for (k=0; k<__m1969; k+=1) {
// 6_3
double *t52 = t42 + k*P_ncols;
double *t50 = t40 + k*P_ncols;
double *t51 = t41 + k*P_ncols;
for (l=0; l<__m1970; l+=1) {
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

int __s1969 = 512;

int __s1967 = 504;

int __s1965 = 504;

int nparts__s1966 = 12;
int __s1966;
if (nparts__s1966 > 1 && P_ncols > nparts__s1966) {
__s1966 = P_ncols/nparts__s1966;
// this will fail if P_ncols%nparts__s1966+__s1966 > nparts__s1966
// which primarily effects small sizes
if (P_ncols%nparts__s1966)
++__s1966;
}
else {
__s1966 = P_ncols;
nparts__s1966 = 1;
}

int nparts__s1968 = 12;
int __s1968;
if (nparts__s1968 > 1 && P_ncols > nparts__s1968) {
__s1968 = P_ncols/nparts__s1968;
// this will fail if P_ncols%nparts__s1968+__s1968 > nparts__s1968
// which primarily effects small sizes
if (P_ncols%nparts__s1968)
++__s1968;
}
else {
__s1968 = P_ncols;
nparts__s1968 = 1;
}

int nparts__s1970 = 12;
int __s1970;
if (nparts__s1970 > 1 && P_ncols > nparts__s1970) {
__s1970 = P_ncols/nparts__s1970;
// this will fail if P_ncols%nparts__s1970+__s1970 > nparts__s1970
// which primarily effects small sizes
if (P_ncols%nparts__s1970)
++__s1970;
}
else {
__s1970 = P_ncols;
nparts__s1970 = 1;
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
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1966);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1966);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1966,ii+=1) {
// 2_1
int __m1966 = i + __s1966 > P_ncols ? P_ncols - i : __s1966;
double *t24 = t25 + i*P_ncols;
double *t23 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t23 = t23;
predict_0[disp].t24 = t24;
predict_0[disp].__s1965 = __s1965;
predict_0[disp].__m1966 = __m1966;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1966; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1968);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1968);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1968,ii+=1) {
// 4_1
int __m1968 = i + __s1968 > P_ncols ? P_ncols - i : __s1968;
double *t27 = t28 + i;
double *t33 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t33 = t33;
predict_1[disp].__m1968 = __m1968;
predict_1[disp].t12 = t12;
predict_1[disp].t27 = t27;
predict_1[disp].__s1967 = __s1967;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1968; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s1970);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s1970);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1970,ii+=1) {
// 6_1
int __m1970 = i + __s1970 > P_ncols ? P_ncols - i : __s1970;
double *t31 = P + i;
double *t29 = t20 + i;
double *t30 = Q + i;
predict_2[disp].__m1970 = __m1970;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t30 = t30;
predict_2[disp].t29 = t29;
predict_2[disp].t31 = t31;
predict_2[disp].__s1969 = __s1969;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s1970; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t28);
free(t25);
}
