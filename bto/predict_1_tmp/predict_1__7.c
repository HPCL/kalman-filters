#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
double *xh;
int A_ncols;
double *t20;
double *t16;
double *t21;
int __s22;
int __m23;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
double *xh = msg->xh;
int A_ncols = msg->A_ncols;
double *t20 = msg->t20;
double *t16 = msg->t16;
double *t21 = msg->t21;
int __s22 = msg->__s22;
int __m23 = msg->__m23;

for (j=0; j<__m23; j+=__s22) {
// 2_2
int __m22 = j + __s22 > __m23 ? __m23 - j : __s22;
double *t24 = malloc(sizeof(double)*__s22*xh_ncols);
double *t28 = t21 + j*xh_ncols;
double *t23 = t16 + j*A_ncols;
double *t27 = t20 + j*xh_ncols;
for (k=0; k<__m22; k+=1) {
// 2_3
double *t31 = t24 + k*xh_ncols;
double *t30 = t23 + k*A_ncols;
for (__zr__ = 0; __zr__ < xh_ncols; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = xh + l*xh_ncols;
for (p=0; p<xh_ncols; p+=1) {
// 2_5
t31[p] += (t30[l]*t38[p]);
}
}
}
for (k=0; k<__m22; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t24 + k*xh_ncols;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<xh_ncols; l+=1) {
// 4_4
t35[l] = (t33[l]+t34[l]);
}
}
free(t24);
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii;

int __s22 = 512;

int nparts__s23 = 12;
int __s23;
if (nparts__s23 > 1 && A_nrows > nparts__s23) {
__s23 = A_nrows/nparts__s23;
// this will fail if A_nrows%nparts__s23+__s23 > nparts__s23
// which primarily effects small sizes
if (A_nrows%nparts__s23)
++__s23;
}
else {
__s23 = A_nrows;
nparts__s23 = 1;
}

predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s23);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s23);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s23,ii+=1) {
// 2_1
int __m23 = i + __s23 > A_nrows ? A_nrows - i : __s23;
double *t21 = xhn + i*xh_ncols;
double *t16 = A + i*A_ncols;
double *t20 = Y + i*xh_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].xh = xh;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t20 = t20;
predict1_0[disp].t16 = t16;
predict1_0[disp].t21 = t21;
predict1_0[disp].__s22 = __s22;
predict1_0[disp].__m23 = __m23;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s23; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
}
