#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m480;
int P_ncols;
double *t27;
double *t19;
double *t21;
int __s479;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int __m480 = msg->__m480;
int P_ncols = msg->P_ncols;
double *t27 = msg->t27;
double *t19 = msg->t19;
double *t21 = msg->t21;
int __s479 = msg->__s479;

for (j=0; j<P_ncols; j+=__s479) {
// 4_2
int __m479 = j + __s479 > P_ncols ? P_ncols - j : __s479;
double *t33 = t21 + j*P_ncols;
double *t32 = t19 + j*P_ncols;
for (k=0; k<__m479; k+=1) {
// 4_3
double *t43 = t33 + k*P_ncols;
double *t42 = t32 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t52 = t27 + l*P_ncols;
t43[l] = 0.0;
for (p=0; p<__m480; p+=1) {
// 4_5
t43[l] += (t42[p]*t52[p]);
}
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k;

int __s481 = 2;

int __s479 = 512;

int nparts__s480 = 12;
int __s480;
if (nparts__s480 > 1 && P_ncols > nparts__s480) {
__s480 = P_ncols/nparts__s480;
// this will fail if P_ncols%nparts__s480+__s480 > nparts__s480
// which primarily effects small sizes
if (P_ncols%nparts__s480)
++__s480;
}
else {
__s480 = P_ncols;
nparts__s480 = 1;
}

double *t22 = malloc(sizeof(double)*nparts__s480*P_ncols*P_ncols);
double *t18 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t13 = t22;
double *t9 = t22;
double *t57 = t22;
double *t12 = A;
double *t10 = t18;
double *t8 = t18;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t17 = t18 + i*P_ncols;
double *t16 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t17[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t29 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t17[k] += (t16[j]*t29[k]);
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s480);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s480);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s480,ii+=1) {
// 4_1
int __m480 = i + __s480 > P_ncols ? P_ncols - i : __s480;
double *t21 = t22 + ii*P_ncols*P_ncols;
double *t19 = t10 + i;
double *t27 = t12 + i;
predict_0[disp].__m480 = __m480;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t27 = t27;
predict_0[disp].t19 = t19;
predict_0[disp].t21 = t21;
predict_0[disp].__s479 = __s479;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s480; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s480,ii+=1) {
// 4_1
int __m480 = i + __s480 > P_ncols ? P_ncols - i : __s480;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s479) {
int __m479 = __j + __s479 > P_ncols ? P_ncols - __j : __s479;
for (__k = 0; __k < __m479; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t57[__j*P_ncols+__k*P_ncols+__l] = t22[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s479) {
int __m479 = __j + __s479 > P_ncols ? P_ncols - __j : __s479;
for (__k = 0; __k < __m479; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t57[__j*P_ncols+__k*P_ncols+__l] += t22[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s481) {
// 6_1
int __m481 = i + __s481 > P_ncols ? P_ncols - i : __s481;
double *t25 = P + i*P_ncols;
double *t23 = t13 + i*P_ncols;
double *t24 = Q + i*P_ncols;
for (j=0; j<__m481; j+=1) {
// 6_2
double *t37 = t25 + j*P_ncols;
double *t35 = t23 + j*P_ncols;
double *t36 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 6_3
t37[k] = (t35[k]+t36[k]);
}
}
}
free(t22);
free(t18);
}
