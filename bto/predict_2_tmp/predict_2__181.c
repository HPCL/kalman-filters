#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m488;
int P_ncols;
double *t21;
double *t20;
double *t22;
int __s487;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m488 = msg->__m488;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
double *t20 = msg->t20;
double *t22 = msg->t22;
int __s487 = msg->__s487;

for (j=0; j<P_ncols; j+=__s487) {
// 6_2
int __m487 = j + __s487 > P_ncols ? P_ncols - j : __s487;
double *t33 = t22 + j*P_ncols;
double *t31 = t20 + j*P_ncols;
double *t32 = t21 + j*P_ncols;
for (k=0; k<__m487; k+=1) {
// 6_3
double *t45 = t33 + k*P_ncols;
double *t43 = t31 + k*P_ncols;
double *t44 = t32 + k*P_ncols;
for (l=0; l<__m488; l+=1) {
// 6_4
t45[l] = (t43[l]+t44[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k;

int __s487 = 512;

int nparts__s488 = 12;
int __s488;
if (nparts__s488 > 1 && P_ncols > nparts__s488) {
__s488 = P_ncols/nparts__s488;
// this will fail if P_ncols%nparts__s488+__s488 > nparts__s488
// which primarily effects small sizes
if (P_ncols%nparts__s488)
++__s488;
}
else {
__s488 = P_ncols;
nparts__s488 = 1;
}

double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t11 = t19;
double *t8 = t19;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t15 = t16 + i*P_ncols;
double *t14 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t15[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t25 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t15[k] += (t14[j]*t25[k]);
}
}
}
for (i=0; i<P_ncols; i+=1) {
// 4_1
double *t18 = t19 + i*P_ncols;
double *t17 = t16 + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t35 = A + j*P_ncols;
t18[j] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 4_3
t18[j] += (t17[k]*t35[k]);
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s488);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s488);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s488,ii+=1) {
// 6_1
int __m488 = i + __s488 > P_ncols ? P_ncols - i : __s488;
double *t22 = P + i;
double *t20 = t11 + i;
double *t21 = Q + i;
predict_0[disp].__m488 = __m488;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].t20 = t20;
predict_0[disp].t22 = t22;
predict_0[disp].__s487 = __s487;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s488; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t19);
free(t16);
}
