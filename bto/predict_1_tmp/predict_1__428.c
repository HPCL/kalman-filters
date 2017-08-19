#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int __m504;
double *t20;
double *t21;
int __s505;
int A_ncols;
double *t16;
double *xh;
int __s503;
int __s504;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int __m504 = msg->__m504;
double *t20 = msg->t20;
double *t21 = msg->t21;
int __s505 = msg->__s505;
int A_ncols = msg->A_ncols;
double *t16 = msg->t16;
double *xh = msg->xh;
int __s503 = msg->__s503;
int __s504 = msg->__s504;

double *t17 = malloc(sizeof(double)*xh_ncols*__s504);
for (j=0; j<xh_ncols; j+=__s503) {
// 2_2
int __m503 = j + __s503 > xh_ncols ? xh_ncols - j : __s503;
double *t24 = t17 + j;
double *t23 = xh + j;
for (k=0; k<__m504; k+=1) {
// 2_3
double *t31 = t24 + k*xh_ncols;
double *t30 = t16 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m503; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = t23 + l*xh_ncols;
for (p=0; p<__m503; p+=1) {
// 2_5
t31[p] += (t30[l]*t38[p]);
}
}
}
}
for (j=0; j<xh_ncols; j+=__s505) {
// 4_2
int __m505 = j + __s505 > xh_ncols ? xh_ncols - j : __s505;
double *t28 = t21 + j;
double *t26 = t17 + j;
double *t27 = t20 + j;
for (k=0; k<__m504; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t26 + k*xh_ncols;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<__m505; l+=1) {
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

int __s505 = 512;

int __s503 = 512;

int nparts__s504 = 8;
int __s504;
if (nparts__s504 > 1 && A_nrows > nparts__s504) {
__s504 = A_nrows/nparts__s504;
// this will fail if A_nrows%nparts__s504+__s504 > nparts__s504
// which primarily effects small sizes
if (A_nrows%nparts__s504)
++__s504;
}
else {
__s504 = A_nrows;
nparts__s504 = 1;
}

predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s504);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s504);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s504,ii+=1) {
// 2_1
int __m504 = i + __s504 > A_nrows ? A_nrows - i : __s504;
double *t21 = xhn + i*xh_ncols;
double *t16 = A + i*A_ncols;
double *t20 = Y + i*xh_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].__m504 = __m504;
predict1_0[disp].t20 = t20;
predict1_0[disp].t21 = t21;
predict1_0[disp].__s505 = __s505;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t16 = t16;
predict1_0[disp].xh = xh;
predict1_0[disp].__s503 = __s503;
predict1_0[disp].__s504 = __s504;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s504; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
}
