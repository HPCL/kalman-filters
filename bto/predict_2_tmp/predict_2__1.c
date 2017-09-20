#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t29;
double *t30;
int __s13;
int __m10;
double *A;
int __s11;
double *P;
double *t22;
int __s9;
int __s10;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t30 = msg->t30;
int __s13 = msg->__s13;
int __m10 = msg->__m10;
double *A = msg->A;
int __s11 = msg->__s11;
double *P = msg->P;
double *t22 = msg->t22;
int __s9 = msg->__s9;
int __s10 = msg->__s10;

double *t26 = malloc(sizeof(double)*__s10*P_ncols);
double *t23 = malloc(sizeof(double)*__s10*P_ncols);
for (j=0; j<__m10; j+=__s9) {
// 2_2
int __m9 = j + __s9 > __m10 ? __m10 - j : __s9;
double *t33 = t23 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<__m9; k+=1) {
// 2_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t53 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t43[p] += (t42[l]*t53[p]);
}
}
}
}
for (j=0; j<__m10; j+=__s11) {
// 4_2
int __m11 = j + __s11 > __m10 ? __m10 - j : __s11;
double *t36 = t26 + j*P_ncols;
double *t35 = t23 + j*P_ncols;
for (k=0; k<__m11; k+=1) {
// 4_3
double *t46 = t36 + k*P_ncols;
double *t45 = t35 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t63 = A + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t46[l] += (t45[p]*t63[p]);
}
}
}
}
for (j=0; j<__m10; j+=__s13) {
// 6_2
int __m13 = j + __s13 > __m10 ? __m10 - j : __s13;
double *t40 = t30 + j*P_ncols;
double *t38 = t26 + j*P_ncols;
double *t39 = t29 + j*P_ncols;
for (k=0; k<__m13; k+=1) {
// 6_3
double *t50 = t40 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 6_4
t50[l] = (t48[l]+t49[l]);
}
}
}
free(t26);
free(t23);
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s9 = 512;

int __s13 = 512;

int __s11 = 512;

int nparts__s10 = 10;
int __s10;
if (nparts__s10 > 1 && P_ncols > nparts__s10) {
__s10 = P_ncols/nparts__s10;
// this will fail if P_ncols%nparts__s10+__s10 > nparts__s10
// which primarily effects small sizes
if (P_ncols%nparts__s10)
++__s10;
}
else {
__s10 = P_ncols;
nparts__s10 = 1;
}

double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s10);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s10);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s10,ii+=1) {
// 2_1
int __m10 = i + __s10 > P_ncols ? P_ncols - i : __s10;
double *t30 = P + i*P_ncols;
double *t22 = t10 + i*P_ncols;
double *t29 = Q + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t29 = t29;
predict_0[disp].t30 = t30;
predict_0[disp].__s13 = __s13;
predict_0[disp].__m10 = __m10;
predict_0[disp].A = A;
predict_0[disp].__s11 = __s11;
predict_0[disp].P = P;
predict_0[disp].t22 = t22;
predict_0[disp].__s9 = __s9;
predict_0[disp].__s10 = __s10;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s10; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
}
