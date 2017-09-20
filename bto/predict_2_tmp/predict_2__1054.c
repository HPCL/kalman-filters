#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *P;
double *t17;
double *t18;
int __s2736;
int __m2737;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t17 = msg->t17;
double *t18 = msg->t18;
int __s2736 = msg->__s2736;
int __m2737 = msg->__m2737;

for (j=0; j<__m2737; j+=__s2736) {
// 2_2
int __m2736 = j + __s2736 > __m2737 ? __m2737 - j : __s2736;
double *t28 = t18 + j*P_ncols;
double *t27 = t17 + j*P_ncols;
for (k=0; k<__m2736; k+=1) {
// 2_3
double *t38 = t28 + k*P_ncols;
double *t37 = t27 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t38[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t49 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
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

int __s2739 = 2;

int __s2738 = 2;

int __s2736 = 512;

int nparts__s2737 = 12;
int __s2737;
if (nparts__s2737 > 1 && P_ncols > nparts__s2737) {
__s2737 = P_ncols/nparts__s2737;
// this will fail if P_ncols%nparts__s2737+__s2737 > nparts__s2737
// which primarily effects small sizes
if (P_ncols%nparts__s2737)
++__s2737;
}
else {
__s2737 = P_ncols;
nparts__s2737 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t22;
double *t13 = t22;
double *t12 = t19;
double *t9 = t19;
double *t11 = t19;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2737);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2737);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2737,ii+=1) {
// 2_1
int __m2737 = i + __s2737 > P_ncols ? P_ncols - i : __s2737;
double *t18 = t19 + i*P_ncols;
double *t17 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t17 = t17;
predict_0[disp].t18 = t18;
predict_0[disp].__s2736 = __s2736;
predict_0[disp].__m2737 = __m2737;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2737; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s2738) {
// 4_1
int __m2738 = i + __s2738 > P_ncols ? P_ncols - i : __s2738;
double *t21 = t22 + i*P_ncols;
double *t20 = t12 + i*P_ncols;
for (j=0; j<__m2738; j+=1) {
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
for (i=0; i<P_ncols; i+=__s2739) {
// 6_1
int __m2739 = i + __s2739 > P_ncols ? P_ncols - i : __s2739;
double *t25 = P + i;
double *t23 = t14 + i;
double *t24 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t35 = t25 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
double *t34 = t24 + j*P_ncols;
for (k=0; k<__m2739; k+=1) {
// 6_3
t35[k] = (t33[k]+t34[k]);
}
}
}
free(t22);
free(t19);
}
