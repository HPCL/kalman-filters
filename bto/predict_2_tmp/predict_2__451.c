#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t36;
double *A;
double *t29;
double *t18;
int __s1186;
int __m1187;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t36 = msg->t36;
double *A = msg->A;
double *t29 = msg->t29;
double *t18 = msg->t18;
int __s1186 = msg->__s1186;
int __m1187 = msg->__m1187;

for (j=0; j<__m1187; j+=__s1186) {
// 2_2
int __m1186 = j + __s1186 > __m1187 ? __m1187 - j : __s1186;
double *t31 = malloc(sizeof(double)*P_ncols*__s1186);
double *t30 = t18 + j;
double *t41 = t29 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t43 = t31 + k*__m1186;
double *t42 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m1186; ++__zr__) t43[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t49 = t30 + l*P_ncols;
for (p=0; p<__m1186; p+=1) {
// 2_5
t43[p] += (t42[l]*t49[p]);
}
}
}
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t46 = t36 + k*P_ncols;
double *t45 = t31 + k*__m1186;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t55 = t41 + l*P_ncols;
t46[l] = 0.0;
for (p=0; p<__m1186; p+=1) {
// 4_5
t46[l] += (t45[p]*t55[p]);
}
}
}
free(t31);
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j;

int __s1186 = 512;

int nparts__s1187 = 12;
int __s1187;
if (nparts__s1187 > 1 && P_ncols > nparts__s1187) {
__s1187 = P_ncols/nparts__s1187;
// this will fail if P_ncols%nparts__s1187+__s1187 > nparts__s1187
// which primarily effects small sizes
if (P_ncols%nparts__s1187)
++__s1187;
}
else {
__s1187 = P_ncols;
nparts__s1187 = 1;
}

double *t24 = malloc(sizeof(double)*nparts__s1187*P_ncols*P_ncols);
double *t63 = t24;
double *t17 = A;
double *t14 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1187);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1187);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1187,ii+=1) {
// 2_1
int __m1187 = i + __s1187 > P_ncols ? P_ncols - i : __s1187;
double *t36 = t24 + ii*P_ncols*P_ncols;
double *t18 = P + i;
double *t29 = t17 + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t36 = t36;
predict_0[disp].A = A;
predict_0[disp].t29 = t29;
predict_0[disp].t18 = t18;
predict_0[disp].__s1186 = __s1186;
predict_0[disp].__m1187 = __m1187;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1187; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1187,ii+=1) {
// 2_1
int __m1187 = i + __s1187 > P_ncols ? P_ncols - i : __s1187;
if ((ii == 0)) {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t63[__k*P_ncols+__l] = t24[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
} else {
for (__k = 0; __k < P_ncols; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t63[__k*P_ncols+__l] += t24[ii*P_ncols*P_ncols+__k*P_ncols+__l];
}
}
}
}
}

for (i=0; i<P_ncols; i+=1) {
// 6_1
double *t27 = P + i*P_ncols;
double *t25 = t63 + i*P_ncols;
double *t26 = Q + i*P_ncols;
for (j=0; j<P_ncols; j+=1) {
// 6_2
t27[j] = (t25[j]+t26[j]);
}
}
free(t24);
}
