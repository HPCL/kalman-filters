#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t29;
double *t28;
double *t30;
int __s4165;
int __m4166;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t9;
double *t32;
double *t26;
int __s4163;
int __m4164;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t9 = msg->t9;
double *t32 = msg->t32;
double *t26 = msg->t26;
int __s4163 = msg->__s4163;
int __m4164 = msg->__m4164;

for (j=0; j<__m4164; j+=__s4163) {
// 4_2
int __m4163 = j + __s4163 > __m4164 ? __m4164 - j : __s4163;
double *t37 = t26 + j;
double *t43 = t32 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t49 = t37 + k*P_ncols;
double *t48 = t9 + k*P_ncols;
for (l=0; l<__m4163; l+=1) {
// 4_4
double *t65 = t43 + l*P_ncols;
t49[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t49[l] += (t48[p]*t65[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
double *t28 = msg->t28;
double *t30 = msg->t30;
int __s4165 = msg->__s4165;
int __m4166 = msg->__m4166;

for (j=0; j<__m4166; j+=__s4165) {
// 6_2
int __m4165 = j + __s4165 > __m4166 ? __m4166 - j : __s4165;
double *t41 = t30 + j;
double *t39 = t28 + j;
double *t40 = t29 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t53 = t41 + k*P_ncols;
double *t51 = t39 + k*P_ncols;
double *t52 = t40 + k*P_ncols;
for (l=0; l<__m4165; l+=1) {
// 6_4
t53[l] = (t51[l]+t52[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s4165 = 504;

int __s4163 = 488;

int __s4162 = 12;

int nparts__s4166 = 12;
int __s4166;
if (nparts__s4166 > 1 && P_ncols > nparts__s4166) {
__s4166 = P_ncols/nparts__s4166;
// this will fail if P_ncols%nparts__s4166+__s4166 > nparts__s4166
// which primarily effects small sizes
if (P_ncols%nparts__s4166)
++__s4166;
}
else {
__s4166 = P_ncols;
nparts__s4166 = 1;
}

int nparts__s4164 = 12;
int __s4164;
if (nparts__s4164 > 1 && P_ncols > nparts__s4164) {
__s4164 = P_ncols/nparts__s4164;
// this will fail if P_ncols%nparts__s4164+__s4164 > nparts__s4164
// which primarily effects small sizes
if (P_ncols%nparts__s4164)
++__s4164;
}
else {
__s4164 = P_ncols;
nparts__s4164 = 1;
}

double *t27 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = t27;
double *t16 = t27;
double *t11 = t27;
double *t14 = t27;
double *t15 = A;
double *t12 = A;
double *t9 = t24;
for (i=0; i<P_ncols; i+=__s4162) {
// 2_1
int __m4162 = i + __s4162 > P_ncols ? P_ncols - i : __s4162;
double *t23 = t24 + i;
double *t22 = P + i;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t34 = t23 + j*P_ncols;
double *t33 = A + j*P_ncols;
for (__zr__ = 0; __zr__ < __m4162; ++__zr__) t34[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t45 = t22 + k*P_ncols;
for (l=0; l<__m4162; l+=1) {
// 2_4
t34[l] += (t33[k]*t45[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s4164);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s4164);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4164,ii+=1) {
// 4_1
int __m4164 = i + __s4164 > P_ncols ? P_ncols - i : __s4164;
double *t26 = t27 + i;
double *t32 = t15 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t9 = t9;
predict_0[disp].t32 = t32;
predict_0[disp].t26 = t26;
predict_0[disp].__s4163 = __s4163;
predict_0[disp].__m4164 = __m4164;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s4164; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s4166);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s4166);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s4166,ii+=1) {
// 6_1
int __m4166 = i + __s4166 > P_ncols ? P_ncols - i : __s4166;
double *t30 = P + i;
double *t28 = t19 + i;
double *t29 = Q + i;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t29 = t29;
predict_1[disp].t28 = t28;
predict_1[disp].t30 = t30;
predict_1[disp].__s4165 = __s4165;
predict_1[disp].__m4166 = __m4166;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s4166; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t27);
free(t24);
}
