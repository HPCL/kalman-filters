#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t29;
double *t30;
int __s3450;
int __m3447;
double *A;
double *P;
double *t22;
int __s3446;
int __s3447;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t30 = msg->t30;
int __s3450 = msg->__s3450;
int __m3447 = msg->__m3447;
double *A = msg->A;
double *P = msg->P;
double *t22 = msg->t22;
int __s3446 = msg->__s3446;
int __s3447 = msg->__s3447;

double *t26 = malloc(sizeof(double)*__s3447*P_ncols);
for (j=0; j<__m3447; j+=__s3446) {
// 2_2
int __m3446 = j + __s3446 > __m3447 ? __m3447 - j : __s3446;
double *t33 = malloc(sizeof(double)*__s3446*P_ncols);
double *t36 = t26 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<__m3446; k+=1) {
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
for (k=0; k<__m3446; k+=1) {
// 4_3
double *t46 = t36 + k*P_ncols;
double *t45 = t33 + k*P_ncols;
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
free(t33);
}
for (j=0; j<__m3447; j+=__s3450) {
// 6_2
int __m3450 = j + __s3450 > __m3447 ? __m3447 - j : __s3450;
double *t40 = t30 + j*P_ncols;
double *t38 = t26 + j*P_ncols;
double *t39 = t29 + j*P_ncols;
for (k=0; k<__m3450; k+=1) {
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
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s3450 = 496;

int __s3446 = 512;

int nparts__s3447 = 12;
int __s3447;
if (nparts__s3447 > 1 && P_ncols > nparts__s3447) {
__s3447 = P_ncols/nparts__s3447;
// this will fail if P_ncols%nparts__s3447+__s3447 > nparts__s3447
// which primarily effects small sizes
if (P_ncols%nparts__s3447)
++__s3447;
}
else {
__s3447 = P_ncols;
nparts__s3447 = 1;
}

double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s3447);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s3447);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s3447,ii+=1) {
// 2_1
int __m3447 = i + __s3447 > P_ncols ? P_ncols - i : __s3447;
double *t30 = P + i*P_ncols;
double *t22 = t10 + i*P_ncols;
double *t29 = Q + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t29 = t29;
predict_0[disp].t30 = t30;
predict_0[disp].__s3450 = __s3450;
predict_0[disp].__m3447 = __m3447;
predict_0[disp].A = A;
predict_0[disp].P = P;
predict_0[disp].t22 = t22;
predict_0[disp].__s3446 = __s3446;
predict_0[disp].__s3447 = __s3447;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s3447; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
}
