#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m2920;
int P_ncols;
double *t28;
double *t27;
double *t29;
int __s2919;
} predict_1_msg_t;

typedef struct { 
int P_ncols;
double *t21;
int __m2917;
double *t20;
double *t22;
int __s2916;
} predict_0_msg_t;

void *predict_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
predict_0_msg_t *msg = (predict_0_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *t21 = msg->t21;
int __m2917 = msg->__m2917;
double *t20 = msg->t20;
double *t22 = msg->t22;
int __s2916 = msg->__s2916;

for (j=0; j<P_ncols; j+=__s2916) {
// 2_2
int __m2916 = j + __s2916 > P_ncols ? P_ncols - j : __s2916;
double *t32 = t22 + j*P_ncols;
double *t31 = t20 + j*P_ncols;
for (k=0; k<__m2916; k+=1) {
// 2_3
double *t42 = t32 + k*P_ncols;
double *t41 = t31 + k*P_ncols;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t42[__zr__] = 0.0;
for (l=0; l<__m2917; l+=1) {
// 2_4
double *t53 = t21 + l*P_ncols;
for (p=0; p<P_ncols; p+=1) {
// 2_5
t42[p] += (t41[l]*t53[p]);
}
}
}
}
return NULL;
}


void *predict_body_1(void *mesg) {
int disp, __zr__,j,k,l;
predict_1_msg_t *msg = (predict_1_msg_t*)mesg;
int __m2920 = msg->__m2920;
int P_ncols = msg->P_ncols;
double *t28 = msg->t28;
double *t27 = msg->t27;
double *t29 = msg->t29;
int __s2919 = msg->__s2919;

for (j=0; j<P_ncols; j+=__s2919) {
// 6_2
int __m2919 = j + __s2919 > P_ncols ? P_ncols - j : __s2919;
double *t39 = t29 + j*P_ncols;
double *t37 = t27 + j*P_ncols;
double *t38 = t28 + j*P_ncols;
for (k=0; k<__m2919; k+=1) {
// 6_3
double *t49 = t39 + k*P_ncols;
double *t47 = t37 + k*P_ncols;
double *t48 = t38 + k*P_ncols;
for (l=0; l<__m2920; l+=1) {
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
int disp, __zr__,i,ii,j,k,l;

int __s2919 = 504;

int __s2918 = 12;

int __s2916 = 512;

int nparts__s2917 = 12;
int __s2917;
if (nparts__s2917 > 1 && P_ncols > nparts__s2917) {
__s2917 = P_ncols/nparts__s2917;
// this will fail if P_ncols%nparts__s2917+__s2917 > nparts__s2917
// which primarily effects small sizes
if (P_ncols%nparts__s2917)
++__s2917;
}
else {
__s2917 = P_ncols;
nparts__s2917 = 1;
}

int nparts__s2920 = 12;
int __s2920;
if (nparts__s2920 > 1 && P_ncols > nparts__s2920) {
__s2920 = P_ncols/nparts__s2920;
// this will fail if P_ncols%nparts__s2920+__s2920 > nparts__s2920
// which primarily effects small sizes
if (P_ncols%nparts__s2920)
++__s2920;
}
else {
__s2920 = P_ncols;
nparts__s2920 = 1;
}

double *t26 = malloc(sizeof(double)*P_ncols*P_ncols);
double *t23 = malloc(sizeof(double)*nparts__s2917*P_ncols*P_ncols);
double *t17 = t26;
double *t14 = t26;
double *t13 = t26;
double *t12 = t23;
double *t9 = t23;
double *t67 = t23;
double *t10 = A;
double *t8 = A;
predict_0_msg_t *predict_0 = malloc(sizeof(predict_0_msg_t)*nparts__s2917);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s2917);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2917,ii+=1) {
// 2_1
int __m2917 = i + __s2917 > P_ncols ? P_ncols - i : __s2917;
double *t22 = t23 + ii*P_ncols*P_ncols;
double *t20 = t10 + i;
double *t21 = P + i*P_ncols;
predict_0[disp].P_ncols = P_ncols;
predict_0[disp].t21 = t21;
predict_0[disp].__m2917 = __m2917;
predict_0[disp].t20 = t20;
predict_0[disp].t22 = t22;
predict_0[disp].__s2916 = __s2916;

pthread_create(&threads_0[disp], NULL, predict_body_0, (void *)(predict_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s2917; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(predict_0);
{
int __j;
int __k;
int __l;
for (i=0,ii=0; i<P_ncols; i+=__s2917,ii+=1) {
// 2_1
int __m2917 = i + __s2917 > P_ncols ? P_ncols - i : __s2917;
if ((ii == 0)) {
for (__j = 0; __j < P_ncols; __j+=__s2916) {
int __m2916 = __j + __s2916 > P_ncols ? P_ncols - __j : __s2916;
for (__k = 0; __k < __m2916; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t67[__j*P_ncols+__k*P_ncols+__l] = t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
} else {
for (__j = 0; __j < P_ncols; __j+=__s2916) {
int __m2916 = __j + __s2916 > P_ncols ? P_ncols - __j : __s2916;
for (__k = 0; __k < __m2916; __k+=1) {
for (__l = 0; __l < P_ncols; __l+=1) {
t67[__j*P_ncols+__k*P_ncols+__l] += t23[ii*P_ncols*P_ncols+__j*P_ncols+__k*P_ncols+__l];
}
}
}
}
}
}

for (i=0; i<P_ncols; i+=__s2918) {
// 4_1
int __m2918 = i + __s2918 > P_ncols ? P_ncols - i : __s2918;
double *t25 = t26 + i*P_ncols;
double *t24 = t12 + i*P_ncols;
for (j=0; j<__m2918; j+=1) {
// 4_2
double *t35 = t25 + j*P_ncols;
double *t34 = t24 + j*P_ncols;
for (k=0; k<P_ncols; k+=1) {
// 4_3
double *t51 = A + k*P_ncols;
t35[k] = 0.0;
for (l=0; l<P_ncols; l+=1) {
// 4_4
t35[k] += (t34[l]*t51[l]);
}
}
}
}
predict_1_msg_t *predict_1 = malloc(sizeof(predict_1_msg_t)*nparts__s2920);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s2920);
disp = 0;
for (i=0,ii=0; i<P_ncols; i+=__s2920,ii+=1) {
// 6_1
int __m2920 = i + __s2920 > P_ncols ? P_ncols - i : __s2920;
double *t29 = P + i;
double *t27 = t17 + i;
double *t28 = Q + i;
predict_1[disp].__m2920 = __m2920;
predict_1[disp].P_ncols = P_ncols;
predict_1[disp].t28 = t28;
predict_1[disp].t27 = t27;
predict_1[disp].t29 = t29;
predict_1[disp].__s2919 = __s2919;

pthread_create(&threads_1[disp], NULL, predict_body_1, (void *)(predict_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s2920; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(predict_1);
free(t26);
free(t23);
}
