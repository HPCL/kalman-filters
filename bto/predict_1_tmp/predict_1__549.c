#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int __m633;
double *t18;
double *t17;
double *t19;
int __s632;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int __m633 = msg->__m633;
double *t18 = msg->t18;
double *t17 = msg->t17;
double *t19 = msg->t19;
int __s632 = msg->__s632;

for (j=0; j<xh_ncols; j+=__s632) {
// 4_2
int __m632 = j + __s632 > xh_ncols ? xh_ncols - j : __s632;
double *t26 = t19 + j;
double *t24 = t17 + j;
double *t25 = t18 + j;
for (k=0; k<__m633; k+=1) {
// 4_3
double *t34 = t26 + k*xh_ncols;
double *t32 = t24 + k*xh_ncols;
double *t33 = t25 + k*xh_ncols;
for (l=0; l<__m632; l+=1) {
// 4_4
t34[l] = (t32[l]+t33[l]);
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii,j,k,l;

int __s632 = 512;

int __s631 = 6;

int nparts__s633 = 6;
int __s633;
if (nparts__s633 > 1 && A_nrows > nparts__s633) {
__s633 = A_nrows/nparts__s633;
// this will fail if A_nrows%nparts__s633+__s633 > nparts__s633
// which primarily effects small sizes
if (A_nrows%nparts__s633)
++__s633;
}
else {
__s633 = A_nrows;
nparts__s633 = 1;
}

double *t16 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t11 = t16;
double *t8 = t16;
double *t7 = t16;
for (i=0; i<A_nrows; i+=__s631) {
// 2_1
int __m631 = i + __s631 > A_nrows ? A_nrows - i : __s631;
double *t15 = t16 + i*xh_ncols;
double *t14 = A + i*A_ncols;
for (j=0; j<__m631; j+=1) {
// 2_2
double *t22 = t15 + j*xh_ncols;
double *t21 = t14 + j*A_ncols;
for (__zr__ = 0; __zr__ < xh_ncols; ++__zr__) t22[__zr__] = 0.0;
for (k=0; k<A_ncols; k+=1) {
// 2_3
double *t29 = xh + k*xh_ncols;
for (l=0; l<xh_ncols; l+=1) {
// 2_4
t22[l] += (t21[k]*t29[l]);
}
}
}
}
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s633);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s633);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s633,ii+=1) {
// 4_1
int __m633 = i + __s633 > A_nrows ? A_nrows - i : __s633;
double *t19 = xhn + i*xh_ncols;
double *t17 = t11 + i*xh_ncols;
double *t18 = Y + i*xh_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].__m633 = __m633;
predict1_0[disp].t18 = t18;
predict1_0[disp].t17 = t17;
predict1_0[disp].t19 = t19;
predict1_0[disp].__s632 = __s632;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s633; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
free(t16);
}
