#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int A_ncols;
double *t16;
int __m35;
double *t20;
double *xh;
double *t21;
int __s34;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *t16 = msg->t16;
int __m35 = msg->__m35;
double *t20 = msg->t20;
double *xh = msg->xh;
double *t21 = msg->t21;
int __s34 = msg->__s34;

for (j=0; j<xh_ncols; j+=__s34) {
// 2_2
int __m34 = j + __s34 > xh_ncols ? xh_ncols - j : __s34;
double *t31 = malloc(sizeof(double)*__s34);
double *t28 = t21 + j;
double *t23 = xh + j;
double *t27 = t20 + j;
for (k=0; k<__m35; k+=1) {
// 2_3
double *t35 = t28 + k*xh_ncols;
double *t30 = t16 + k*A_ncols;
double *t34 = t27 + k*xh_ncols;
for (__zr__ = 0; __zr__ < __m34; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = t23 + l*xh_ncols;
for (p=0; p<__m34; p+=1) {
// 2_5
t31[p] += (t30[l]*t38[p]);
}
}
for (l=0; l<__m34; l+=1) {
// 4_4
t35[l] = (t31[l]+t34[l]);
}
}
free(t31);
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii;

int __s34 = 512;

int nparts__s35 = 12;
int __s35;
if (nparts__s35 > 1 && A_nrows > nparts__s35) {
__s35 = A_nrows/nparts__s35;
// this will fail if A_nrows%nparts__s35+__s35 > nparts__s35
// which primarily effects small sizes
if (A_nrows%nparts__s35)
++__s35;
}
else {
__s35 = A_nrows;
nparts__s35 = 1;
}

predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s35);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s35);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s35,ii+=1) {
// 2_1
int __m35 = i + __s35 > A_nrows ? A_nrows - i : __s35;
double *t21 = xhn + i*xh_ncols;
double *t16 = A + i*A_ncols;
double *t20 = Y + i*xh_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t16 = t16;
predict1_0[disp].__m35 = __m35;
predict1_0[disp].t20 = t20;
predict1_0[disp].xh = xh;
predict1_0[disp].t21 = t21;
predict1_0[disp].__s34 = __s34;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s35; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
}
