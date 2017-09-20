#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t29;
double *t28;
double *t30;
int __s3118;
int __m3119;
} predict_1_msg_t;

typedef struct { 
int __m3117;
int P_ncols;
double *t32;
double *t24;
double *t26;
int __s3116;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m3117 = msg->__m3117;
int P_ncols = msg->P_ncols;
double *t32 = msg->t32;
double *t24 = msg->t24;
double *t26 = msg->t26;
int __s3116 = msg->__s3116;

for (j=0; j<P_ncols; j+=__s3116) {
// 4_2
int __m3116 = j + __s3116 > P_ncols ? P_ncols - j : __s3116;
double *t37 = t26 + j*P_ncols;
double *t36 = t24 + j*P_ncols;
for (k=0; k<__m3116; k+=1) {
// 4_3
double *t48 = t37 + k*P_ncols;
double *t47 = t36 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t64 = t32 + l*P_ncols;
t48[l] = 0.0;
for (p=0; p<__m3117; p+=1) {
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
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t28 = msg->t28;
double *t30 = msg->t30;
int __s3118 = msg->__s3118;
int __m3119 = msg->__m3119;

for (j=0; j<__m3119; j+=__s3118) {
// 6_2
int __m3118 = j + __s3118 > __m3119 ? __m3119 - j : __s3118;
double *t41 = t30 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
double *t40 = t29 + j*P_ncols;
for (k=0; k<__m3118; k+=1) {
// 6_3
double *t52 = t41 + k*P_ncols;
double *t50 = t39 + k*P_ncols;
double *t51 = t40 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
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

int __s3118 = 504;

int __s3116 = 504;

int __s3115 = 2;

int nparts__s3119 = 12;
int __s3119;
if (nparts__s3119 > 1 && P_ncols > nparts__s3119) {
__s3119 = P_ncols/nparts__s3119;
// this will fail if P_ncols%nparts__s3119+__s3119 > nparts__s3119
// which primarily effects small sizes
if (P_ncols%nparts__s3119)
++__s3119;
}
else {
__s3119 = P_ncols;
nparts__s3119 = 1;
}

int nparts__s3117 = 12;
int __s3117;
if (nparts__s3117 > 1 && P_ncols > nparts__s3117) {
__s3117 = P_ncols/nparts__s3117;
// this will fail if P_ncols%nparts__s3117+__s3117 > nparts__s3117
// which primarily effects small sizes
if (P_ncols%nparts__s3117)
++__s3117;
}
else {
__s3117 = P_ncols;
nparts__s3117 = 1;
}

double *t27 = malloc(sizeof(double)*nparts__s3117*P_ncols*P_ncols);
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
for (i=0; i<P_ncols; i+=__s3115) {
// 2_1
int __m3115 = i + __s3115 > P_ncols ? P_ncols - i : __s3115;
double *t22 = t23 + i*P_ncols;
double *t21 = t8 + i*P_ncols;
for (j=0; j<__m3115; j+=1) {
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3117);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3117);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3117,ii+=1) {
// 4_1
int __m3117 = i + __s3117 > P_ncols ? P_ncols - i : __s3117;
double *t26 = t27 + ii*P_ncols*P_ncols;
double *t24 = t12 + i;
double *t32 = t14 + i;
predict_0[disp].__m3117 = __m3117;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t32 = t32;
predict_0[disp].t24 = t24;
predict_0[disp].t26 = t26;
predict_0[disp].__s3116 = __s3116;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3117; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s3117,ii+=1) {
// 4_1
int __m3117 = i + __s3117 > P_ncols ? P_ncols - i : __s3117;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s3116) {
int __m3116 = __j + __s3116 > P_ncols ? P_ncols - __j : __s3116;
for (__k = 0; __k < __m3116; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] = t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s3116) {
int __m3116 = __j + __s3116 > P_ncols ? P_ncols - __j : __s3116;
for (__k = 0; __k < __m3116; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t69[__j*P_ncols+__k*P_ncols+__l] += t27[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s3119);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s3119);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3119,ii+=1) {
// 6_1
int __m3119 = i + __s3119 > P_ncols ? P_ncols - i : __s3119;
double *t30 = P + i*P_ncols;
double *t28 = t18 + i*P_ncols;
double *t29 = Q + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t29 = t29;
predict_1[disp].t28 = t28;
predict_1[disp].t30 = t30;
predict_1[disp].__s3118 = __s3118;
predict_1[disp].__m3119 = __m3119;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s3119; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t27);
free(t23);
}
