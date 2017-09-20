#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m2858;
double *t26;
double *t32;
double *t12;
int __s2857;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t36;
double *t22;
double *t21;
int __s2855;
int __m2856;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t36 = msg->t36;
double *t22 = msg->t22;
double *t21 = msg->t21;
int __s2855 = msg->__s2855;
int __m2856 = msg->__m2856;

for (j=0; j<__m2856; j+=__s2855) {
// 2_2
int __m2855 = j + __s2855 > __m2856 ? __m2856 - j : __s2855;
double *t33 = t21 + j;
double *t34 = t22 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t47 = t36 + k*P_ncols;
double *t46 = t33 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t47[__zr__] = 0.0;
for (l=0; l<__m2855; l+=1) {
// 2_4
double *t57 = t34 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t47[p] += (t46[l]*t57[p]);
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
int __m2858 = msg->__m2858;
double *t26 = msg->t26;
double *t32 = msg->t32;
double *t12 = msg->t12;
int __s2857 = msg->__s2857;

for (j=0; j<P_ncols; j+=__s2857) {
// 4_2
int __m2857 = j + __s2857 > P_ncols ? P_ncols - j : __s2857;
double *t37 = t12 + j;
double *t45 = t32 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t50 = t26 + k*P_ncols;
double *t49 = t37 + k*P_ncols;
for (l=0; l<__m2858; l+=1) {
// 4_4
double *t63 = t45 + l*P_ncols;
t50[l] = 0.0;
for (p=0; p<__m2857; p+=1) {
// 4_5
t50[l] += (t49[p]*t63[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k;

int __s2859 = 10;

int __s2857 = 504;

int __s2855 = 512;

int nparts__s2856 = 8;
int __s2856;
if (nparts__s2856 > 1 && P_ncols > nparts__s2856) {
__s2856 = P_ncols/nparts__s2856;
// this will fail if P_ncols%nparts__s2856+__s2856 > nparts__s2856
// which primarily effects small sizes
if (P_ncols%nparts__s2856)
++__s2856;
}
else {
__s2856 = P_ncols;
nparts__s2856 = 1;
}

int nparts__s2858 = 10;
int __s2858;
if (nparts__s2858 > 1 && P_ncols > nparts__s2858) {
__s2858 = P_ncols/nparts__s2858;
// this will fail if P_ncols%nparts__s2858+__s2858 > nparts__s2858
// which primarily effects small sizes
if (P_ncols%nparts__s2858)
++__s2858;
}
else {
__s2858 = P_ncols;
nparts__s2858 = 1;
}

double *t27 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t24 = malloc(sizeof(double)*nparts__s2856*P_ncols*P_ncols);
double *t18 = t27;
double *t16 = t27;
double *t12 = t24;
double *t71 = t24;
double *t10 = A;
double *t8 = A;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2856);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2856);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2856,ii+=1) {
// 2_1
int __m2856 = i + __s2856 > P_ncols ? P_ncols - i : __s2856;
double *t36 = t24 + ii*P_ncols*P_ncols;
double *t21 = t10 + i;
double *t22 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t36 = t36;
predict_0[disp].t22 = t22;
predict_0[disp].t21 = t21;
predict_0[disp].__s2855 = __s2855;
predict_0[disp].__m2856 = __m2856;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2856; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2856,ii+=1) {
// 2_1
int __m2856 = i + __s2856 > P_ncols ? P_ncols - i : __s2856;
if ((ii == 0)) {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t71[__k*P_ncols+__l] = t24[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
} else {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t71[__k*P_ncols+__l] += t24[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2858);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2858);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2858,ii+=1) {
// 4_1
int __m2858 = i + __s2858 > P_ncols ? P_ncols - i : __s2858;
double *t26 = t27 + i;
double *t32 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].__m2858 = __m2858;
predict_1[disp].t26 = t26;
predict_1[disp].t32 = t32;
predict_1[disp].t12 = t12;
predict_1[disp].__s2857 = __s2857;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2858; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s2859) {
// 6_1
int __m2859 = i + __s2859 > P_ncols ? P_ncols - i : __s2859;
double *t30 = P + i*P_ncols;
double *t28 = t18 + i*P_ncols;
double *t29 = Q + i*P_ncols;
for (j=0; j<__m2859; j+=1) {
// 6_2
double *t43 = t30 + j*P_ncols;
double *t41 = t28 + j*P_ncols;
double *t42 = t29 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t43[k] = (t41[k]+t42[k]);
}
}
}
free(t27);
free(t24);
}
