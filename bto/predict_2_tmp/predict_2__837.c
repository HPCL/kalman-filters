#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2038;
int P_ncols;
double *t29;
double *t28;
double *t30;
int __s2037;
} predict_1_msg_t;

typedef struct { 
int __m2036;
int P_ncols;
double *t32;
double *t24;
double *t26;
int __s2035;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2036 = msg->__m2036;
int P_ncols = msg->P_ncols;
double *t32 = msg->t32;
double *t24 = msg->t24;
double *t26 = msg->t26;
int __s2035 = msg->__s2035;

for (j=0; j<P_ncols; j+=__s2035) {
// 4_2
int __m2035 = j + __s2035 > P_ncols ? P_ncols - j : __s2035;
double *t37 = t26 + j*P_ncols;
double *t36 = t24 + j*P_ncols;
for (k=0; k<__m2035; k+=1) {
// 4_3
double *t48 = t37 + k*P_ncols;
double *t47 = t36 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t64 = t32 + l*P_ncols;
t48[l] = 0.0;
for (p=0; p<__m2036; p+=1) {
// 4_5
t48[l] += (t47[p]*t64[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m2038 = msg->__m2038;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t28 = msg->t28;
double *t30 = msg->t30;
int __s2037 = msg->__s2037;

for (j=0; j<P_ncols; j+=__s2037) {
// 6_2
int __m2037 = j + __s2037 > P_ncols ? P_ncols - j : __s2037;
double *t41 = t30 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
double *t40 = t29 + j*P_ncols;
for (k=0; k<__m2037; k+=1) {
// 6_3
double *t52 = t41 + k*P_ncols;
double *t50 = t39 + k*P_ncols;
double *t51 = t40 + k*P_ncols;
for (l=0; l<__m2038; l+=1) {
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

int __s2037 = 512;

int __s2035 = 512;

int __s2034 = 2;

int nparts__s2036 = 12;
int __s2036;
if (nparts__s2036 > 1 && P_ncols > nparts__s2036) {
__s2036 = P_ncols/nparts__s2036;
// this will fail if P_ncols%nparts__s2036+__s2036 > nparts__s2036
// which primarily effects small sizes
if (P_ncols%nparts__s2036)
++__s2036;
}
else {
__s2036 = P_ncols;
nparts__s2036 = 1;
}

int nparts__s2038 = 12;
int __s2038;
if (nparts__s2038 > 1 && P_ncols > nparts__s2038) {
__s2038 = P_ncols/nparts__s2038;
// this will fail if P_ncols%nparts__s2038+__s2038 > nparts__s2038
// which primarily effects small sizes
if (P_ncols%nparts__s2038)
++__s2038;
}
else {
__s2038 = P_ncols;
nparts__s2038 = 1;
}

double *t27 = malloc(sizeof(double)*nparts__s2036*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t27;
double *t15 = t27;
double *t11 = t27;
double *t69 = t27;
double *t12 = t23;
double *t10 = t23;
double *t9 = t23;
double *t8 = A;
double *t14 = A;
for (i=0; i<P_ncols; i+=__s2034) {
// 2_1
int __m2034 = i + __s2034 > P_ncols ? P_ncols - i : __s2034;
double *t22 = t23 + i*P_ncols;
double *t21 = t8 + i*P_ncols;
for (j=0; j<__m2034; j+=1) {
// 2_2
double *t34 = t22 + j*P_ncols;
double *t33 = t21 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t34[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t44 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t34[l] += (t33[k]*t44[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2036);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2036);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2036,ii+=1) {
// 4_1
int __m2036 = i + __s2036 > P_ncols ? P_ncols - i : __s2036;
double *t26 = t27 + ii*P_ncols*P_ncols;
double *t24 = t12 + i;
double *t32 = t14 + i;
predict_0[disp].__m2036 = __m2036;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t32 = t32;
predict_0[disp].t24 = t24;
predict_0[disp].t26 = t26;
predict_0[disp].__s2035 = __s2035;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2036; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2036,ii+=1) {
// 4_1
int __m2036 = i + __s2036 > P_ncols ? P_ncols - i : __s2036;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2035) {
int __m2035 = __j + __s2035 > P_ncols ? P_ncols - __j : __s2035;
for (__k = 0; __k < __m2035; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] = t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2035) {
int __m2035 = __j + __s2035 > P_ncols ? P_ncols - __j : __s2035;
for (__k = 0; __k < __m2035; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] += t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2038);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2038);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2038,ii+=1) {
// 6_1
int __m2038 = i + __s2038 > P_ncols ? P_ncols - i : __s2038;
double *t30 = P + i;
double *t28 = t18 + i;
double *t29 = Q + i;
predict_1[disp].__m2038 = __m2038;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t29 = t29;
predict_1[disp].t28 = t28;
predict_1[disp].t30 = t30;
predict_1[disp].__s2037 = __s2037;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2038; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t27);
free(t23);
}
