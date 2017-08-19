#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xh_ncols;
int A_ncols;
double *t13;
int __m325;
double *xh;
double *t14;
int __s324;
} predict1_0_msg_t;

void *predict1_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict1_0_msg_t *msg = (predict1_0_msg_t*)mesg;
int xh_ncols = msg->xh_ncols;
int A_ncols = msg->A_ncols;
double *t13 = msg->t13;
int __m325 = msg->__m325;
double *xh = msg->xh;
double *t14 = msg->t14;
int __s324 = msg->__s324;

for (j=0; j<xh_ncols; j+=__s324) {
// 2_2
int __m324 = j + __s324 > xh_ncols ? xh_ncols - j : __s324;
double *t21 = t14 + j;
double *t20 = xh + j;
for (k=0; k<__m325; k+=1) {
// 2_3
double *t28 = t21 + k*xh_ncols;
double *t27 = t13 + k*A_ncols;
for (__zr__ = 0; __zr__ < __m324; ++__zr__) t28[__zr__] = 0.0;
for (l=0; l<A_ncols; l+=1) {
// 2_4
double *t35 = t20 + l*xh_ncols;
for (p=0; p<__m324; p+=1) {
// 2_5
t28[p] += (t27[l]*t35[p]);
}
}
}
}
return NULL;
}


void predict1
(int A_nrows, int A_ncols, double* A, int Y_nrows, int Y_ncols, double* Y, int xh_nrows, int xh_ncols, double* xh, int xhn_nrows, int xhn_ncols, double* xhn)
{
int disp, __zr__,i,ii,j,k;

int __s326 = 8;

int __s324 = 504;

int nparts__s325 = 10;
int __s325;
if (nparts__s325 > 1 && A_nrows > nparts__s325) {
__s325 = A_nrows/nparts__s325;
// this will fail if A_nrows%nparts__s325+__s325 > nparts__s325
// which primarily effects small sizes
if (A_nrows%nparts__s325)
++__s325;
}
else {
__s325 = A_nrows;
nparts__s325 = 1;
}

double *t15 = malloc(sizeof(double)*A_nrows*xh_ncols);
double *t10 = t15;
double *t7 = t15;
double *t9 = t15;
predict1_0_msg_t *predict1_0 = malloc(sizeof(predict1_0_msg_t)*nparts__s325);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s325);
disp = 0;
for (i=0,ii=0; i<A_nrows; i+=__s325,ii+=1) {
// 2_1
int __m325 = i + __s325 > A_nrows ? A_nrows - i : __s325;
double *t14 = t15 + i*xh_ncols;
double *t13 = A + i*A_ncols;
predict1_0[disp].xh_ncols = xh_ncols;
predict1_0[disp].A_ncols = A_ncols;
predict1_0[disp].t13 = t13;
predict1_0[disp].__m325 = __m325;
predict1_0[disp].xh = xh;
predict1_0[disp].t14 = t14;
predict1_0[disp].__s324 = __s324;

pthread_create(&threads_0[disp], NULL, predict1_body_0, (void *)(predict1_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s325; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict1_0);
for (i=0; i<A_nrows; i+=__s326) {
// 4_1
int __m326 = i + __s326 > A_nrows ? A_nrows - i : __s326;
double *t18 = xhn + i*xh_ncols;
double *t16 = t10 + i*xh_ncols;
double *t17 = Y + i*xh_ncols;
for (j=0; j<__m326; j+=1) {
// 4_2
double *t25 = t18 + j*xh_ncols;
double *t23 = t16 + j*xh_ncols;
double *t24 = t17 + j*xh_ncols;
for (k=0; k<xh_ncols; k+=1) {
// 4_3
t25[k] = (t23[k]+t24[k]);
}
}
}
free(t15);
}
