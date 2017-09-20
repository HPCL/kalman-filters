#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m1401;
int P_ncols;
double *t28;
double *t29;
int __s1402;
double *t31;
double *t10;
int __s1400;
int __s1401;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m1401 = msg->__m1401;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t29 = msg->t29;
int __s1402 = msg->__s1402;
double *t31 = msg->t31;
double *t10 = msg->t10;
int __s1400 = msg->__s1400;
int __s1401 = msg->__s1401;

double *t25 = malloc(sizeof(double)*P_ncols*__s1401);
for (j=0; j<P_ncols; j+=__s1400) {
// 4_2
int __m1400 = j + __s1400 > P_ncols ? P_ncols - j : __s1400;
double *t36 = t25 + j*__m1401;
double *t35 = t10 + j*P_ncols;
for (k=0; k<__m1400; k+=1) {
// 4_3
double *t47 = t36 + k*__m1401;
double *t46 = t35 + k*P_ncols;
for (l=0; l<__m1401; l+=1) {
// 4_4
double *t63 = t31 + l*P_ncols;
t47[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t47[l] += (t46[p]*t63[p]);
}
}
}
}
for (j=0; j<P_ncols; j+=__s1402) {
// 6_2
int __m1402 = j + __s1402 > P_ncols ? P_ncols - j : __s1402;
double *t40 = t29 + j*P_ncols;
double *t38 = t25 + j*__m1401;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m1402; k+=1) {
// 6_3
double *t51 = t40 + k*P_ncols;
double *t49 = t38 + k*__m1401;
double *t50 = t39 + k*P_ncols;
for (l=0; l<__m1401; l+=1) {
// 6_4
t51[l] = (t49[l]+t50[l]);
}
}
}
free(t25);
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s1402 = 512;

int __s1400 = 512;

int __s1399 = 10;

int nparts__s1401 = 10;
int __s1401;
if (nparts__s1401 > 1 && P_ncols > nparts__s1401) {
__s1401 = P_ncols/nparts__s1401;
// this will fail if P_ncols%nparts__s1401+__s1401 > nparts__s1401
// which primarily effects small sizes
if (P_ncols%nparts__s1401)
++__s1401;
}
else {
__s1401 = P_ncols;
nparts__s1401 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t10 = t23;
double *t9 = t23;
double *t8 = A;
double *t14 = A;
for (i=0; i<P_ncols; i+=__s1399) {
// 2_1
int __m1399 = i + __s1399 > P_ncols ? P_ncols - i : __s1399;
double *t22 = t23 + i*P_ncols;
double *t21 = t8 + i*P_ncols;
for (j=0; j<__m1399; j+=1) {
// 2_2
double *t33 = t22 + j*P_ncols;
double *t32 = t21 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t33[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t43 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t33[l] += (t32[k]*t43[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1401);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1401);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1401,ii+=1) {
// 4_1
int __m1401 = i + __s1401 > P_ncols ? P_ncols - i : __s1401;
double *t29 = P + i;
double *t31 = t14 + i*P_ncols;
double *t28 = Q + i;
predict_0[disp].__m1401 = __m1401;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t28 = t28;
predict_0[disp].t29 = t29;
predict_0[disp].__s1402 = __s1402;
predict_0[disp].t31 = t31;
predict_0[disp].t10 = t10;
predict_0[disp].__s1400 = __s1400;
predict_0[disp].__s1401 = __s1401;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1401; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t23);
}
