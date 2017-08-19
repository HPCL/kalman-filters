#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m218;
int xh_ncols;
double *t18;
double *t17;
double *t19;
int __s217;
int A_nrows;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int __m218 = msg->__m218;
int xh_ncols = msg->xh_ncols;
double *t18 = msg->t18;
double *t17 = msg->t17;
double *t19 = msg->t19;
int __s217 = msg->__s217;
int A_nrows = msg->A_nrows;

for (j=0; j<A_nrows; j+=__s217) {
// 4_2
int __m217 = j + __s217 > A_nrows ? A_nrows - j : __s217;
double *t26 = t19 + j*xh_ncols;
double *t24 = t17 + j*xh_ncols;
double *t25 = t18 + j*xh_ncols;
for (k=0; k<__m217; k+=1) {
// 4_3
double *t34 = t26 + k*xh_ncols;
double *t32 = t24 + k*xh_ncols;
double *t33 = t25 + k*xh_ncols;
for (l=0; l<__m218; l+=1) {
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

int __s217 = 512;

int __s216 = 2;

int nparts__s218 = 8;
int __s218;
if (nparts__s218 > 1 && xh_ncols > nparts__s218) {
__s218 = xh_ncols/nparts__s218;
// this will fail if xh_ncols%nparts__s218+__s218 > nparts__s218
// which primarily effects small sizes
if (xh_ncols%nparts__s218)
++__s218;
}
else {
__s218 = xh_ncols;
nparts__s218 = 1;
}

double *t16 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t11 = t16;
double *t8 = t16;
double *t7 = t16;
for (i=0; i<A_nrows; i+=__s216) {
// 2_1
int __m216 = i + __s216 > A_nrows ? A_nrows - i : __s216;
double *t15 = t16 + i*xh_ncols;
double *t14 = A + i*A_ncols;
for (j=0; j<__m216; j+=1) {
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
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s218);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s218);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s218,ii+=1) {
// 4_1
int __m218 = i + __s218 > xh_ncols ? xh_ncols - i : __s218;
double *t19 = xhn + i;
double *t17 = t11 + i;
double *t18 = Y + i;
predict1_0[disp].__m218 = __m218;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].t18 = t18;
predict1_0[disp].t17 = t17;
predict1_0[disp].t19 = t19;
predict1_0[disp].__s217 = __s217;
predict1_0[disp].A_nrows = A_nrows;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s218; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
free(t16);
}
