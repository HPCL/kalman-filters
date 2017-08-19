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
int __s615;
int __m616;
} predict1_1_msg_t;

typedef struct { 
int xh_ncols;
int A_ncols;
double *t16;
int __m614;
double *xh;
double *t17;
int __s613;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *t16 = msg->t16;
int __m614 = msg->__m614;
double *xh = msg->xh;
double *t17 = msg->t17;
int __s613 = msg->__s613;

for (j=0; j<xh_ncols; j+=__s613) {
// 2_2
int __m613 = j + __s613 > xh_ncols ? xh_ncols - j : __s613;
double *t24 = t17 + j;
double *t23 = xh + j;
for (k=0; k<__m614; k+=1) {
// 2_3
double *t31 = t24 + k*xh_ncols;
double *t30 = t16 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m613; ++__zr__) t31[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t38 = t23 + l*xh_ncols;
for (p=0; p<__m613; p+=1) {
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
int __s615 = msg->__s615;
int __m616 = msg->__m616;

for (j=0; j<__m616; j+=__s615) {
// 4_2
int __m615 = j + __s615 > __m616 ? __m616 - j : __s615;
double *t28 = t21 + j;
double *t26 = t19 + j;
double *t27 = t20 + j;
for (k=0; k<A_nrows; k+=1) {
// 4_3
double *t35 = t28 + k*xh_ncols;
double *t33 = t26 + k*xh_ncols;
double *t34 = t27 + k*xh_ncols;
for (l=0; l<__m615; l+=1) {
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

int __s615 = 504;

int __s613 = 504;

int nparts__s616 = 4;
int __s616;
if (nparts__s616 > 1 && xh_ncols > nparts__s616) {
__s616 = xh_ncols/nparts__s616;
// this will fail if xh_ncols%nparts__s616+__s616 > nparts__s616
// which primarily effects small sizes
if (xh_ncols%nparts__s616)
++__s616;
}
else {
__s616 = xh_ncols;
nparts__s616 = 1;
}

int nparts__s614 = 4;
int __s614;
if (nparts__s614 > 1 && A_nrows > nparts__s614) {
__s614 = A_nrows/nparts__s614;
// this will fail if A_nrows%nparts__s614+__s614 > nparts__s614
// which primarily effects small sizes
if (A_nrows%nparts__s614)
++__s614;
}
else {
__s614 = A_nrows;
nparts__s614 = 1;
}

double *t18 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t13 = t18;
double *t10 = t18;
double *t7 = t18;
double *t9 = t18;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s614);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s614);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s614,ii+=1) {
// 2_1
int __m614 = i + __s614 > A_nrows ? A_nrows - i : __s614;
double *t17 = t18 + i*xh_ncols;
double *t16 = A + i*A_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t16 = t16;
predict1_0[disp].__m614 = __m614;
predict1_0[disp].xh = xh;
predict1_0[disp].t17 = t17;
predict1_0[disp].__s613 = __s613;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s614; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
predict1_1_msg_t *predict1_1 = malloc(sizeof(predict1_1_msg_t)*nparts__s616);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s616);
disp = 0;
for (i=0,ii=0; i<xh_ncols; i+=__s616,ii+=1) {
// 4_1
int __m616 = i + __s616 > xh_ncols ? xh_ncols - i : __s616;
double *t21 = xhn + i;
double *t19 = t13 + i;
double *t20 = Y + i;
predict1_1[disp].xh_ncols = xh_ncols;
predict1_1[disp].A_nrows = A_nrows;
predict1_1[disp].t20 = t20;
predict1_1[disp].t19 = t19;
predict1_1[disp].t21 = t21;
predict1_1[disp].__s615 = __s615;
predict1_1[disp].__m616 = __m616;

pthread_create(&threads_1[disp], NULL, predict1_body_1, (void *)(predict1_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s616; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict1_1);
free(t18);
}
