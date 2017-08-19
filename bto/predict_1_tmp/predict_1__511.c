#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int A_ncols;
double *t10;
int __m592;
double *xh;
double *t11;
int __s591;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *t10 = msg->t10;
int __m592 = msg->__m592;
double *xh = msg->xh;
double *t11 = msg->t11;
int __s591 = msg->__s591;

for (j=0; j<xh_ncols; j+=__s591) {
// 2_2
int __m591 = j + __s591 > xh_ncols ? xh_ncols - j : __s591;
double *t18 = t11 + j;
double *t17 = xh + j;
for (k=0; k<__m592; k+=1) {
// 2_3
double *t25 = t18 + k*xh_ncols;
double *t24 = t10 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m591; ++__zr__) t25[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t28 = t17 + l*xh_ncols;
for (p=0; p<__m591; p+=1) {
// 2_5
t25[p] += (t24[l]*t28[p]);
}
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii,j;

int __s591 = 504;

int nparts__s592 = 4;
int __s592;
if (nparts__s592 > 1 && A_nrows > nparts__s592) {
__s592 = A_nrows/nparts__s592;
// this will fail if A_nrows%nparts__s592+__s592 > nparts__s592
// which primarily effects small sizes
if (A_nrows%nparts__s592)
++__s592;
}
else {
__s592 = A_nrows;
nparts__s592 = 1;
}

double *t12 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t7 = t12;
double *t9 = t12;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s592);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s592);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s592,ii+=1) {
// 2_1
int __m592 = i + __s592 > A_nrows ? A_nrows - i : __s592;
double *t11 = t12 + i*xh_ncols;
double *t10 = A + i*A_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t10 = t10;
predict1_0[disp].__m592 = __m592;
predict1_0[disp].xh = xh;
predict1_0[disp].t11 = t11;
predict1_0[disp].__s591 = __s591;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s592; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
for (i=0; i<A_nrows; i+=1) {
// 4_1
double *t15 = xhn + i*xh_ncols;
double *t13 = t7 + i*xh_ncols;
double *t14 = Y + i*xh_ncols;
for (j=0; j<xh_ncols; j+=1) {
// 4_2
t15[j] = (t13[j]+t14[j]);
}
}
free(t12);
}
