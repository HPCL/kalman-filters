#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *P;
double *t18;
double *t19;
int __s223;
int __m224;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t18 = msg->t18;
double *t19 = msg->t19;
int __s223 = msg->__s223;
int __m224 = msg->__m224;

for (j=0; j<__m224; j+=__s223) {
// 2_2
int __m223 = j + __s223 > __m224 ? __m224 - j : __s223;
double *t30 = t19 + j*P_ncols;
double *t29 = t18 + j*P_ncols;
for (k=0; k<__m223; k+=1) {
// 2_3
double *t40 = t30 + k*P_ncols;
double *t39 = t29 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t40[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t51 = P + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t40[p] += (t39[l]*t51[p]);
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

int __s225 = 2;

int __s223 = 512;

int nparts__s224 = 12;
int __s224;
if (nparts__s224 > 1 && P_ncols > nparts__s224) {
__s224 = P_ncols/nparts__s224;
// this will fail if P_ncols%nparts__s224+__s224 > nparts__s224
// which primarily effects small sizes
if (P_ncols%nparts__s224)
++__s224;
}
else {
__s224 = P_ncols;
nparts__s224 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*__s225);
double *t20 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t20;
double *t11 = t20;
double *t10 = A;
double *t8 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s224);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s224);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s224,ii+=1) {
// 2_1
int __m224 = i + __s224 > P_ncols ? P_ncols - i : __s224;
double *t19 = t20 + i*P_ncols;
double *t18 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t18 = t18;
predict_0[disp].t19 = t19;
predict_0[disp].__s223 = __s223;
predict_0[disp].__m224 = __m224;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s224; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s225) {
// 4_1
int __m225 = i + __s225 > P_ncols ? P_ncols - i : __s225;
double *t26 = P + i;
double *t28 = t14 + i*P_ncols;
double *t25 = Q + i;
for (j=0; j<P_ncols; j+=1) {
// 4_2
double *t33 = t22 + j*__m225;
double *t32 = t9 + j*P_ncols;
for (k=0; k<__m225; k+=1) {
// 4_3
double *t49 = t28 + k*P_ncols;
t33[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t33[k] += (t32[l]*t49[l]);
}
}
}
for (j=0; j<P_ncols; j+=1) {
// 6_2
double *t37 = t26 + j*P_ncols;
double *t35 = t22 + j*__m225;
double *t36 = t25 + j*P_ncols;
for (k=0; k<__m225; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t22);
free(t20);
}
