#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int A_nrows;
double *t20;
double *t19;
double *t21;
int __s431;
int __m432;
} predict1_1_msg_t;

typedef struct { 
int xh_ncols;
int A_ncols;
double *t16;
int __m430;
double *xh;
double *t17;
int __s429;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *t16 = msg->t16;
int __m430 = msg->__m430;
double *xh = msg->xh;
double *t17 = msg->t17;
int __s429 = msg->__s429;

for (j=0; j<xh_ncols; j+=__s429) {
// 2_2
int __m429 = j + __s429 > xh_ncols ? xh_ncols - j : __s429;
double *t24 = t17 + j;
double *t23 = xh + j;
for (k=0; k<__m430; k+=1) {
// 2_3
double *t31 = t24 + k*xh_ncols;
double *t30 = t16 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m429; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = t23 + l*xh_ncols;
for (p=0; p<__m429; p+=1) {
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
int A_nrows = msg->A_nrows;
double *t20 = msg->t20;
double *t19 = msg->t19;
double *t21 = msg->t21;
int __s431 = msg->__s431;
int __m432 = msg->__m432;

for (j=0; j<__m432; j+=__s431) {
// 4_2
int __m431 = j + __s431 > __m432 ? __m432 - j : __s431;
double *t28 = t21 + j;
double *t26 = t19 + j;
double *t27 = t20 + j;
for (k=0; k<A_nrows; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t26 + k*xh_ncols;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<__m431; l+=1) {
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

int __s431 = 512;

int __s429 = 512;

int nparts__s432 = 8;
int __s432;
if (nparts__s432 > 1 && xh_ncols > nparts__s432) {
__s432 = xh_ncols/nparts__s432;
// this will fail if xh_ncols%nparts__s432+__s432 > nparts__s432
// which primarily effects small sizes
if (xh_ncols%nparts__s432)
++__s432;
}
else {
__s432 = xh_ncols;
nparts__s432 = 1;
}

int nparts__s430 = 8;
int __s430;
if (nparts__s430 > 1 && A_nrows > nparts__s430) {
__s430 = A_nrows/nparts__s430;
// this will fail if A_nrows%nparts__s430+__s430 > nparts__s430
// which primarily effects small sizes
if (A_nrows%nparts__s430)
++__s430;
}
else {
__s430 = A_nrows;
nparts__s430 = 1;
}

double *t18 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t13 = t18;
double *t10 = t18;
double *t7 = t18;
double *t9 = t18;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s430);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s430);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s430,ii+=1) {
// 2_1
int __m430 = i + __s430 > A_nrows ? A_nrows - i : __s430;
double *t17 = t18 + i*xh_ncols;
double *t16 = A + i*A_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t16 = t16;
predict1_0[disp].__m430 = __m430;
predict1_0[disp].xh = xh;
predict1_0[disp].t17 = t17;
predict1_0[disp].__s429 = __s429;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s430; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
predict1_1_msg_t *predict1_1 = malloc(sizeof(predict1_1_msg_t)*nparts__s432);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s432);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s432,ii+=1) {
// 4_1
int __m432 = i + __s432 > xh_ncols ? xh_ncols - i : __s432;
double *t21 = xhn + i;
double *t19 = t13 + i;
double *t20 = Y + i;
predict1_1[disp].xh_ncols = xh_ncols;
predict1_1[disp].A_nrows = A_nrows;
predict1_1[disp].t20 = t20;
predict1_1[disp].t19 = t19;
predict1_1[disp].t21 = t21;
predict1_1[disp].__s431 = __s431;
predict1_1[disp].__m432 = __m432;

pthread_create(&threads_1[disp], NULL, predict1_body_1, (void *)(predict1_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s432; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict1_1);
free(t18);
}
