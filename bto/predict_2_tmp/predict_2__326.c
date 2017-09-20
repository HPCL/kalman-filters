#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t28;
double *t27;
double *t29;
int __s899;
int __m900;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t31;
int __m898;
double *t10;
double *t25;
int __s897;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t31 = msg->t31;
int __m898 = msg->__m898;
double *t10 = msg->t10;
double *t25 = msg->t25;
int __s897 = msg->__s897;

for (j=0; j<P_ncols; j+=__s897) {
// 4_2
int __m897 = j + __s897 > P_ncols ? P_ncols - j : __s897;
double *t36 = t25 + j*P_ncols;
double *t35 = t10 + j*P_ncols;
for (k=0; k<__m897; k+=1) {
// 4_3
double *t47 = t36 + k*P_ncols;
double *t46 = t35 + k*P_ncols;
for (l=0; l<__m898; l+=1) {
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
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s899 = msg->__s899;
int __m900 = msg->__m900;

for (j=0; j<__m900; j+=__s899) {
// 6_2
int __m899 = j + __s899 > __m900 ? __m900 - j : __s899;
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<__m899; k+=1) {
// 6_3
double *t51 = t40 + k*P_ncols;
double *t49 = t38 + k*P_ncols;
double *t50 = t39 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
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

int __s899 = 504;

int __s897 = 512;

int __s896 = 12;

int nparts__s900 = 12;
int __s900;
if (nparts__s900 > 1 && P_ncols > nparts__s900) {
__s900 = P_ncols/nparts__s900;
// this will fail if P_ncols%nparts__s900+__s900 > nparts__s900
// which primarily effects small sizes
if (P_ncols%nparts__s900)
++__s900;
}
else {
__s900 = P_ncols;
nparts__s900 = 1;
}

int nparts__s898 = 12;
int __s898;
if (nparts__s898 > 1 && P_ncols > nparts__s898) {
__s898 = P_ncols/nparts__s898;
// this will fail if P_ncols%nparts__s898+__s898 > nparts__s898
// which primarily effects small sizes
if (P_ncols%nparts__s898)
++__s898;
}
else {
__s898 = P_ncols;
nparts__s898 = 1;
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
for (i=0; i<P_ncols; i+=__s896) {
// 2_1
int __m896 = i + __s896 > P_ncols ? P_ncols - i : __s896;
double *t22 = t23 + i*P_ncols;
double *t21 = t8 + i*P_ncols;
for (j=0; j<__m896; j+=1) {
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
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s898);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s898);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s898,ii+=1) {
// 4_1
int __m898 = i + __s898 > P_ncols ? P_ncols - i : __s898;
double *t25 = t26 + i;
double *t31 = t14 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t31 = t31;
predict_0[disp].__m898 = __m898;
predict_0[disp].t10 = t10;
predict_0[disp].t25 = t25;
predict_0[disp].__s897 = __s897;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s898; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s900);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s900);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s900,ii+=1) {
// 6_1
int __m900 = i + __s900 > P_ncols ? P_ncols - i : __s900;
double *t29 = P + i*P_ncols;
double *t27 = t18 + i*P_ncols;
double *t28 = Q + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s899 = __s899;
predict_1[disp].__m900 = __m900;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s900; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t26);
free(t23);
}
