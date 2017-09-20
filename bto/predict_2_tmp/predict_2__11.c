#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *P;
double *t29;
double *t22;
double *t30;
int __s48;
int __m49;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *P = msg->P;
double *t29 = msg->t29;
double *t22 = msg->t22;
double *t30 = msg->t30;
int __s48 = msg->__s48;
int __m49 = msg->__m49;

for (j=0; j<__m49; j+=__s48) {
// 2_2
int __m48 = j + __s48 > __m49 ? __m49 - j : __s48;
double *t46 = malloc(sizeof(double)*P_ncols);
double *t43 = malloc(sizeof(double)*P_ncols);
double *t40 = t30 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
double *t39 = t29 + j*P_ncols;
for (k=0; k<__m48; k+=1) {
// 2_3
double *t50 = t40 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t53 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t43[p] += (t42[l]*t53[p]);
}
}
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t63 = A + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t46[l] += (t43[p]*t63[p]);
}
}
for (l=0; l<P_ncols; l+=1) {
// 6_4
t50[l] = (t46[l]+t49[l]);
}
}
free(t46);
free(t43);
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s48 = 512;

int nparts__s49 = 12;
int __s49;
if (nparts__s49 > 1 && P_ncols > nparts__s49) {
__s49 = P_ncols/nparts__s49;
// this will fail if P_ncols%nparts__s49+__s49 > nparts__s49
// which primarily effects small sizes
if (P_ncols%nparts__s49)
++__s49;
}
else {
__s49 = P_ncols;
nparts__s49 = 1;
}

double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s49);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s49);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s49,ii+=1) {
// 2_1
int __m49 = i + __s49 > P_ncols ? P_ncols - i : __s49;
double *t30 = P + i*P_ncols;
double *t22 = t10 + i*P_ncols;
double *t29 = Q + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].P = P;
predict_0[disp].t29 = t29;
predict_0[disp].t22 = t22;
predict_0[disp].t30 = t30;
predict_0[disp].__s48 = __s48;
predict_0[disp].__m49 = __m49;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s49; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
}
