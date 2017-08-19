#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
double *t20;
double *t19;
double *t21;
int __s234;
int __m235;
} predict1_1_msg_t;

typedef struct { 
int xh_ncols;
double *xh;
int A_ncols;
double *t16;
double *t17;
int __s232;
int __m233;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
double *xh = msg->xh;
int A_ncols = msg->A_ncols;
double *t16 = msg->t16;
double *t17 = msg->t17;
int __s232 = msg->__s232;
int __m233 = msg->__m233;

for (j=0; j<__m233; j+=__s232) {
// 2_2
int __m232 = j + __s232 > __m233 ? __m233 - j : __s232;
double *t24 = t17 + j*xh_ncols;
double *t23 = t16 + j*A_ncols;
for (k=0; k<__m232; k+=1) {
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
return NULL;
}


void *predict1_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict1_1_msg_t *msg = (predict1_1_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
double *t20 = msg->t20;
double *t19 = msg->t19;
double *t21 = msg->t21;
int __s234 = msg->__s234;
int __m235 = msg->__m235;

for (j=0; j<__m235; j+=__s234) {
// 4_2
int __m234 = j + __s234 > __m235 ? __m235 - j : __s234;
double *t28 = t21 + j*xh_ncols;
double *t26 = t19 + j*xh_ncols;
double *t27 = t20 + j*xh_ncols;
for (k=0; k<__m234; k+=1) {
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
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii;

int __s234 = 512;

int __s232 = 512;

int nparts__s235 = 8;
int __s235;
if (nparts__s235 > 1 && A_nrows > nparts__s235) {
__s235 = A_nrows/nparts__s235;
// this will fail if A_nrows%nparts__s235+__s235 > nparts__s235
// which primarily effects small sizes
if (A_nrows%nparts__s235)
++__s235;
}
else {
__s235 = A_nrows;
nparts__s235 = 1;
}

int nparts__s233 = 8;
int __s233;
if (nparts__s233 > 1 && A_nrows > nparts__s233) {
__s233 = A_nrows/nparts__s233;
// this will fail if A_nrows%nparts__s233+__s233 > nparts__s233
// which primarily effects small sizes
if (A_nrows%nparts__s233)
++__s233;
}
else {
__s233 = A_nrows;
nparts__s233 = 1;
}

double *t18 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t13 = t18;
double *t10 = t18;
double *t7 = t18;
double *t9 = t18;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s233);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s233);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s233,ii+=1) {
// 2_1
int __m233 = i + __s233 > A_nrows ? A_nrows - i : __s233;
double *t17 = t18 + i*xh_ncols;
double *t16 = A + i*A_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].xh = xh;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t16 = t16;
predict1_0[disp].t17 = t17;
predict1_0[disp].__s232 = __s232;
predict1_0[disp].__m233 = __m233;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s233; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
predict1_1_msg_t *predict1_1 = malloc(sizeof(predict1_1_msg_t)*nparts__s235);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s235);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s235,ii+=1) {
// 4_1
int __m235 = i + __s235 > A_nrows ? A_nrows - i : __s235;
double *t21 = xhn + i*xh_ncols;
double *t19 = t13 + i*xh_ncols;
double *t20 = Y + i*xh_ncols;
predict1_1[disp].xh_ncols = xh_ncols;
predict1_1[disp].t20 = t20;
predict1_1[disp].t19 = t19;
predict1_1[disp].t21 = t21;
predict1_1[disp].__s234 = __s234;
predict1_1[disp].__m235 = __m235;

pthread_create(&threads_1[disp], NULL, predict1_body_1, (void *)(predict1_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s235; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict1_1);
free(t18);
}
