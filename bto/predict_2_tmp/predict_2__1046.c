#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m2708;
double *t29;
double *t30;
int __s2709;
double *t9;
double *t32;
int __s2707;
int __s2708;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m2708 = msg->__m2708;
double *t29 = msg->t29;
double *t30 = msg->t30;
int __s2709 = msg->__s2709;
double *t9 = msg->t9;
double *t32 = msg->t32;
int __s2707 = msg->__s2707;
int __s2708 = msg->__s2708;

double *t26 = malloc(sizeof(double)*__s2708*P_ncols);
for (j=0; j<__m2708; j+=__s2707) {
// 4_2
int __m2707 = j + __s2707 > __m2708 ? __m2708 - j : __s2707;
double *t37 = t26 + j;
double *t43 = t32 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t49 = t37 + k*__m2708;
double *t48 = t9 + k*P_ncols;
for (l=0; l<__m2707; l+=1) {
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
for (j=0; j<__m2708; j+=__s2709) {
// 6_2
int __m2709 = j + __s2709 > __m2708 ? __m2708 - j : __s2709;
double *t41 = t30 + j;
double *t39 = t26 + j;
double *t40 = t29 + j;
for (k=0; k<P_ncols; k+=1) {
// 6_3
double *t53 = t41 + k*P_ncols;
double *t51 = t39 + k*__m2708;
double *t52 = t40 + k*P_ncols;
for (l=0; l<__m2709; l+=1) {
// 6_4
t53[l] = (t51[l]+t52[l]);
}
}
}
free(t26);
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k,l;

int __s2709 = 504;

int __s2707 = 504;

int __s2706 = 2;

int nparts__s2708 = 10;
int __s2708;
if (nparts__s2708 > 1 && P_ncols > nparts__s2708) {
__s2708 = P_ncols/nparts__s2708;
// this will fail if P_ncols%nparts__s2708+__s2708 > nparts__s2708
// which primarily effects small sizes
if (P_ncols%nparts__s2708)
++__s2708;
}
else {
__s2708 = P_ncols;
nparts__s2708 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t9 = t24;
double *t8 = A;
double *t15 = A;
double *t12 = A;
for (i=0; i<P_ncols; i+=__s2706) {
// 2_1
int __m2706 = i + __s2706 > P_ncols ? P_ncols - i : __s2706;
double *t23 = t24 + i*P_ncols;
double *t22 = t8 + i*P_ncols;
for (j=0; j<__m2706; j+=1) {
// 2_2
double *t34 = t23 + j*P_ncols;
double *t33 = t22 + j*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t34[__zr__] = 0.0;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t45 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 2_4
t34[l] += (t33[k]*t45[l]);
}
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2708);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2708);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2708,ii+=1) {
// 4_1
int __m2708 = i + __s2708 > P_ncols ? P_ncols - i : __s2708;
double *t30 = P + i;
double *t32 = t15 + i*P_ncols;
double *t29 = Q + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].__m2708 = __m2708;
predict_0[disp].t29 = t29;
predict_0[disp].t30 = t30;
predict_0[disp].__s2709 = __s2709;
predict_0[disp].t9 = t9;
predict_0[disp].t32 = t32;
predict_0[disp].__s2707 = __s2707;
predict_0[disp].__s2708 = __s2708;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2708; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
free(t24);
}
