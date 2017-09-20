#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t27;
double *t26;
double *t28;
int __s1036;
int __m1037;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t27 = msg->t27;
double *t26 = msg->t26;
double *t28 = msg->t28;
int __s1036 = msg->__s1036;
int __m1037 = msg->__m1037;

for (j=0; j<__m1037; j+=__s1036) {
// 6_2
int __m1036 = j + __s1036 > __m1037 ? __m1037 - j : __s1036;
double *t39 = t28 + j*P_ncols;
double *t37 = t26 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
for (k=0; k<__m1036; k+=1) {
// 6_3
double *t50 = t39 + k*P_ncols;
double *t48 = t37 + k*P_ncols;
double *t49 = t38 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
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

int __s1036 = 504;

int __s1035 = 2;

int __s1034 = 2;

int nparts__s1037 = 12;
int __s1037;
if (nparts__s1037 > 1 && P_ncols > nparts__s1037) {
__s1037 = P_ncols/nparts__s1037;
// this will fail if P_ncols%nparts__s1037+__s1037 > nparts__s1037
// which primarily effects small sizes
if (P_ncols%nparts__s1037)
++__s1037;
}
else {
__s1037 = P_ncols;
nparts__s1037 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t25;
double *t13 = t25;
double *t10 = t21;
double *t9 = t21;
double *t8 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s1034) {
// 2_1
int __m1034 = i + __s1034 > P_ncols ? P_ncols - i : __s1034;
double *t20 = t21 + i*P_ncols;
double *t19 = t8 + i*P_ncols;
for (j=0; j<__m1034; j+=1) {
// 2_2
double *t32 = t20 + j*P_ncols;
double *t31 = t19 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t32[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t42 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t32[l] += (t31[k]*t42[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s1035) {
// 4_1
int __m1035 = i + __s1035 > P_ncols ? P_ncols - i : __s1035;
double *t22 = t10 + i;
double *t30 = t12 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t35 = t25 + j*P_ncols;
double *t34 = t22 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t52 = t30 + k*P_ncols;
t35[k] = 0.0;
for (l=0; l<__m1035; l+=1) {
// 4_4
t35[k] += (t34[l]*t52[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1037);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1037);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1037,ii+=1) {
// 6_1
int __m1037 = i + __s1037 > P_ncols ? P_ncols - i : __s1037;
double *t28 = P + i*P_ncols;
double *t26 = t16 + i*P_ncols;
double *t27 = Q + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t27 = t27;
predict_0[disp].t26 = t26;
predict_0[disp].t28 = t28;
predict_0[disp].__s1036 = __s1036;
predict_0[disp].__m1037 = __m1037;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1037; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t25);
free(t21);
}
