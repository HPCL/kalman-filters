#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2980;
int P_ncols;
double *t28;
double *t27;
double *t29;
int __s2979;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t34;
double *t21;
double *t20;
int __s2976;
int __m2977;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t34 = msg->t34;
double *t21 = msg->t21;
double *t20 = msg->t20;
int __s2976 = msg->__s2976;
int __m2977 = msg->__m2977;

for (j=0; j<__m2977; j+=__s2976) {
// 2_2
int __m2976 = j + __s2976 > __m2977 ? __m2977 - j : __s2976;
double *t31 = t20 + j;
double *t32 = t21 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t43 = t34 + k*P_ncols;
double *t42 = t31 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<__m2976; l+=1) {
// 2_4
double *t54 = t32 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t43[p] += (t42[l]*t54[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m2980 = msg->__m2980;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s2979 = msg->__s2979;

for (j=0; j<P_ncols; j+=__s2979) {
// 6_2
int __m2979 = j + __s2979 > P_ncols ? P_ncols - j : __s2979;
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m2979; k+=1) {
// 6_3
double *t50 = t40 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<__m2980; l+=1) {
// 6_4
t50[l] = (t48[l]+t49[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s2979 = 504;

int __s2978 = 12;

int __s2976 = 512;

int nparts__s2977 = 12;
int __s2977;
if (nparts__s2977 > 1 && P_ncols > nparts__s2977) {
__s2977 = P_ncols/nparts__s2977;
// this will fail if P_ncols%nparts__s2977+__s2977 > nparts__s2977
// which primarily effects small sizes
if (P_ncols%nparts__s2977)
++__s2977;
}
else {
__s2977 = P_ncols;
nparts__s2977 = 1;
}

int nparts__s2980 = 12;
int __s2980;
if (nparts__s2980 > 1 && P_ncols > nparts__s2980) {
__s2980 = P_ncols/nparts__s2980;
// this will fail if P_ncols%nparts__s2980+__s2980 > nparts__s2980
// which primarily effects small sizes
if (P_ncols%nparts__s2980)
++__s2980;
}
else {
__s2980 = P_ncols;
nparts__s2980 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*nparts__s2977*P_ncols*P_ncols);
double *t17 = t26;
double *t14 = t26;
double *t13 = t26;
double *t12 = t23;
double *t68 = t23;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2977);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2977);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2977,ii+=1) {
// 2_1
int __m2977 = i + __s2977 > P_ncols ? P_ncols - i : __s2977;
double *t34 = t23 + ii*P_ncols*P_ncols;
double *t20 = t10 + i;
double *t21 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t34 = t34;
predict_0[disp].t21 = t21;
predict_0[disp].t20 = t20;
predict_0[disp].__s2976 = __s2976;
predict_0[disp].__m2977 = __m2977;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2977; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2977,ii+=1) {
// 2_1
int __m2977 = i + __s2977 > P_ncols ? P_ncols - i : __s2977;
if ((ii == 0)) {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t68[__k*P_ncols+__l] = t23[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
} else {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t68[__k*P_ncols+__l] += t23[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s2978) {
// 4_1
int __m2978 = i + __s2978 > P_ncols ? P_ncols - i : __s2978;
double *t25 = t26 + i*P_ncols;
double *t24 = t12 + i*P_ncols;
for (j=0; j<__m2978; j+=1) {
// 4_2
double *t36 = t25 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t52 = A + k*P_ncols;
t36[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t36[k] += (t35[l]*t52[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2980);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2980);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2980,ii+=1) {
// 6_1
int __m2980 = i + __s2980 > P_ncols ? P_ncols - i : __s2980;
double *t29 = P + i;
double *t27 = t17 + i;
double *t28 = Q + i;
predict_1[disp].__m2980 = __m2980;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s2979 = __s2979;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2980; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t26);
free(t23);
}
