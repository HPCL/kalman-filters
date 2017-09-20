#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2199;
int P_ncols;
double *t17;
double *t8;
double *t18;
int __s2198;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2199 = msg->__m2199;
int P_ncols = msg->P_ncols;
double *t17 = msg->t17;
double *t8 = msg->t8;
double *t18 = msg->t18;
int __s2198 = msg->__s2198;

for (j=0; j<P_ncols; j+=__s2198) {
// 2_2
int __m2198 = j + __s2198 > P_ncols ? P_ncols - j : __s2198;
double *t28 = t18 + j*P_ncols;
double *t27 = t8 + j*P_ncols;
for (k=0; k<__m2198; k+=1) {
// 2_3
double *t38 = t28 + k*P_ncols;
double *t37 = t27 + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2199; ++__zr__) t38[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t49 = t17 + l*P_ncols;
for (p=0; p<__m2199; p+=1) {
// 2_5
t38[p] += (t37[l]*t49[p]);
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

int __s2201 = 12;

int __s2200 = 2;

int __s2198 = 512;

int nparts__s2199 = 12;
int __s2199;
if (nparts__s2199 > 1 && P_ncols > nparts__s2199) {
__s2199 = P_ncols/nparts__s2199;
// this will fail if P_ncols%nparts__s2199+__s2199 > nparts__s2199
// which primarily effects small sizes
if (P_ncols%nparts__s2199)
++__s2199;
}
else {
__s2199 = P_ncols;
nparts__s2199 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t22;
double *t13 = t22;
double *t12 = t19;
double *t9 = t19;
double *t11 = t19;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2199);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2199);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2199,ii+=1) {
// 2_1
int __m2199 = i + __s2199 > P_ncols ? P_ncols - i : __s2199;
double *t18 = t19 + i;
double *t17 = P + i;
predict_0[disp].__m2199 = __m2199;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t17 = t17;
predict_0[disp].t8 = t8;
predict_0[disp].t18 = t18;
predict_0[disp].__s2198 = __s2198;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2199; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s2200) {
// 4_1
int __m2200 = i + __s2200 > P_ncols ? P_ncols - i : __s2200;
double *t21 = t22 + i*P_ncols;
double *t20 = t12 + i*P_ncols;
for (j=0; j<__m2200; j+=1) {
// 4_2
double *t31 = t21 + j*P_ncols;
double *t30 = t20 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t47 = A + k*P_ncols;
t31[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t31[k] += (t30[l]*t47[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s2201) {
// 6_1
int __m2201 = i + __s2201 > P_ncols ? P_ncols - i : __s2201;
double *t25 = P + i*P_ncols;
double *t23 = t14 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<__m2201; j+=1) {
// 6_2
double *t35 = t25 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
double *t34 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t35[k] = (t33[k]+t34[k]);
}
}
}
free(t22);
free(t19);
}
