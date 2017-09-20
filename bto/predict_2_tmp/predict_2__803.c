#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m1904;
int P_ncols;
double *t32;
double *t31;
double *t33;
int __s1903;
} predict_2_msg_t;

typedef struct { 
int __m1902;
int P_ncols;
double *t35;
double *t27;
double *t29;
int __s1901;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t24;
int __m1900;
double *t23;
double *t25;
int __s1899;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t24 = msg->t24;
int __m1900 = msg->__m1900;
double *t23 = msg->t23;
double *t25 = msg->t25;
int __s1899 = msg->__s1899;

for (j=0; j<P_ncols; j+=__s1899) {
// 2_2
int __m1899 = j + __s1899 > P_ncols ? P_ncols - j : __s1899;
double *t37 = t25 + j*P_ncols;
double *t36 = t23 + j*P_ncols;
for (k=0; k<__m1899; k+=1) {
// 2_3
double *t47 = t37 + k*P_ncols;
double *t46 = t36 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t47[__zr__] = 0.0;
for (l=0; l<__m1900; l+=1) {
// 2_4
double *t57 = t24 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
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
int __m1902 = msg->__m1902;
int P_ncols = msg->P_ncols;
double *t35 = msg->t35;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s1901 = msg->__s1901;

for (j=0; j<P_ncols; j+=__s1901) {
// 4_2
int __m1901 = j + __s1901 > P_ncols ? P_ncols - j : __s1901;
double *t40 = t29 + j*P_ncols;
double *t39 = t27 + j*P_ncols;
for (k=0; k<__m1901; k+=1) {
// 4_3
double *t50 = t40 + k*P_ncols;
double *t49 = t39 + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 4_4
double *t67 = t35 + l*P_ncols;
t50[l] = 0.0;
for (p=0; p<__m1902; p+=1) {
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
int __m1904 = msg->__m1904;
int P_ncols = msg->P_ncols;
double *t32 = msg->t32;
double *t31 = msg->t31;
double *t33 = msg->t33;
int __s1903 = msg->__s1903;

for (j=0; j<P_ncols; j+=__s1903) {
// 6_2
int __m1903 = j + __s1903 > P_ncols ? P_ncols - j : __s1903;
double *t44 = t33 + j*P_ncols;
double *t42 = t31 + j*P_ncols;
double *t43 = t32 + j*P_ncols;
for (k=0; k<__m1903; k+=1) {
// 6_3
double *t54 = t44 + k*P_ncols;
double *t52 = t42 + k*P_ncols;
double *t53 = t43 + k*P_ncols;
for (l=0; l<__m1904; l+=1) {
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

int __s1903 = 512;

int __s1901 = 512;

int __s1899 = 512;

int nparts__s1900 = 12;
int __s1900;
if (nparts__s1900 > 1 && P_ncols > nparts__s1900) {
__s1900 = P_ncols/nparts__s1900;
// this will fail if P_ncols%nparts__s1900+__s1900 > nparts__s1900
// which primarily effects small sizes
if (P_ncols%nparts__s1900)
++__s1900;
}
else {
__s1900 = P_ncols;
nparts__s1900 = 1;
}

int nparts__s1902 = 12;
int __s1902;
if (nparts__s1902 > 1 && P_ncols > nparts__s1902) {
__s1902 = P_ncols/nparts__s1902;
// this will fail if P_ncols%nparts__s1902+__s1902 > nparts__s1902
// which primarily effects small sizes
if (P_ncols%nparts__s1902)
++__s1902;
}
else {
__s1902 = P_ncols;
nparts__s1902 = 1;
}

int nparts__s1904 = 12;
int __s1904;
if (nparts__s1904 > 1 && P_ncols > nparts__s1904) {
__s1904 = P_ncols/nparts__s1904;
// this will fail if P_ncols%nparts__s1904+__s1904 > nparts__s1904
// which primarily effects small sizes
if (P_ncols%nparts__s1904)
++__s1904;
}
else {
__s1904 = P_ncols;
nparts__s1904 = 1;
}

double *t30 = malloc(sizeof(double)*nparts__s1902*P_ncols*P_ncols);
double *t26 = malloc(sizeof(double)*nparts__s1900*P_ncols*P_ncols);
double *t20 = t30;
double *t17 = t30;
double *t13 = t30;
double *t76 = t30;
double *t14 = t26;
double *t12 = t26;
double *t9 = t26;
double *t75 = t26;
double *t10 = A;
double *t8 = A;
double *t16 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1900);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1900);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1900,ii+=1) {
// 2_1
int __m1900 = i + __s1900 > P_ncols ? P_ncols - i : __s1900;
double *t25 = t26 + ii*P_ncols*P_ncols;
double *t23 = t10 + i;
double *t24 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t24 = t24;
predict_0[disp].__m1900 = __m1900;
predict_0[disp].t23 = t23;
predict_0[disp].t25 = t25;
predict_0[disp].__s1899 = __s1899;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1900; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1900,ii+=1) {
// 2_1
int __m1900 = i + __s1900 > P_ncols ? P_ncols - i : __s1900;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1899) {
int __m1899 = __j + __s1899 > P_ncols ? P_ncols - __j : __s1899;
for (__k = 0; __k < __m1899; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t75[__j*P_ncols+__k*P_ncols+__l] = t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1899) {
int __m1899 = __j + __s1899 > P_ncols ? P_ncols - __j : __s1899;
for (__k = 0; __k < __m1899; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t75[__j*P_ncols+__k*P_ncols+__l] += t26[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1902);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1902);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1902,ii+=1) {
// 4_1
int __m1902 = i + __s1902 > P_ncols ? P_ncols - i : __s1902;
double *t29 = t30 + ii*P_ncols*P_ncols;
double *t27 = t14 + i;
double *t35 = t16 + i;
predict_1[disp].__m1902 = __m1902;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t35 = t35;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s1901 = __s1901;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1902; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s1902,ii+=1) {
// 4_1
int __m1902 = i + __s1902 > P_ncols ? P_ncols - i : __s1902;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s1901) {
int __m1901 = __j + __s1901 > P_ncols ? P_ncols - __j : __s1901;
for (__k = 0; __k < __m1901; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t76[__j*P_ncols+__k*P_ncols+__l] = t30[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s1901) {
int __m1901 = __j + __s1901 > P_ncols ? P_ncols - __j : __s1901;
for (__k = 0; __k < __m1901; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t76[__j*P_ncols+__k*P_ncols+__l] += t30[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

predict_2_msg_t *predict_2 = malloc(sizeof(predict_2_msg_t)*nparts__s1904);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s1904);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1904,ii+=1) {
// 6_1
int __m1904 = i + __s1904 > P_ncols ? P_ncols - i : __s1904;
double *t33 = P + i;
double *t31 = t20 + i;
double *t32 = Q + i;
predict_2[disp].__m1904 = __m1904;
predict_2[disp].P_ncols = P_ncols;
predict_2[disp].t32 = t32;
predict_2[disp].t31 = t31;
predict_2[disp].t33 = t33;
predict_2[disp].__s1903 = __s1903;

pthread_create(&threads_2[disp], NULL, predict_body_2, (void *)(predict_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s1904; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(predict_2);
free(t30);
free(t26);
}
