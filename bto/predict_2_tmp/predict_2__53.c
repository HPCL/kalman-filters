#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t29;
double *t28;
double *t30;
int __s178;
int __m179;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t25;
double *t26;
int __s176;
int __m177;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *P;
double *t22;
double *t23;
int __s174;
int __m175;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
double *t22 = msg->t22;
double *t23 = msg->t23;
int __s174 = msg->__s174;
int __m175 = msg->__m175;

for (j=0; j<__m175; j+=__s174) {
// 2_2
int __m174 = j + __s174 > __m175 ? __m175 - j : __s174;
double *t33 = t23 + j*P_ncols;
double *t32 = t22 + j*P_ncols;
for (k=0; k<__m174; k+=1) {
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
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t25 = msg->t25;
double *t26 = msg->t26;
int __s176 = msg->__s176;
int __m177 = msg->__m177;

for (j=0; j<__m177; j+=__s176) {
// 4_2
int __m176 = j + __s176 > __m177 ? __m177 - j : __s176;
double *t36 = t26 + j*P_ncols;
double *t35 = t25 + j*P_ncols;
for (k=0; k<__m176; k+=1) {
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
return NULL;
}


void *predict_body_2(void *mesg) {
int disp, __zr__,j,k,l;
predict_2_msg_t *msg = (predict_2_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t28 = msg->t28;
double *t30 = msg->t30;
int __s178 = msg->__s178;
int __m179 = msg->__m179;

for (j=0; j<__m179; j+=__s178) {
// 6_2
int __m178 = j + __s178 > __m179 ? __m179 - j : __s178;
double *t40 = t30 + j*P_ncols;
double *t38 = t28 + j*P_ncols;
double *t39 = t29 + j*P_ncols;
for (k=0; k<__m178; k+=1) {
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
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s178 = 512;

int __s176 = 512;

int __s174 = 512;

int nparts__s179 = 10;
int __s179;
if (nparts__s179 > 1 && P_ncols > nparts__s179) {
__s179 = P_ncols/nparts__s179;
// this will fail if P_ncols%nparts__s179+__s179 > nparts__s179
// which primarily effects small sizes
if (P_ncols%nparts__s179)
++__s179;
}
else {
__s179 = P_ncols;
nparts__s179 = 1;
}

int nparts__s177 = 10;
int __s177;
if (nparts__s177 > 1 && P_ncols > nparts__s177) {
__s177 = P_ncols/nparts__s177;
// this will fail if P_ncols%nparts__s177+__s177 > nparts__s177
// which primarily effects small sizes
if (P_ncols%nparts__s177)
++__s177;
}
else {
__s177 = P_ncols;
nparts__s177 = 1;
}

int nparts__s175 = 10;
int __s175;
if (nparts__s175 > 1 && P_ncols > nparts__s175) {
__s175 = P_ncols/nparts__s175;
// this will fail if P_ncols%nparts__s175+__s175 > nparts__s175
// which primarily effects small sizes
if (P_ncols%nparts__s175)
++__s175;
}
else {
__s175 = P_ncols;
nparts__s175 = 1;
}

double *t27 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = t27;
double *t16 = t27;
double *t13 = t27;
double *t15 = t27;
double *t14 = t24;
double *t12 = t24;
double *t9 = t24;
double *t11 = t24;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s175);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s175);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s175,ii+=1) {
// 2_1
int __m175 = i + __s175 > P_ncols ? P_ncols - i : __s175;
double *t23 = t24 + i*P_ncols;
double *t22 = t10 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].P = P;
predict_0[disp].t22 = t22;
predict_0[disp].t23 = t23;
predict_0[disp].__s174 = __s174;
predict_0[disp].__m175 = __m175;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s175; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s177);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s177);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s177,ii+=1) {
// 4_1
int __m177 = i + __s177 > P_ncols ? P_ncols - i : __s177;
double *t26 = t27 + i*P_ncols;
double *t25 = t14 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].A = A;
predict_1[disp].t25 = t25;
predict_1[disp].t26 = t26;
predict_1[disp].__s176 = __s176;
predict_1[disp].__m177 = __m177;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s177; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s179);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s179);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s179,ii+=1) {
// 6_1
int __m179 = i + __s179 > P_ncols ? P_ncols - i : __s179;
double *t30 = P + i*P_ncols;
double *t28 = t19 + i*P_ncols;
double *t29 = Q + i*P_ncols;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t29 = t29;
predict_2[disp].t28 = t28;
predict_2[disp].t30 = t30;
predict_2[disp].__s178 = __s178;
predict_2[disp].__m179 = __m179;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s179; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t27);
free(t24);
}
