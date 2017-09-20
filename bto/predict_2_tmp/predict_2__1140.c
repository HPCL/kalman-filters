#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t27;
int __m2941;
double *t12;
double *t21;
int __s2940;
} predict_1_msg_t;

typedef struct { 
int __m2939;
int P_ncols;
double *t17;
double *t8;
double *t18;
int __s2938;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2939 = msg->__m2939;
int P_ncols = msg->P_ncols;
double *t17 = msg->t17;
double *t8 = msg->t8;
double *t18 = msg->t18;
int __s2938 = msg->__s2938;

for (j=0; j<P_ncols; j+=__s2938) {
// 2_2
int __m2938 = j + __s2938 > P_ncols ? P_ncols - j : __s2938;
double *t29 = t18 + j*P_ncols;
double *t28 = t8 + j*P_ncols;
for (k=0; k<__m2938; k+=1) {
// 2_3
double *t39 = t29 + k*P_ncols;
double *t38 = t28 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2939; ++__zr__) t39[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t45 = t17 + l*P_ncols;
for (p=0; p<__m2939; p+=1) {
// 2_5
t39[p] += (t38[l]*t45[p]);
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
double *t27 = msg->t27;
int __m2941 = msg->__m2941;
double *t12 = msg->t12;
double *t21 = msg->t21;
int __s2940 = msg->__s2940;

for (j=0; j<P_ncols; j+=__s2940) {
// 4_2
int __m2940 = j + __s2940 > P_ncols ? P_ncols - j : __s2940;
double *t32 = t21 + j*P_ncols;
double *t31 = t12 + j*P_ncols;
for (k=0; k<__m2940; k+=1) {
// 4_3
double *t42 = t32 + k*P_ncols;
double *t41 = t31 + k*P_ncols;
for (l=0; l<__m2941; l+=1) {
// 4_4
double *t51 = t27 + l*P_ncols;
t42[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t42[l] += (t41[p]*t51[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j;

int __s2940 = 512;

int __s2938 = 512;

int nparts__s2939 = 12;
int __s2939;
if (nparts__s2939 > 1 && P_ncols > nparts__s2939) {
__s2939 = P_ncols/nparts__s2939;
// this will fail if P_ncols%nparts__s2939+__s2939 > nparts__s2939
// which primarily effects small sizes
if (P_ncols%nparts__s2939)
++__s2939;
}
else {
__s2939 = P_ncols;
nparts__s2939 = 1;
}

int nparts__s2941 = 12;
int __s2941;
if (nparts__s2941 > 1 && P_ncols > nparts__s2941) {
__s2941 = P_ncols/nparts__s2941;
// this will fail if P_ncols%nparts__s2941+__s2941 > nparts__s2941
// which primarily effects small sizes
if (P_ncols%nparts__s2941)
++__s2941;
}
else {
__s2941 = P_ncols;
nparts__s2941 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t22;
double *t15 = t22;
double *t12 = t19;
double *t9 = t19;
double *t11 = t19;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2939);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2939);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2939,ii+=1) {
// 2_1
int __m2939 = i + __s2939 > P_ncols ? P_ncols - i : __s2939;
double *t18 = t19 + i;
double *t17 = P + i;
predict_0[disp].__m2939 = __m2939;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t17 = t17;
predict_0[disp].t8 = t8;
predict_0[disp].t18 = t18;
predict_0[disp].__s2938 = __s2938;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2939; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2941);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2941);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2941,ii+=1) {
// 4_1
int __m2941 = i + __s2941 > P_ncols ? P_ncols - i : __s2941;
double *t21 = t22 + i;
double *t27 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t27 = t27;
predict_1[disp].__m2941 = __m2941;
predict_1[disp].t12 = t12;
predict_1[disp].t21 = t21;
predict_1[disp].__s2940 = __s2940;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2941; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t25 = P + i*P_ncols;
double *t23 = t13 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t25[j] = (t23[j]+t24[j]);
}
}
free(t22);
free(t19);
}
