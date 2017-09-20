#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int P_ncols;
int __m2012;
double *t31;
double *t30;
double *t32;
int __s2011;
} predict_2_msg_t;

typedef struct { 
int P_ncols;
double *t9;
double *t34;
double *t28;
int __s2009;
int __m2010;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *A;
double *t24;
double *t25;
int __s2007;
int __m2008;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *A = msg->A;
double *t24 = msg->t24;
double *t25 = msg->t25;
int __s2007 = msg->__s2007;
int __m2008 = msg->__m2008;

for (j=0; j<__m2008; j+=__s2007) {
// 2_2
int __m2007 = j + __s2007 > __m2008 ? __m2008 - j : __s2007;
double *t36 = t25 + j;
double *t35 = t24 + j;
for (k=0; k<P_ncols; k+=1) {
// 2_3
double *t47 = t36 + k*P_ncols;
double *t46 = A + k*P_ncols;
for (__zr__ = 0; __zr__ < __m2007; ++__zr__) t47[__zr__] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 2_4
double *t57 = t35 + l*P_ncols;
for (p=0; p<__m2007; p+=1) {
// 2_5
t47[p] += (t46[l]*t57[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t9 = msg->t9;
double *t34 = msg->t34;
double *t28 = msg->t28;
int __s2009 = msg->__s2009;
int __m2010 = msg->__m2010;

for (j=0; j<__m2010; j+=__s2009) {
// 4_2
int __m2009 = j + __s2009 > __m2010 ? __m2010 - j : __s2009;
double *t39 = t28 + j;
double *t45 = t34 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t50 = t39 + k*P_ncols;
double *t49 = t9 + k*P_ncols;
for (l=0; l<__m2009; l+=1) {
// 4_4
double *t67 = t45 + l*P_ncols;
t50[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t50[l] += (t49[p]*t67[p]);
}
}
}
}
return NULL;
}


void *predict_body_2(void *mesg) {
int disp, __zr__,j,k,l;
predict_2_msg_t *msg = (predict_2_msg_t*)mesg;
int P_ncols = msg->P_ncols;
int __m2012 = msg->__m2012;
double *t31 = msg->t31;
double *t30 = msg->t30;
double *t32 = msg->t32;
int __s2011 = msg->__s2011;

for (j=0; j<P_ncols; j+=__s2011) {
// 6_2
int __m2011 = j + __s2011 > P_ncols ? P_ncols - j : __s2011;
double *t43 = t32 + j;
double *t41 = t30 + j;
double *t42 = t31 + j;
for (k=0; k<__m2012; k+=1) {
// 6_3
double *t54 = t43 + k*P_ncols;
double *t52 = t41 + k*P_ncols;
double *t53 = t42 + k*P_ncols;
for (l=0; l<__m2011; l+=1) {
// 6_4
t54[l] = (t52[l]+t53[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii;

int __s2011 = 512;

int __s2009 = 512;

int __s2007 = 512;

int nparts__s2010 = 12;
int __s2010;
if (nparts__s2010 > 1 && P_ncols > nparts__s2010) {
__s2010 = P_ncols/nparts__s2010;
// this will fail if P_ncols%nparts__s2010+__s2010 > nparts__s2010
// which primarily effects small sizes
if (P_ncols%nparts__s2010)
++__s2010;
}
else {
__s2010 = P_ncols;
nparts__s2010 = 1;
}

int nparts__s2008 = 12;
int __s2008;
if (nparts__s2008 > 1 && P_ncols > nparts__s2008) {
__s2008 = P_ncols/nparts__s2008;
// this will fail if P_ncols%nparts__s2008+__s2008 > nparts__s2008
// which primarily effects small sizes
if (P_ncols%nparts__s2008)
++__s2008;
}
else {
__s2008 = P_ncols;
nparts__s2008 = 1;
}

int nparts__s2012 = 12;
int __s2012;
if (nparts__s2012 > 1 && P_ncols > nparts__s2012) {
__s2012 = P_ncols/nparts__s2012;
// this will fail if P_ncols%nparts__s2012+__s2012 > nparts__s2012
// which primarily effects small sizes
if (P_ncols%nparts__s2012)
++__s2012;
}
else {
__s2012 = P_ncols;
nparts__s2012 = 1;
}

double *t29 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = t29;
double *t18 = t29;
double *t13 = t29;
double *t16 = t29;
double *t17 = A;
double *t14 = A;
double *t9 = t26;
double *t11 = t26;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2008);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2008);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2008,ii+=1) {
// 2_1
int __m2008 = i + __s2008 > P_ncols ? P_ncols - i : __s2008;
double *t25 = t26 + i;
double *t24 = P + i;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].A = A;
predict_0[disp].t24 = t24;
predict_0[disp].t25 = t25;
predict_0[disp].__s2007 = __s2007;
predict_0[disp].__m2008 = __m2008;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2008; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2010);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2010);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2010,ii+=1) {
// 4_1
int __m2010 = i + __s2010 > P_ncols ? P_ncols - i : __s2010;
double *t28 = t29 + i;
double *t34 = t17 + i*P_ncols;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t9 = t9;
predict_1[disp].t34 = t34;
predict_1[disp].t28 = t28;
predict_1[disp].__s2009 = __s2009;
predict_1[disp].__m2010 = __m2010;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2010; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s2012);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s2012);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2012,ii+=1) {
// 6_1
int __m2012 = i + __s2012 > P_ncols ? P_ncols - i : __s2012;
double *t32 = P + i*P_ncols;
double *t30 = t21 + i*P_ncols;
double *t31 = Q + i*P_ncols;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].__m2012 = __m2012;
predict_2[disp].t31 = t31;
predict_2[disp].t30 = t30;
predict_2[disp].t32 = t32;
predict_2[disp].__s2011 = __s2011;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s2012; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t29);
free(t26);
}
