#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *A;
double *t20;
double *t21;
int __s258;
int __m259;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t20 = msg->t20;
double *t21 = msg->t21;
int __s258 = msg->__s258;
int __m259 = msg->__m259;

for (j=0; j<__m259; j+=__s258) {
// 4_2
int __m258 = j + __s258 > __m259 ? __m259 - j : __s258;
double *t31 = t21 + j*P_ncols;
double *t30 = t20 + j*P_ncols;
for (k=0; k<__m258; k+=1) {
// 4_3
double *t42 = t31 + k*P_ncols;
double *t41 = t30 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t54 = A + l*P_ncols;
t42[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t42[l] += (t41[p]*t54[p]);
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

int __s260 = 2;

int __s258 = 512;

int __s257 = 2;

int nparts__s259 = 12;
int __s259;
if (nparts__s259 > 1 && P_ncols > nparts__s259) {
__s259 = P_ncols/nparts__s259;
// this will fail if P_ncols%nparts__s259+__s259 > nparts__s259
// which primarily effects small sizes
if (P_ncols%nparts__s259)
++__s259;
}
else {
__s259 = P_ncols;
nparts__s259 = 1;
}

double *t22 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t19 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t14 = t22;
double *t11 = t22;
double *t13 = t22;
double *t12 = t19;
double *t10 = t19;
double *t9 = t19;
double *t8 = A;
for (i=0; i<P_ncols; i+=__s257) {
// 2_1
int __m257 = i + __s257 > P_ncols ? P_ncols - i : __s257;
double *t18 = t19 + i*P_ncols;
double *t17 = t8 + i*P_ncols;
for (j=0; j<__m257; j+=1) {
// 2_2
double *t28 = t18 + j*P_ncols;
double *t27 = t17 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t28[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t38 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t28[l] += (t27[k]*t38[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s259);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s259);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s259,ii+=1) {
// 4_1
int __m259 = i + __s259 > P_ncols ? P_ncols - i : __s259;
double *t21 = t22 + i*P_ncols;
double *t20 = t12 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t20 = t20;
predict_0[disp].t21 = t21;
predict_0[disp].__s258 = __s258;
predict_0[disp].__m259 = __m259;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s259; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s260) {
// 6_1
int __m260 = i + __s260 > P_ncols ? P_ncols - i : __s260;
double *t25 = P + i*P_ncols;
double *t23 = t14 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<__m260; j+=1) {
// 6_2
double *t35 = t25 + j*P_ncols;
double *t33 = t23 + j*P_ncols;
double *t34 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t35[k] = (t33[k]+t34[k]);
}
}
}
free(t22);
free(t19);
}
