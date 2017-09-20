#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t30;
double *t29;
double *t31;
int __s1986;
int __m1987;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *t33;
int __m1985;
double *t12;
double *t27;
int __s1984;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *P;
double *t23;
double *t24;
int __s1982;
int __m1983;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t23 = msg->t23;
double *t24 = msg->t24;
int __s1982 = msg->__s1982;
int __m1983 = msg->__m1983;

for (j=0; j<__m1983; j+=__s1982) {
// 2_2
int __m1982 = j + __s1982 > __m1983 ? __m1983 - j : __s1982;
double *t35 = t24 + j*P_ncols;
double *t34 = t23 + j*P_ncols;
for (k=0; k<__m1982; k+=1) {
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
int __m1985 = msg->__m1985;
double *t12 = msg->t12;
double *t27 = msg->t27;
int __s1984 = msg->__s1984;

for (j=0; j<P_ncols; j+=__s1984) {
// 4_2
int __m1984 = j + __s1984 > P_ncols ? P_ncols - j : __s1984;
double *t38 = t27 + j*P_ncols;
double *t37 = t12 + j*P_ncols;
for (k=0; k<__m1984; k+=1) {
// 4_3
double *t48 = t38 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
for (l=0; l<__m1985; l+=1) {
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
int P_ncols = msg->P_ncols;
double *t30 = msg->t30;
double *t29 = msg->t29;
double *t31 = msg->t31;
int __s1986 = msg->__s1986;
int __m1987 = msg->__m1987;

for (j=0; j<__m1987; j+=__s1986) {
// 6_2
int __m1986 = j + __s1986 > __m1987 ? __m1987 - j : __s1986;
double *t42 = t31 + j;
double *t40 = t29 + j;
double *t41 = t30 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t52 = t42 + k*P_ncols;
double *t50 = t40 + k*P_ncols;
double *t51 = t41 + k*P_ncols;
for (l=0; l<__m1986; l+=1) {
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

int __s1986 = 512;

int __s1984 = 504;

int __s1982 = 504;

int nparts__s1987 = 12;
int __s1987;
if (nparts__s1987 > 1 && P_ncols > nparts__s1987) {
__s1987 = P_ncols/nparts__s1987;
// this will fail if P_ncols%nparts__s1987+__s1987 > nparts__s1987
// which primarily effects small sizes
if (P_ncols%nparts__s1987)
++__s1987;
}
else {
__s1987 = P_ncols;
nparts__s1987 = 1;
}

int nparts__s1983 = 12;
int __s1983;
if (nparts__s1983 > 1 && P_ncols > nparts__s1983) {
__s1983 = P_ncols/nparts__s1983;
// this will fail if P_ncols%nparts__s1983+__s1983 > nparts__s1983
// which primarily effects small sizes
if (P_ncols%nparts__s1983)
++__s1983;
}
else {
__s1983 = P_ncols;
nparts__s1983 = 1;
}

int nparts__s1985 = 12;
int __s1985;
if (nparts__s1985 > 1 && P_ncols > nparts__s1985) {
__s1985 = P_ncols/nparts__s1985;
// this will fail if P_ncols%nparts__s1985+__s1985 > nparts__s1985
// which primarily effects small sizes
if (P_ncols%nparts__s1985)
++__s1985;
}
else {
__s1985 = P_ncols;
nparts__s1985 = 1;
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1983);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1983);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1983,ii+=1) {
// 2_1
int __m1983 = i + __s1983 > P_ncols ? P_ncols - i : __s1983;
double *t24 = t25 + i*P_ncols;
double *t23 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t23 = t23;
predict_0[disp].t24 = t24;
predict_0[disp].__s1982 = __s1982;
predict_0[disp].__m1983 = __m1983;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1983; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1985);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1985);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1985,ii+=1) {
// 4_1
int __m1985 = i + __s1985 > P_ncols ? P_ncols - i : __s1985;
double *t27 = t28 + i;
double *t33 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t33 = t33;
predict_1[disp].__m1985 = __m1985;
predict_1[disp].t12 = t12;
predict_1[disp].t27 = t27;
predict_1[disp].__s1984 = __s1984;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1985; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s1987);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s1987);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1987,ii+=1) {
// 6_1
int __m1987 = i + __s1987 > P_ncols ? P_ncols - i : __s1987;
double *t31 = P + i;
double *t29 = t20 + i;
double *t30 = Q + i;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t30 = t30;
predict_2[disp].t29 = t29;
predict_2[disp].t31 = t31;
predict_2[disp].__s1986 = __s1986;
predict_2[disp].__m1987 = __m1987;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s1987; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t28);
free(t25);
}
