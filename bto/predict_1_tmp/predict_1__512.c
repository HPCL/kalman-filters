#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
double *t20;
double *t19;
double *t21;
int __s595;
int __m596;
} predict1_1_msg_t;

typedef struct { 
int xh_ncols;
double *xh;
int A_ncols;
double *t16;
double *t17;
int __s593;
int __m594;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
double *xh = msg->xh;
int A_ncols = msg->A_ncols;
double *t16 = msg->t16;
double *t17 = msg->t17;
int __s593 = msg->__s593;
int __m594 = msg->__m594;

for (j=0; j<__m594; j+=__s593) {
// 2_2
int __m593 = j + __s593 > __m594 ? __m594 - j : __s593;
double *t24 = t17 + j*xh_ncols;
double *t23 = t16 + j*A_ncols;
for (k=0; k<__m593; k+=1) {
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
int __s595 = msg->__s595;
int __m596 = msg->__m596;

for (j=0; j<__m596; j+=__s595) {
// 4_2
int __m595 = j + __s595 > __m596 ? __m596 - j : __s595;
double *t28 = t21 + j*xh_ncols;
double *t26 = t19 + j*xh_ncols;
double *t27 = t20 + j*xh_ncols;
for (k=0; k<__m595; k+=1) {
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

int __s595 = 504;

int __s593 = 504;

int nparts__s596 = 6;
int __s596;
if (nparts__s596 > 1 && A_nrows > nparts__s596) {
__s596 = A_nrows/nparts__s596;
// this will fail if A_nrows%nparts__s596+__s596 > nparts__s596
// which primarily effects small sizes
if (A_nrows%nparts__s596)
++__s596;
}
else {
__s596 = A_nrows;
nparts__s596 = 1;
}

int nparts__s594 = 6;
int __s594;
if (nparts__s594 > 1 && A_nrows > nparts__s594) {
__s594 = A_nrows/nparts__s594;
// this will fail if A_nrows%nparts__s594+__s594 > nparts__s594
// which primarily effects small sizes
if (A_nrows%nparts__s594)
++__s594;
}
else {
__s594 = A_nrows;
nparts__s594 = 1;
}

double *t18 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t13 = t18;
double *t10 = t18;
double *t7 = t18;
double *t9 = t18;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s594);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s594);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s594,ii+=1) {
// 2_1
int __m594 = i + __s594 > A_nrows ? A_nrows - i : __s594;
double *t17 = t18 + i*xh_ncols;
double *t16 = A + i*A_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].xh = xh;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t16 = t16;
predict1_0[disp].t17 = t17;
predict1_0[disp].__s593 = __s593;
predict1_0[disp].__m594 = __m594;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s594; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
predict1_1_msg_t *predict1_1 = malloc(sizeof(predict1_1_msg_t)*nparts__s596);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s596);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s596,ii+=1) {
// 4_1
int __m596 = i + __s596 > A_nrows ? A_nrows - i : __s596;
double *t21 = xhn + i*xh_ncols;
double *t19 = t13 + i*xh_ncols;
double *t20 = Y + i*xh_ncols;
predict1_1[disp].xh_ncols = xh_ncols;
predict1_1[disp].t20 = t20;
predict1_1[disp].t19 = t19;
predict1_1[disp].t21 = t21;
predict1_1[disp].__s595 = __s595;
predict1_1[disp].__m596 = __m596;

pthread_create(&threads_1[disp], NULL, predict1_body_1, (void *)(predict1_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s596; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict1_1);
free(t18);
}
