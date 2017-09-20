#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2774;
int P_ncols;
double *t28;
double *t29;
int __s2775;
double *t31;
double *t10;
int __s2773;
int __s2774;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m2774 = msg->__m2774;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t29 = msg->t29;
int __s2775 = msg->__s2775;
double *t31 = msg->t31;
double *t10 = msg->t10;
int __s2773 = msg->__s2773;
int __s2774 = msg->__s2774;

double *t25 = malloc(sizeof(double)*P_ncols*__s2774);
for (j=0; j<P_ncols; j+=__s2773) {
// 4_2
int __m2773 = j + __s2773 > P_ncols ? P_ncols - j : __s2773;
double *t36 = t25 + j*__m2774;
double *t35 = t10 + j*P_ncols;
for (k=0; k<__m2773; k+=1) {
// 4_3
double *t47 = t36 + k*__m2774;
double *t46 = t35 + k*P_ncols;
for (l=0; l<__m2774; l+=1) {
// 4_4
double *t63 = t31 + l*P_ncols;
t47[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t47[l] += (t46[p]*t63[p]);
}
}
}
}
for (j=0; j<P_ncols; j+=__s2775) {
// 6_2
int __m2775 = j + __s2775 > P_ncols ? P_ncols - j : __s2775;
double *t40 = t29 + j*P_ncols;
double *t38 = t25 + j*__m2774;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m2775; k+=1) {
// 6_3
double *t51 = t40 + k*P_ncols;
double *t49 = t38 + k*__m2774;
double *t50 = t39 + k*P_ncols;
for (l=0; l<__m2774; l+=1) {
// 6_4
t51[l] = (t49[l]+t50[l]);
}
}
}
free(t25);
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s2775 = 504;

int __s2773 = 504;

int __s2772 = 2;

int nparts__s2774 = 10;
int __s2774;
if (nparts__s2774 > 1 && P_ncols > nparts__s2774) {
__s2774 = P_ncols/nparts__s2774;
// this will fail if P_ncols%nparts__s2774+__s2774 > nparts__s2774
// which primarily effects small sizes
if (P_ncols%nparts__s2774)
++__s2774;
}
else {
__s2774 = P_ncols;
nparts__s2774 = 1;
}

double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t10 = t23;
double *t9 = t23;
double *t8 = A;
double *t14 = A;
for (i=0; i<P_ncols; i+=__s2772) {
// 2_1
int __m2772 = i + __s2772 > P_ncols ? P_ncols - i : __s2772;
double *t22 = t23 + i*P_ncols;
double *t21 = t8 + i*P_ncols;
for (j=0; j<__m2772; j+=1) {
// 2_2
double *t33 = t22 + j*P_ncols;
double *t32 = t21 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t33[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t43 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t33[l] += (t32[k]*t43[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2774);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2774);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2774,ii+=1) {
// 4_1
int __m2774 = i + __s2774 > P_ncols ? P_ncols - i : __s2774;
double *t29 = P + i;
double *t31 = t14 + i*P_ncols;
double *t28 = Q + i;
predict_0[disp].__m2774 = __m2774;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t28 = t28;
predict_0[disp].t29 = t29;
predict_0[disp].__s2775 = __s2775;
predict_0[disp].t31 = t31;
predict_0[disp].t10 = t10;
predict_0[disp].__s2773 = __s2773;
predict_0[disp].__s2774 = __s2774;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2774; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t23);
}
