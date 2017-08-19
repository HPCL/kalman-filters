#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int __m620;
double *t20;
double *t19;
double *t21;
int __s619;
} predict1_1_msg_t;

typedef struct { 
int xh_ncols;
double *xh;
int A_ncols;
double *t16;
double *t17;
int __s617;
int __m618;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
double *xh = msg->xh;
int A_ncols = msg->A_ncols;
double *t16 = msg->t16;
double *t17 = msg->t17;
int __s617 = msg->__s617;
int __m618 = msg->__m618;

for (j=0; j<__m618; j+=__s617) {
// 2_2
int __m617 = j + __s617 > __m618 ? __m618 - j : __s617;
double *t24 = t17 + j*xh_ncols;
double *t23 = t16 + j*A_ncols;
for (k=0; k<__m617; k+=1) {
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
int __m620 = msg->__m620;
double *t20 = msg->t20;
double *t19 = msg->t19;
double *t21 = msg->t21;
int __s619 = msg->__s619;

for (j=0; j<xh_ncols; j+=__s619) {
// 4_2
int __m619 = j + __s619 > xh_ncols ? xh_ncols - j : __s619;
double *t28 = t21 + j;
double *t26 = t19 + j;
double *t27 = t20 + j;
for (k=0; k<__m620; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t26 + k*xh_ncols;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<__m619; l+=1) {
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

int __s619 = 512;

int __s617 = 512;

int nparts__s618 = 6;
int __s618;
if (nparts__s618 > 1 && A_nrows > nparts__s618) {
__s618 = A_nrows/nparts__s618;
// this will fail if A_nrows%nparts__s618+__s618 > nparts__s618
// which primarily effects small sizes
if (A_nrows%nparts__s618)
++__s618;
}
else {
__s618 = A_nrows;
nparts__s618 = 1;
}

int nparts__s620 = 6;
int __s620;
if (nparts__s620 > 1 && A_nrows > nparts__s620) {
__s620 = A_nrows/nparts__s620;
// this will fail if A_nrows%nparts__s620+__s620 > nparts__s620
// which primarily effects small sizes
if (A_nrows%nparts__s620)
++__s620;
}
else {
__s620 = A_nrows;
nparts__s620 = 1;
}

double *t18 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t13 = t18;
double *t10 = t18;
double *t7 = t18;
double *t9 = t18;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s618);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s618);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s618,ii+=1) {
// 2_1
int __m618 = i + __s618 > A_nrows ? A_nrows - i : __s618;
double *t17 = t18 + i*xh_ncols;
double *t16 = A + i*A_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].xh = xh;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t16 = t16;
predict1_0[disp].t17 = t17;
predict1_0[disp].__s617 = __s617;
predict1_0[disp].__m618 = __m618;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s618; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
predict1_1_msg_t *predict1_1 = malloc(sizeof(predict1_1_msg_t)*nparts__s620);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s620);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s620,ii+=1) {
// 4_1
int __m620 = i + __s620 > A_nrows ? A_nrows - i : __s620;
double *t21 = xhn + i*xh_ncols;
double *t19 = t13 + i*xh_ncols;
double *t20 = Y + i*xh_ncols;
predict1_1[disp].xh_ncols = xh_ncols;
predict1_1[disp].__m620 = __m620;
predict1_1[disp].t20 = t20;
predict1_1[disp].t19 = t19;
predict1_1[disp].t21 = t21;
predict1_1[disp].__s619 = __s619;

pthread_create(&threads_1[disp], NULL, predict1_body_1, (void *)(predict1_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s620; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict1_1);
free(t18);
}
