#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m1543;
double *t21;
double *t27;
double *t10;
int __s1542;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m1543 = msg->__m1543;
double *t21 = msg->t21;
double *t27 = msg->t27;
double *t10 = msg->t10;
int __s1542 = msg->__s1542;

for (j=0; j<P_ncols; j+=__s1542) {
// 4_2
int __m1542 = j + __s1542 > P_ncols ? P_ncols - j : __s1542;
double *t31 = t10 + j;
double *t39 = t27 + j;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t45 = t21 + k*P_ncols;
double *t44 = t31 + k*P_ncols;
for (l=0; l<__m1543; l+=1) {
// 4_4
double *t53 = t39 + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<__m1542; p+=1) {
// 4_5
t45[l] += (t44[p]*t53[p]);
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

int __s1542 = 504;

int __s1541 = 2;

int nparts__s1543 = 12;
int __s1543;
if (nparts__s1543 > 1 && P_ncols > nparts__s1543) {
__s1543 = P_ncols/nparts__s1543;
// this will fail if P_ncols%nparts__s1543+__s1543 > nparts__s1543
// which primarily effects small sizes
if (P_ncols%nparts__s1543)
++__s1543;
}
else {
__s1543 = P_ncols;
nparts__s1543 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t22;
double *t10 = t19;
double *t8 = A;
double *t15 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s1541) {
// 2_1
int __m1541 = i + __s1541 > P_ncols ? P_ncols - i : __s1541;
double *t16 = t8 + i;
double *t17 = P + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t29 = t19 + j*P_ncols;
double *t28 = t16 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t29[__zr__] = 0.0;
for (k=0; k<__m1541; k+=1) {
// 2_3
double *t41 = t17 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t29[l] += (t28[k]*t41[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1543);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1543);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1543,ii+=1) {
// 4_1
int __m1543 = i + __s1543 > P_ncols ? P_ncols - i : __s1543;
double *t21 = t22 + i;
double *t27 = t15 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m1543 = __m1543;
predict_0[disp].t21 = t21;
predict_0[disp].t27 = t27;
predict_0[disp].t10 = t10;
predict_0[disp].__s1542 = __s1542;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1543; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t25 = P + i*P_ncols;
double *t23 = t14 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t25[j] = (t23[j]+t24[j]);
}
}
free(t22);
free(t19);
}
