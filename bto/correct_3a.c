#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int temp_ncols;
double *t22;
double *t21;
double *t23;
int __m299;
} correct3a_1_msg_t;

typedef struct { 
int P_ncols;
double *C;
int temp_ncols;
double *t19;
int __m297;
double *P;
double *t15;
int __s297;
} correct3a_0_msg_t;

void *correct3a_body_0(void *mesg) {
int disp, __zr__,j,k,l;
correct3a_0_msg_t *msg = (correct3a_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *C = msg->C;
int temp_ncols = msg->temp_ncols;
double *t19 = msg->t19;
int __m297 = msg->__m297;
double *P = msg->P;
double *t15 = msg->t15;
int __s297 = msg->__s297;

double *t16 = malloc(sizeof(double)*__s297*P_ncols);
for (j=0; j<__m297; j+=1) {
// 2_2
double *t26 = t16 + j*P_ncols;
double *t25 = t15 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t26[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t36 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t26[l] += (t25[k]*t36[l]);
}
}
}
for (j=0; j<__m297; j+=1) {
// 4_2
double *t29 = t19 + j*temp_ncols;
double *t28 = t16 + j*P_ncols;
for (k=0; k<temp_ncols; k+=1) {
// 4_3
double *t46 = C + k*P_ncols;
t29[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t29[k] += (t28[l]*t46[l]);
}
}
}
free(t16);
return NULL;
}


void *correct3a_body_1(void *mesg) {
int disp, __zr__,j,k;
correct3a_1_msg_t *msg = (correct3a_1_msg_t*)mesg;
int temp_ncols = msg->temp_ncols;
double *t22 = msg->t22;
double *t21 = msg->t21;
double *t23 = msg->t23;
int __m299 = msg->__m299;

for (j=0; j<__m299; j+=1) {
// 6_2
double *t33 = t23 + j*temp_ncols;
double *t31 = t21 + j*temp_ncols;
double *t32 = t22 + j*temp_ncols;
for (k=0; k<temp_ncols; k+=1) {
// 6_3
t33[k] = (t31[k]+t32[k]);
}
}
return NULL;
}


void correct3a
(int C_nrows, int C_ncols, double* C, int P_nrows, int P_ncols, double* P, int R_nrows, int R_ncols, double* R, int temp_nrows, int temp_ncols, double* temp)
{
int disp, __zr__,i,ii;

int nparts__s297 = 6;
int __s297;
if (nparts__s297 > 1 && temp_ncols > nparts__s297) {
__s297 = temp_ncols/nparts__s297;
// this will fail if temp_ncols%nparts__s297+__s297 > nparts__s297
// which primarily effects small sizes
if (temp_ncols%nparts__s297)
++__s297;
}
else {
__s297 = temp_ncols;
nparts__s297 = 1;
}

int nparts__s299 = 10;
int __s299;
if (nparts__s299 > 1 && temp_ncols > nparts__s299) {
__s299 = temp_ncols/nparts__s299;
// this will fail if temp_ncols%nparts__s299+__s299 > nparts__s299
// which primarily effects small sizes
if (temp_ncols%nparts__s299)
++__s299;
}
else {
__s299 = temp_ncols;
nparts__s299 = 1;
}

double *t20 = malloc(sizeof(double)*temp_ncols*temp_ncols);
double *t12 = t20;
double *t11 = t20;
double *t8 = C;
correct3a_0_msg_t *correct3a_0 = malloc(sizeof(correct3a_0_msg_t)*nparts__s297);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s297);
disp = 0;
for (i=0,ii=0; i<temp_ncols; i+=__s297,ii+=1) {
// 2_1
int __m297 = i + __s297 > temp_ncols ? temp_ncols - i : __s297;
double *t19 = t20 + i*temp_ncols;
double *t15 = t8 + i*P_ncols;
correct3a_0[disp].P_ncols = P_ncols;
correct3a_0[disp].C = C;
correct3a_0[disp].temp_ncols = temp_ncols;
correct3a_0[disp].t19 = t19;
correct3a_0[disp].__m297 = __m297;
correct3a_0[disp].P = P;
correct3a_0[disp].t15 = t15;
correct3a_0[disp].__s297 = __s297;

pthread_create(&threads_0[disp], NULL, correct3a_body_0, (void *)(correct3a_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s297; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(correct3a_0);
correct3a_1_msg_t *correct3a_1 = malloc(sizeof(correct3a_1_msg_t)*nparts__s299);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s299);
disp = 0;
for (i=0,ii=0; i<temp_ncols; i+=__s299,ii+=1) {
// 6_1
int __m299 = i + __s299 > temp_ncols ? temp_ncols - i : __s299;
double *t23 = temp + i*temp_ncols;
double *t21 = t12 + i*temp_ncols;
double *t22 = R + i*temp_ncols;
correct3a_1[disp].temp_ncols = temp_ncols;
correct3a_1[disp].t22 = t22;
correct3a_1[disp].t21 = t21;
correct3a_1[disp].t23 = t23;
correct3a_1[disp].__m299 = __m299;

pthread_create(&threads_1[disp], NULL, correct3a_body_1, (void *)(correct3a_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s299; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(correct3a_1);
free(t20);
}
