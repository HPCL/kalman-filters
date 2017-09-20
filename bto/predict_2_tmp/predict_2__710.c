#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m1657;
int P_ncols;
double *t28;
double *t27;
double *t29;
int __s1656;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t31;
int __m1655;
double *t10;
double *t25;
int __s1654;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t31 = msg->t31;
int __m1655 = msg->__m1655;
double *t10 = msg->t10;
double *t25 = msg->t25;
int __s1654 = msg->__s1654;

for (j=0; j<P_ncols; j+=__s1654) {
// 4_2
int __m1654 = j + __s1654 > P_ncols ? P_ncols - j : __s1654;
double *t36 = t25 + j*P_ncols;
double *t35 = t10 + j*P_ncols;
for (k=0; k<__m1654; k+=1) {
// 4_3
double *t47 = t36 + k*P_ncols;
double *t46 = t35 + k*P_ncols;
for (l=0; l<__m1655; l+=1) {
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
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m1657 = msg->__m1657;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s1656 = msg->__s1656;

for (j=0; j<P_ncols; j+=__s1656) {
// 6_2
int __m1656 = j + __s1656 > P_ncols ? P_ncols - j : __s1656;
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m1656; k+=1) {
// 6_3
double *t51 = t40 + k*P_ncols;
double *t49 = t38 + k*P_ncols;
double *t50 = t39 + k*P_ncols;
for (l=0; l<__m1657; l+=1) {
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

int __s1656 = 512;

int __s1654 = 512;

int __s1653 = 2;

int nparts__s1655 = 12;
int __s1655;
if (nparts__s1655 > 1 && P_ncols > nparts__s1655) {
__s1655 = P_ncols/nparts__s1655;
// this will fail if P_ncols%nparts__s1655+__s1655 > nparts__s1655
// which primarily effects small sizes
if (P_ncols%nparts__s1655)
++__s1655;
}
else {
__s1655 = P_ncols;
nparts__s1655 = 1;
}

int nparts__s1657 = 12;
int __s1657;
if (nparts__s1657 > 1 && P_ncols > nparts__s1657) {
__s1657 = P_ncols/nparts__s1657;
// this will fail if P_ncols%nparts__s1657+__s1657 > nparts__s1657
// which primarily effects small sizes
if (P_ncols%nparts__s1657)
++__s1657;
}
else {
__s1657 = P_ncols;
nparts__s1657 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = t26;
double *t15 = t26;
double *t11 = t26;
double *t13 = t26;
double *t10 = t23;
double *t9 = t23;
double *t8 = A;
double *t14 = A;
for (i=0; i<P_ncols; i+=__s1653) {
// 2_1
int __m1653 = i + __s1653 > P_ncols ? P_ncols - i : __s1653;
double *t22 = t23 + i*P_ncols;
double *t21 = t8 + i*P_ncols;
for (j=0; j<__m1653; j+=1) {
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1655);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1655);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1655,ii+=1) {
// 4_1
int __m1655 = i + __s1655 > P_ncols ? P_ncols - i : __s1655;
double *t25 = t26 + i;
double *t31 = t14 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t31 = t31;
predict_0[disp].__m1655 = __m1655;
predict_0[disp].t10 = t10;
predict_0[disp].t25 = t25;
predict_0[disp].__s1654 = __s1654;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1655; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1657);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1657);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1657,ii+=1) {
// 6_1
int __m1657 = i + __s1657 > P_ncols ? P_ncols - i : __s1657;
double *t29 = P + i;
double *t27 = t18 + i;
double *t28 = Q + i;
predict_1[disp].__m1657 = __m1657;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s1656 = __s1656;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1657; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t26);
free(t23);
}
