#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m446;
int P_ncols;
double *t27;
double *t26;
double *t28;
int __s445;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t21;
int __m443;
double *P;
double *t20;
int __s442;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
int __m443 = msg->__m443;
double *P = msg->P;
double *t20 = msg->t20;
int __s442 = msg->__s442;

for (j=0; j<P_ncols; j+=__s442) {
// 2_2
int __m442 = j + __s442 > P_ncols ? P_ncols - j : __s442;
double *t30 = t20 + j;
double *t31 = P + j*P_ncols;
for (k=0; k<__m443; k+=1) {
// 2_3
double *t42 = t21 + k*P_ncols;
double *t41 = t30 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t42[__zr__] = 0.0;
for (l=0; l<__m442; l+=1) {
// 2_4
double *t53 = t31 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t42[p] += (t41[l]*t53[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m446 = msg->__m446;
int P_ncols = msg->P_ncols;
double *t27 = msg->t27;
double *t26 = msg->t26;
double *t28 = msg->t28;
int __s445 = msg->__s445;

for (j=0; j<P_ncols; j+=__s445) {
// 6_2
int __m445 = j + __s445 > P_ncols ? P_ncols - j : __s445;
double *t39 = t28 + j*P_ncols;
double *t37 = t26 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
for (k=0; k<__m445; k+=1) {
// 6_3
double *t49 = t39 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
for (l=0; l<__m446; l+=1) {
// 6_4
t49[l] = (t47[l]+t48[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s445 = 512;

int __s444 = 10;

int __s442 = 512;

int nparts__s443 = 12;
int __s443;
if (nparts__s443 > 1 && P_ncols > nparts__s443) {
__s443 = P_ncols/nparts__s443;
// this will fail if P_ncols%nparts__s443+__s443 > nparts__s443
// which primarily effects small sizes
if (P_ncols%nparts__s443)
++__s443;
}
else {
__s443 = P_ncols;
nparts__s443 = 1;
}

int nparts__s446 = 10;
int __s446;
if (nparts__s446 > 1 && P_ncols > nparts__s446) {
__s446 = P_ncols/nparts__s446;
// this will fail if P_ncols%nparts__s446+__s446 > nparts__s446
// which primarily effects small sizes
if (P_ncols%nparts__s446)
++__s446;
}
else {
__s446 = P_ncols;
nparts__s446 = 1;
}

double *t25 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t17 = t25;
double *t14 = t25;
double *t13 = t25;
double *t12 = t22;
double *t11 = t22;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s443);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s443);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s443,ii+=1) {
// 2_1
int __m443 = i + __s443 > P_ncols ? P_ncols - i : __s443;
double *t21 = t22 + i*P_ncols;
double *t20 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].__m443 = __m443;
predict_0[disp].P = P;
predict_0[disp].t20 = t20;
predict_0[disp].__s442 = __s442;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s443; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s444) {
// 4_1
int __m444 = i + __s444 > P_ncols ? P_ncols - i : __s444;
double *t24 = t25 + i*P_ncols;
double *t23 = t12 + i*P_ncols;
for (j=0; j<__m444; j+=1) {
// 4_2
double *t35 = t24 + j*P_ncols;
double *t34 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t51 = A + k*P_ncols;
t35[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t35[k] += (t34[l]*t51[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s446);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s446);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s446,ii+=1) {
// 6_1
int __m446 = i + __s446 > P_ncols ? P_ncols - i : __s446;
double *t28 = P + i;
double *t26 = t17 + i;
double *t27 = Q + i;
predict_1[disp].__m446 = __m446;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t27 = t27;
predict_1[disp].t26 = t26;
predict_1[disp].t28 = t28;
predict_1[disp].__s445 = __s445;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s446; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t25);
free(t22);
}
