#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t20;
double *t21;
int __s155;
int __m156;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t20 = msg->t20;
double *t21 = msg->t21;
int __s155 = msg->__s155;
int __m156 = msg->__m156;

for (j=0; j<__m156; j+=__s155) {
// 4_2
int __m155 = j + __s155 > __m156 ? __m156 - j : __s155;
double *t31 = t21 + j*P_ncols;
double *t30 = t20 + j*P_ncols;
for (k=0; k<__m155; k+=1) {
// 4_3
double *t42 = t31 + k*P_ncols;
double *t41 = t30 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t54 = A + l*P_ncols;
t42[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t42[l] += (t41[p]*t54[p]);
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

int __s157 = 12;

int __s155 = 504;

int __s154 = 12;

int nparts__s156 = 12;
int __s156;
if (nparts__s156 > 1 && P_ncols > nparts__s156) {
__s156 = P_ncols/nparts__s156;
// this will fail if P_ncols%nparts__s156+__s156 > nparts__s156
// which primarily effects small sizes
if (P_ncols%nparts__s156)
++__s156;
}
else {
__s156 = P_ncols;
nparts__s156 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t22;
double *t11 = t22;
double *t13 = t22;
double *t12 = t19;
double *t10 = t19;
double *t9 = t19;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s154) {
// 2_1
int __m154 = i + __s154 > P_ncols ? P_ncols - i : __s154;
double *t18 = t19 + i*P_ncols;
double *t17 = t8 + i*P_ncols;
for (j=0; j<__m154; j+=1) {
// 2_2
double *t28 = t18 + j*P_ncols;
double *t27 = t17 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t28[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t38 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t28[l] += (t27[k]*t38[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s156);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s156);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s156,ii+=1) {
// 4_1
int __m156 = i + __s156 > P_ncols ? P_ncols - i : __s156;
double *t21 = t22 + i*P_ncols;
double *t20 = t12 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t20 = t20;
predict_0[disp].t21 = t21;
predict_0[disp].__s155 = __s155;
predict_0[disp].__m156 = __m156;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s156; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s157) {
// 6_1
int __m157 = i + __s157 > P_ncols ? P_ncols - i : __s157;
double *t25 = P + i*P_ncols;
double *t23 = t14 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<__m157; j+=1) {
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
