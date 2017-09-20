#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t28;
int __m991;
double *t10;
double *t22;
int __s990;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
int __m991 = msg->__m991;
double *t10 = msg->t10;
double *t22 = msg->t22;
int __s990 = msg->__s990;

for (j=0; j<P_ncols; j+=__s990) {
// 4_2
int __m990 = j + __s990 > P_ncols ? P_ncols - j : __s990;
double *t33 = t22 + j*P_ncols;
double *t32 = t10 + j*P_ncols;
for (k=0; k<__m990; k+=1) {
// 4_3
double *t44 = t33 + k*P_ncols;
double *t43 = t32 + k*P_ncols;
for (l=0; l<__m991; l+=1) {
// 4_4
double *t56 = t28 + l*P_ncols;
t44[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t44[l] += (t43[p]*t56[p]);
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

int __s992 = 2;

int __s990 = 512;

int __s989 = 12;

int nparts__s991 = 12;
int __s991;
if (nparts__s991 > 1 && P_ncols > nparts__s991) {
__s991 = P_ncols/nparts__s991;
// this will fail if P_ncols%nparts__s991+__s991 > nparts__s991
// which primarily effects small sizes
if (P_ncols%nparts__s991)
++__s991;
}
else {
__s991 = P_ncols;
nparts__s991 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t15 = t23;
double *t11 = t23;
double *t13 = t23;
double *t10 = t20;
double *t9 = t20;
double *t8 = A;
double *t14 = A;
for (i=0; i<P_ncols; i+=__s989) {
// 2_1
int __m989 = i + __s989 > P_ncols ? P_ncols - i : __s989;
double *t19 = t20 + i*P_ncols;
double *t18 = t8 + i*P_ncols;
for (j=0; j<__m989; j+=1) {
// 2_2
double *t30 = t19 + j*P_ncols;
double *t29 = t18 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t30[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t40 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t30[l] += (t29[k]*t40[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s991);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s991);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s991,ii+=1) {
// 4_1
int __m991 = i + __s991 > P_ncols ? P_ncols - i : __s991;
double *t22 = t23 + i;
double *t28 = t14 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t28 = t28;
predict_0[disp].__m991 = __m991;
predict_0[disp].t10 = t10;
predict_0[disp].t22 = t22;
predict_0[disp].__s990 = __s990;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s991; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s992) {
// 6_1
int __m992 = i + __s992 > P_ncols ? P_ncols - i : __s992;
double *t26 = P + i*P_ncols;
double *t24 = t15 + i*P_ncols;
double *t25 = Q + i*P_ncols;
for (j=0; j<__m992; j+=1) {
// 6_2
double *t37 = t26 + j*P_ncols;
double *t35 = t24 + j*P_ncols;
double *t36 = t25 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t23);
free(t20);
}
