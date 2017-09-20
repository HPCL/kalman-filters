#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m904;
int P_ncols;
double *t28;
double *t27;
double *t29;
int __s903;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m904 = msg->__m904;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s903 = msg->__s903;

for (j=0; j<P_ncols; j+=__s903) {
// 6_2
int __m903 = j + __s903 > P_ncols ? P_ncols - j : __s903;
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m903; k+=1) {
// 6_3
double *t51 = t40 + k*P_ncols;
double *t49 = t38 + k*P_ncols;
double *t50 = t39 + k*P_ncols;
for (l=0; l<__m904; l+=1) {
// 6_4
t51[l] = (t49[l]+t50[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s903 = 512;

int __s902 = 2;

int __s901 = 2;

int nparts__s904 = 12;
int __s904;
if (nparts__s904 > 1 && P_ncols > nparts__s904) {
__s904 = P_ncols/nparts__s904;
// this will fail if P_ncols%nparts__s904+__s904 > nparts__s904
// which primarily effects small sizes
if (P_ncols%nparts__s904)
++__s904;
}
else {
__s904 = P_ncols;
nparts__s904 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t26;
double *t13 = t26;
double *t10 = t22;
double *t8 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s901) {
// 2_1
int __m901 = i + __s901 > P_ncols ? P_ncols - i : __s901;
double *t19 = t8 + i;
double *t20 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t33 = t22 + j*P_ncols;
double *t32 = t19 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t33[__zr__] = 0.0;
for (k=0; k<__m901; k+=1) {
// 2_3
double *t43 = t20 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t33[l] += (t32[k]*t43[l]);
}
}
}
}
for (i=0; i<P_ncols; i+=__s902) {
// 4_1
int __m902 = i + __s902 > P_ncols ? P_ncols - i : __s902;
double *t23 = t10 + i;
double *t31 = t12 + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t36 = t26 + j*P_ncols;
double *t35 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t53 = t31 + k*P_ncols;
t36[k] = 0.0;
for (l=0; l<__m902; l+=1) {
// 4_4
t36[k] += (t35[l]*t53[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s904);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s904);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s904,ii+=1) {
// 6_1
int __m904 = i + __s904 > P_ncols ? P_ncols - i : __s904;
double *t29 = P + i;
double *t27 = t16 + i;
double *t28 = Q + i;
predict_0[disp].__m904 = __m904;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t28 = t28;
predict_0[disp].t27 = t27;
predict_0[disp].t29 = t29;
predict_0[disp].__s903 = __s903;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s904; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t26);
free(t22);
}
