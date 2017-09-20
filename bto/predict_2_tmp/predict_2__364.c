#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t31;
int __m985;
double *t12;
double *t25;
int __s984;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t21;
int __m983;
double *t20;
double *t22;
int __s982;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
int __m983 = msg->__m983;
double *t20 = msg->t20;
double *t22 = msg->t22;
int __s982 = msg->__s982;

for (j=0; j<P_ncols; j+=__s982) {
// 2_2
int __m982 = j + __s982 > P_ncols ? P_ncols - j : __s982;
double *t33 = t22 + j*P_ncols;
double *t32 = t20 + j*P_ncols;
for (k=0; k<__m982; k+=1) {
// 2_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<__m983; l+=1) {
// 2_4
double *t53 = t21 + l*P_ncols;
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
double *t31 = msg->t31;
int __m985 = msg->__m985;
double *t12 = msg->t12;
double *t25 = msg->t25;
int __s984 = msg->__s984;

for (j=0; j<P_ncols; j+=__s984) {
// 4_2
int __m984 = j + __s984 > P_ncols ? P_ncols - j : __s984;
double *t36 = t25 + j*P_ncols;
double *t35 = t12 + j*P_ncols;
for (k=0; k<__m984; k+=1) {
// 4_3
double *t46 = t36 + k*P_ncols;
double *t45 = t35 + k*P_ncols;
for (l=0; l<__m985; l+=1) {
// 4_4
double *t59 = t31 + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t46[l] += (t45[p]*t59[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k;

int __s986 = 2;

int __s984 = 512;

int __s982 = 512;

int nparts__s983 = 12;
int __s983;
if (nparts__s983 > 1 && P_ncols > nparts__s983) {
__s983 = P_ncols/nparts__s983;
// this will fail if P_ncols%nparts__s983+__s983 > nparts__s983
// which primarily effects small sizes
if (P_ncols%nparts__s983)
++__s983;
}
else {
__s983 = P_ncols;
nparts__s983 = 1;
}

int nparts__s985 = 12;
int __s985;
if (nparts__s985 > 1 && P_ncols > nparts__s985) {
__s985 = P_ncols/nparts__s985;
// this will fail if P_ncols%nparts__s985+__s985 > nparts__s985
// which primarily effects small sizes
if (P_ncols%nparts__s985)
++__s985;
}
else {
__s985 = P_ncols;
nparts__s985 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*nparts__s983*P_ncols*P_ncols);
double *t17 = t26;
double *t13 = t26;
double *t15 = t26;
double *t12 = t23;
double *t9 = t23;
double *t67 = t23;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s983);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s983);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s983,ii+=1) {
// 2_1
int __m983 = i + __s983 > P_ncols ? P_ncols - i : __s983;
double *t22 = t23 + ii*P_ncols*P_ncols;
double *t20 = t10 + i;
double *t21 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].__m983 = __m983;
predict_0[disp].t20 = t20;
predict_0[disp].t22 = t22;
predict_0[disp].__s982 = __s982;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s983; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s983,ii+=1) {
// 2_1
int __m983 = i + __s983 > P_ncols ? P_ncols - i : __s983;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s982) {
int __m982 = __j + __s982 > P_ncols ? P_ncols - __j : __s982;
for (__k = 0; __k < __m982; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t67[__j*P_ncols+__k*P_ncols+__l] = t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s982) {
int __m982 = __j + __s982 > P_ncols ? P_ncols - __j : __s982;
for (__k = 0; __k < __m982; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t67[__j*P_ncols+__k*P_ncols+__l] += t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s985);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s985);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s985,ii+=1) {
// 4_1
int __m985 = i + __s985 > P_ncols ? P_ncols - i : __s985;
double *t25 = t26 + i;
double *t31 = t16 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t31 = t31;
predict_1[disp].__m985 = __m985;
predict_1[disp].t12 = t12;
predict_1[disp].t25 = t25;
predict_1[disp].__s984 = __s984;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s985; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
for (i=0; i<P_ncols; i+=__s986) {
// 6_1
int __m986 = i + __s986 > P_ncols ? P_ncols - i : __s986;
double *t29 = P + i*P_ncols;
double *t27 = t17 + i*P_ncols;
double *t28 = Q + i*P_ncols;
for (j=0; j<__m986; j+=1) {
// 6_2
double *t40 = t29 + j*P_ncols;
double *t38 = t27 + j*P_ncols;
double *t39 = t28 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t40[k] = (t38[k]+t39[k]);
}
}
}
free(t26);
free(t23);
}
