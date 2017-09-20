#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t15;
int __m953;
double *t14;
double *t16;
int __s952;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t15 = msg->t15;
int __m953 = msg->__m953;
double *t14 = msg->t14;
double *t16 = msg->t16;
int __s952 = msg->__s952;

for (j=0; j<P_ncols; j+=__s952) {
// 2_2
int __m952 = j + __s952 > P_ncols ? P_ncols - j : __s952;
double *t26 = t16 + j*P_ncols;
double *t25 = t14 + j*P_ncols;
for (k=0; k<__m952; k+=1) {
// 2_3
double *t36 = t26 + k*P_ncols;
double *t35 = t25 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t36[__zr__] = 0.0;
for (l=0; l<__m953; l+=1) {
// 2_4
double *t43 = t15 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t36[p] += (t35[l]*t43[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s954 = 12;

int __s952 = 512;

int nparts__s953 = 12;
int __s953;
if (nparts__s953 > 1 && P_ncols > nparts__s953) {
__s953 = P_ncols/nparts__s953;
// this will fail if P_ncols%nparts__s953+__s953 > nparts__s953
// which primarily effects small sizes
if (P_ncols%nparts__s953)
++__s953;
}
else {
__s953 = P_ncols;
nparts__s953 = 1;
}

double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = malloc(sizeof(double)*nparts__s953*P_ncols*P_ncols);
double *t13 = t20;
double *t12 = t17;
double *t9 = t17;
double *t53 = t17;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s953);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s953);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s953,ii+=1) {
// 2_1
int __m953 = i + __s953 > P_ncols ? P_ncols - i : __s953;
double *t16 = t17 + ii*P_ncols*P_ncols;
double *t14 = t10 + i;
double *t15 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t15 = t15;
predict_0[disp].__m953 = __m953;
predict_0[disp].t14 = t14;
predict_0[disp].t16 = t16;
predict_0[disp].__s952 = __s952;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s953; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s953,ii+=1) {
// 2_1
int __m953 = i + __s953 > P_ncols ? P_ncols - i : __s953;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s952) {
int __m952 = __j + __s952 > P_ncols ? P_ncols - __j : __s952;
for (__k = 0; __k < __m952; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t53[__j*P_ncols+__k*P_ncols+__l] = t17[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s952) {
int __m952 = __j + __s952 > P_ncols ? P_ncols - __j : __s952;
for (__k = 0; __k < __m952; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t53[__j*P_ncols+__k*P_ncols+__l] += t17[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s954) {
// 4_1
int __m954 = i + __s954 > P_ncols ? P_ncols - i : __s954;
double *t19 = t20 + i*P_ncols;
double *t18 = t12 + i*P_ncols;
for (j=0; j<__m954; j+=1) {
// 4_2
double *t29 = t19 + j*P_ncols;
double *t28 = t18 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t41 = A + k*P_ncols;
t29[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t29[k] += (t28[l]*t41[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t23 = P + i*P_ncols;
double *t21 = t13 + i*P_ncols;
double *t22 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t23[j] = (t21[j]+t22[j]);
}
}
free(t20);
free(t17);
}
