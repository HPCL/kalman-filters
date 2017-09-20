#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t14;
double *t15;
int __s4265;
int __m4266;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t14 = msg->t14;
double *t15 = msg->t15;
int __s4265 = msg->__s4265;
int __m4266 = msg->__m4266;

for (j=0; j<__m4266; j+=__s4265) {
// 2_2
int __m4265 = j + __s4265 > __m4266 ? __m4266 - j : __s4265;
double *t25 = t15 + j;
double *t24 = t14 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t35 = t25 + k*P_ncols;
double *t34 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m4265; ++__zr__) t35[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t42 = t24 + l*P_ncols;
for (p=0; p<__m4265; p+=1) {
// 2_5
t35[p] += (t34[l]*t42[p]);
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

int __s4267 = 2;

int __s4265 = 488;

int nparts__s4266 = 10;
int __s4266;
if (nparts__s4266 > 1 && P_ncols > nparts__s4266) {
__s4266 = P_ncols/nparts__s4266;
// this will fail if P_ncols%nparts__s4266+__s4266 > nparts__s4266
// which primarily effects small sizes
if (P_ncols%nparts__s4266)
++__s4266;
}
else {
__s4266 = P_ncols;
nparts__s4266 = 1;
}

double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t19;
double *t12 = t16;
double *t9 = t16;
double *t11 = t16;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4266);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4266);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4266,ii+=1) {
// 2_1
int __m4266 = i + __s4266 > P_ncols ? P_ncols - i : __s4266;
double *t15 = t16 + i;
double *t14 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t14 = t14;
predict_0[disp].t15 = t15;
predict_0[disp].__s4265 = __s4265;
predict_0[disp].__m4266 = __m4266;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4266; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s4267) {
// 4_1
int __m4267 = i + __s4267 > P_ncols ? P_ncols - i : __s4267;
double *t18 = t19 + i*P_ncols;
double *t17 = t12 + i*P_ncols;
for (j=0; j<__m4267; j+=1) {
// 4_2
double *t28 = t18 + j*P_ncols;
double *t27 = t17 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t40 = A + k*P_ncols;
t28[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t28[k] += (t27[l]*t40[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t22 = P + i*P_ncols;
double *t20 = t13 + i*P_ncols;
double *t21 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t22[j] = (t20[j]+t21[j]);
}
}
free(t19);
free(t16);
}
