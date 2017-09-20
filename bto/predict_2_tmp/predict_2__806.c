#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m1918;
int P_ncols;
double *t26;
double *t25;
double *t27;
int __s1917;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t29;
int __m1916;
double *t8;
double *t23;
int __s1915;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t29 = msg->t29;
int __m1916 = msg->__m1916;
double *t8 = msg->t8;
double *t23 = msg->t23;
int __s1915 = msg->__s1915;

for (j=0; j<P_ncols; j+=__s1915) {
// 4_2
int __m1915 = j + __s1915 > P_ncols ? P_ncols - j : __s1915;
double *t35 = t23 + j*P_ncols;
double *t34 = t8 + j*P_ncols;
for (k=0; k<__m1915; k+=1) {
// 4_3
double *t45 = t35 + k*P_ncols;
double *t44 = t34 + k*P_ncols;
for (l=0; l<__m1916; l+=1) {
// 4_4
double *t58 = t29 + l*P_ncols;
t45[l] = 0.0;
for (p=0; p<P_ncols; p+=1) {
// 4_5
t45[l] += (t44[p]*t58[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m1918 = msg->__m1918;
int P_ncols = msg->P_ncols;
double *t26 = msg->t26;
double *t25 = msg->t25;
double *t27 = msg->t27;
int __s1917 = msg->__s1917;

for (j=0; j<P_ncols; j+=__s1917) {
// 6_2
int __m1917 = j + __s1917 > P_ncols ? P_ncols - j : __s1917;
double *t39 = t27 + j*P_ncols;
double *t37 = t25 + j*P_ncols;
double *t38 = t26 + j*P_ncols;
for (k=0; k<__m1917; k+=1) {
// 6_3
double *t49 = t39 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
for (l=0; l<__m1918; l+=1) {
// 6_4
t49[l] = (t47[l]+t48[l]);
}
}
}
return NULL;
}


void predict
(int A_nrows, int A_ncols, double* A, int Q_nrows, int Q_ncols, double* Q, int P_nrows, int P_ncols, double* P)
{
int disp, __zr__,i,ii,j,k;

int __s1917 = 512;

int __s1915 = 512;

int nparts__s1916 = 12;
int __s1916;
if (nparts__s1916 > 1 && P_ncols > nparts__s1916) {
__s1916 = P_ncols/nparts__s1916;
// this will fail if P_ncols%nparts__s1916+__s1916 > nparts__s1916
// which primarily effects small sizes
if (P_ncols%nparts__s1916)
++__s1916;
}
else {
__s1916 = P_ncols;
nparts__s1916 = 1;
}

int nparts__s1918 = 12;
int __s1918;
if (nparts__s1918 > 1 && P_ncols > nparts__s1918) {
__s1918 = P_ncols/nparts__s1918;
// this will fail if P_ncols%nparts__s1918+__s1918 > nparts__s1918
// which primarily effects small sizes
if (P_ncols%nparts__s1918)
++__s1918;
}
else {
__s1918 = P_ncols;
nparts__s1918 = 1;
}

double *t24 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t21 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t16 = t24;
double *t13 = t24;
double *t9 = t24;
double *t11 = t24;
double *t12 = A;
double *t8 = t21;
for (i=0; i<P_ncols; i+=1) {
// 2_1
double *t20 = t21 + i*P_ncols;
double *t19 = A + i*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t20[__zr__] = 0.0;
for (j=0; j<P_ncols; j+=1) {
// 2_2
double *t31 = P + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 2_3
t20[k] += (t19[j]*t31[k]);
}
}
}
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s1916);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s1916);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1916,ii+=1) {
// 4_1
int __m1916 = i + __s1916 > P_ncols ? P_ncols - i : __s1916;
double *t23 = t24 + i;
double *t29 = t12 + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t29 = t29;
predict_0[disp].__m1916 = __m1916;
predict_0[disp].t8 = t8;
predict_0[disp].t23 = t23;
predict_0[disp].__s1915 = __s1915;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s1916; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s1918);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s1918);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s1918,ii+=1) {
// 6_1
int __m1918 = i + __s1918 > P_ncols ? P_ncols - i : __s1918;
double *t27 = P + i;
double *t25 = t16 + i;
double *t26 = Q + i;
predict_1[disp].__m1918 = __m1918;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t26 = t26;
predict_1[disp].t25 = t25;
predict_1[disp].t27 = t27;
predict_1[disp].__s1917 = __s1917;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s1918; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t24);
free(t21);
}
