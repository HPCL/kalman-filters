#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
double *t26;
int __m1659;
double *t8;
double *t20;
int __s1658;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t26 = msg->t26;
int __m1659 = msg->__m1659;
double *t8 = msg->t8;
double *t20 = msg->t20;
int __s1658 = msg->__s1658;

for (j=0; j<P_ncols; j+=__s1658) {
// 4_2
int __m1658 = j + __s1658 > P_ncols ? P_ncols - j : __s1658;
double *t32 = t20 + j*P_ncols;
double *t31 = t8 + j*P_ncols;
for (k=0; k<__m1658; k+=1) {
// 4_3
double *t42 = t32 + k*P_ncols;
double *t41 = t31 + k*P_ncols;
for (l=0; l<__m1659; l+=1) {
// 4_4
double *t51 = t26 + l*P_ncols;
t42[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t42[l] += (t41[p]*t51[p]);
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

int __s1660 = 12;

int __s1658 = 512;

int nparts__s1659 = 12;
int __s1659;
if (nparts__s1659 > 1 && P_ncols > nparts__s1659) {
__s1659 = P_ncols/nparts__s1659;
// this will fail if P_ncols%nparts__s1659+__s1659 > nparts__s1659
// which primarily effects small sizes
if (P_ncols%nparts__s1659)
++__s1659;
}
else {
__s1659 = P_ncols;
nparts__s1659 = 1;
}

double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t21;
double *t9 = t21;
double *t11 = t21;
double *t12 = A;
double *t8 = t18;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t17 = t18 + i*P_ncols;
double *t16 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t17[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t28 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t17[k] += (t16[j]*t28[k]);
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1659);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1659);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1659,ii+=1) {
// 4_1
int __m1659 = i + __s1659 > P_ncols ? P_ncols - i : __s1659;
double *t20 = t21 + i;
double *t26 = t12 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t26 = t26;
predict_0[disp].__m1659 = __m1659;
predict_0[disp].t8 = t8;
predict_0[disp].t20 = t20;
predict_0[disp].__s1658 = __s1658;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1659; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
for (i=0; i<P_ncols; i+=__s1660) {
// 6_1
int __m1660 = i + __s1660 > P_ncols ? P_ncols - i : __s1660;
double *t24 = P + i*P_ncols;
double *t22 = t13 + i*P_ncols;
double *t23 = Q + i*P_ncols;
for (j=0; j<__m1660; j+=1) {
// 6_2
double *t36 = t24 + j*P_ncols;
double *t34 = t22 + j*P_ncols;
double *t35 = t23 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t36[k] = (t34[k]+t35[k]);
}
}
}
free(t21);
free(t18);
}
