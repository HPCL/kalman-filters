#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m362;
int xh_ncols;
double *t19;
double *t18;
double *t20;
int __s361;
int A_nrows;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int __m362 = msg->__m362;
int xh_ncols = msg->xh_ncols;
double *t19 = msg->t19;
double *t18 = msg->t18;
double *t20 = msg->t20;
int __s361 = msg->__s361;
int A_nrows = msg->A_nrows;

for (j=0; j<A_nrows; j+=__s361) {
// 4_2
int __m361 = j + __s361 > A_nrows ? A_nrows - j : __s361;
double *t27 = t20 + j*xh_ncols;
double *t25 = t18 + j*xh_ncols;
double *t26 = t19 + j*xh_ncols;
for (k=0; k<__m361; k+=1) {
// 4_3
double *t35 = t27 + k*xh_ncols;
double *t33 = t25 + k*xh_ncols;
double *t34 = t26 + k*xh_ncols;
for (l=0; l<__m362; l+=1) {
// 4_4
t35[l] = (t33[l]+t34[l]);
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii,j,k,l;

int __s361 = 512;

int __s360 = 10;

int nparts__s362 = 8;
int __s362;
if (nparts__s362 > 1 && xh_ncols > nparts__s362) {
__s362 = xh_ncols/nparts__s362;
// this will fail if xh_ncols%nparts__s362+__s362 > nparts__s362
// which primarily effects small sizes
if (xh_ncols%nparts__s362)
++__s362;
}
else {
__s362 = xh_ncols;
nparts__s362 = 1;
}

double *t17 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t11 = t17;
double *t8 = t17;
for (i=0; i<A_ncols; i+=__s360) {
// 2_1
int __m360 = i + __s360 > A_ncols ? A_ncols - i : __s360;
double *t14 = A + i;
double *t15 = xh + i*xh_ncols;
for (j=0; j<A_nrows; j+=1) {
// 2_2
double *t23 = t17 + j*xh_ncols;
double *t22 = t14 + j*A_ncols;
for (__zr__ = 0; __zr__ < xh_ncols; ++__zr__) t23[__zr__] = 0.0;
for (k=0; k<__m360; k+=1) {
// 2_3
double *t30 = t15 + k*xh_ncols;
for (l=0; l<xh_ncols; l+=1) {
// 2_4
t23[l] += (t22[k]*t30[l]);
}
}
}
}
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s362);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s362);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s362,ii+=1) {
// 4_1
int __m362 = i + __s362 > xh_ncols ? xh_ncols - i : __s362;
double *t20 = xhn + i;
double *t18 = t11 + i;
double *t19 = Y + i;
predict1_0[disp].__m362 = __m362;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].t19 = t19;
predict1_0[disp].t18 = t18;
predict1_0[disp].t20 = t20;
predict1_0[disp].__s361 = __s361;
predict1_0[disp].A_nrows = A_nrows;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s362; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
free(t17);
}
