#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
double *t20;
double *t21;
int __s156;
int __m155;
double *xh;
int A_ncols;
double *t16;
int __s154;
int __s155;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
double *t20 = msg->t20;
double *t21 = msg->t21;
int __s156 = msg->__s156;
int __m155 = msg->__m155;
double *xh = msg->xh;
int A_ncols = msg->A_ncols;
double *t16 = msg->t16;
int __s154 = msg->__s154;
int __s155 = msg->__s155;

double *t17 = malloc(sizeof(double)*__s155*xh_ncols);
for (j=0; j<__m155; j+=__s154) {
// 2_2
int __m154 = j + __s154 > __m155 ? __m155 - j : __s154;
double *t24 = t17 + j*xh_ncols;
double *t23 = t16 + j*A_ncols;
for (k=0; k<__m154; k+=1) {
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
}
for (j=0; j<__m155; j+=__s156) {
// 4_2
int __m156 = j + __s156 > __m155 ? __m155 - j : __s156;
double *t28 = t21 + j*xh_ncols;
double *t26 = t17 + j*xh_ncols;
double *t27 = t20 + j*xh_ncols;
for (k=0; k<__m156; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t26 + k*xh_ncols;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<xh_ncols; l+=1) {
// 4_4
t35[l] = (t33[l]+t34[l]);
}
}
}
free(t17);
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii;

int __s156 = 512;

int __s154 = 512;

int nparts__s155 = 10;
int __s155;
if (nparts__s155 > 1 && A_nrows > nparts__s155) {
__s155 = A_nrows/nparts__s155;
// this will fail if A_nrows%nparts__s155+__s155 > nparts__s155
// which primarily effects small sizes
if (A_nrows%nparts__s155)
++__s155;
}
else {
__s155 = A_nrows;
nparts__s155 = 1;
}

predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s155);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s155);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s155,ii+=1) {
// 2_1
int __m155 = i + __s155 > A_nrows ? A_nrows - i : __s155;
double *t21 = xhn + i*xh_ncols;
double *t16 = A + i*A_ncols;
double *t20 = Y + i*xh_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].t20 = t20;
predict1_0[disp].t21 = t21;
predict1_0[disp].__s156 = __s156;
predict1_0[disp].__m155 = __m155;
predict1_0[disp].xh = xh;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t16 = t16;
predict1_0[disp].__s154 = __s154;
predict1_0[disp].__s155 = __s155;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s155; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
}
