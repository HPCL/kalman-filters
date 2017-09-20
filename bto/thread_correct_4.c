#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int __m125;
int xhn_ncols;
double *t32;
double *t44;
int P_nrows;
int K_ncols;
double *K;
double *t35;
double *C;
int __s125;
} correct4_3_msg_t;

typedef struct { 
int P_ncols;
double *P;
int P_nrows;
double *t53;
double *t54;
int __m131;
} correct4_2_msg_t;

typedef struct { 
int P_nrows;
double *t50;
double *t49;
double *t51;
int __m130;
} correct4_1_msg_t;

typedef struct { 
int P_nrows;
double *C;
int K_ncols;
double *t46;
double *t47;
int __m129;
} correct4_0_msg_t;

void *correct4_body_0(void *mesg) {
int disp, __zr__,j,k,l;
correct4_0_msg_t *msg = (correct4_0_msg_t*)mesg;
int P_nrows = msg->P_nrows;
double *C = msg->C;
int K_ncols = msg->K_ncols;
double *t46 = msg->t46;
double *t47 = msg->t47;
int __m129 = msg->__m129;

for (j=0; j<__m129; j+=1) {
// 9_2
double *t71 = t47 + j*P_nrows;
double *t70 = t46 + j*K_ncols;
for (__zr__ = 0; __zr__ < P_nrows; ++__zr__) t71[__zr__] = 0.0;
for (k=0; k<K_ncols; k+=1) {
// 9_3
double *t97 = C + k*P_nrows;
for (l=0; l<P_nrows; l+=1) {
// 9_4
t71[l] += (t70[k]*t97[l]);
}
}
}
return NULL;
}


void *correct4_body_1(void *mesg) {
int disp, __zr__,j,k;
correct4_1_msg_t *msg = (correct4_1_msg_t*)mesg;
int P_nrows = msg->P_nrows;
double *t50 = msg->t50;
double *t49 = msg->t49;
double *t51 = msg->t51;
int __m130 = msg->__m130;

for (j=0; j<__m130; j+=1) {
// 10_2
double *t75 = t51 + j*P_nrows;
double *t73 = t49 + j*P_nrows;
double *t74 = t50 + j*P_nrows;
for (k=0; k<P_nrows; k+=1) {
// 10_3
t75[k] = (t73[k]-t74[k]);
}
}
return NULL;
}


void *correct4_body_2(void *mesg) {
int disp, __zr__,j,k,l;
correct4_2_msg_t *msg = (correct4_2_msg_t*)mesg;
int P_ncols = msg->P_ncols;
double *P = msg->P;
int P_nrows = msg->P_nrows;
double *t53 = msg->t53;
double *t54 = msg->t54;
int __m131 = msg->__m131;

for (j=0; j<__m131; j+=1) {
// 12_2
double *t78 = t54 + j*P_ncols;
double *t77 = t53 + j*P_nrows;
for (__zr__ = 0; __zr__ < P_ncols; ++__zr__) t78[__zr__] = 0.0;
for (k=0; k<P_nrows; k+=1) {
// 12_3
double *t105 = P + k*P_ncols;
for (l=0; l<P_ncols; l+=1) {
// 12_4
t78[l] += (t77[k]*t105[l]);
}
}
}
return NULL;
}


void *correct4_body_3(void *mesg) {
int disp, __zr__,j,k,l;
correct4_3_msg_t *msg = (correct4_3_msg_t*)mesg;
int __m125 = msg->__m125;
int xhn_ncols = msg->xhn_ncols;
double *t32 = msg->t32;
double *t44 = msg->t44;
int P_nrows = msg->P_nrows;
int K_ncols = msg->K_ncols;
double *K = msg->K;
double *t35 = msg->t35;
double *C = msg->C;
int __s125 = msg->__s125;

double *t40 = malloc(sizeof(double)*P_nrows*__s125);
double *t37 = malloc(sizeof(double)*K_ncols*__s125);
double *t33 = malloc(sizeof(double)*K_ncols*__s125);
for (j=0; j<K_ncols; j+=1) {
// 4_2
double *t57 = t33 + j*__m125;
double *t56 = C + j*P_nrows;
for (__zr__ = 0; __zr__ < __m125; ++__zr__) t57[__zr__] = 0.0;
for (k=0; k<P_nrows; k+=1) {
// 4_3
double *t81 = t32 + k*xhn_ncols;
for (l=0; l<__m125; l+=1) {
// 4_4
t57[l] += (t56[k]*t81[l]);
}
}
}
for (j=0; j<K_ncols; j+=1) {
// 5_2
double *t61 = t37 + j*__m125;
double *t59 = t35 + j*xhn_ncols;
double *t60 = t33 + j*__m125;
for (k=0; k<__m125; k+=1) {
// 5_3
t61[k] = (t59[k]-t60[k]);
}
}
for (j=0; j<P_nrows; j+=1) {
// 6_2
double *t64 = t40 + j*__m125;
double *t63 = K + j*K_ncols;
for (__zr__ = 0; __zr__ < __m125; ++__zr__) t64[__zr__] = 0.0;
for (k=0; k<K_ncols; k+=1) {
// 6_3
double *t89 = t37 + k*__m125;
for (l=0; l<__m125; l+=1) {
// 6_4
t64[l] += (t63[k]*t89[l]);
}
}
}
for (j=0; j<P_nrows; j+=1) {
// 7_2
double *t68 = t44 + j*xhn_ncols;
double *t66 = t32 + j*xhn_ncols;
double *t67 = t40 + j*__m125;
for (k=0; k<__m125; k+=1) {
// 7_3
t68[k] = (t66[k]+t67[k]);
}
}
free(t40);
free(t37);
free(t33);
return NULL;
}


void correct4
(int C_nrows, int C_ncols, double* C, int I_nrows, int I_ncols, double* I, int K_nrows, int K_ncols, double* K, int xhn_nrows, int xhn_ncols, double* xhn, int y_nrows, int y_ncols, double* y, int P_nrows, int P_ncols, double* P, int xh_nrows, int xh_ncols, double* xh)
{
int disp, __zr__,i,ii;

int nparts__s125 = 12;
int __s125;
if (nparts__s125 > 1 && xhn_ncols > nparts__s125) {
__s125 = xhn_ncols/nparts__s125;
// this will fail if xhn_ncols%nparts__s125+__s125 > nparts__s125
// which primarily effects small sizes
if (xhn_ncols%nparts__s125)
++__s125;
}
else {
__s125 = xhn_ncols;
nparts__s125 = 1;
}

int nparts__s129 = 12;
int __s129;
if (nparts__s129 > 1 && P_nrows > nparts__s129) {
__s129 = P_nrows/nparts__s129;
// this will fail if P_nrows%nparts__s129+__s129 > nparts__s129
// which primarily effects small sizes
if (P_nrows%nparts__s129)
++__s129;
}
else {
__s129 = P_nrows;
nparts__s129 = 1;
}

int nparts__s130 = 12;
int __s130;
if (nparts__s130 > 1 && P_nrows > nparts__s130) {
__s130 = P_nrows/nparts__s130;
// this will fail if P_nrows%nparts__s130+__s130 > nparts__s130
// which primarily effects small sizes
if (P_nrows%nparts__s130)
++__s130;
}
else {
__s130 = P_nrows;
nparts__s130 = 1;
}

int nparts__s131 = 12;
int __s131;
if (nparts__s131 > 1 && P_nrows > nparts__s131) {
__s131 = P_nrows/nparts__s131;
// this will fail if P_nrows%nparts__s131+__s131 > nparts__s131
// which primarily effects small sizes
if (P_nrows%nparts__s131)
++__s131;
}
else {
__s131 = P_nrows;
nparts__s131 = 1;
}

double *t52 = malloc(sizeof(double)*P_nrows*P_nrows);
double *t48 = malloc(sizeof(double)*P_nrows*P_nrows);
double *t30 = t52;
double *t29 = t52;
double *t28 = t48;
double *t26 = t48;
double *t25 = K;
correct4_0_msg_t *correct4_0 = malloc(sizeof(correct4_0_msg_t)*nparts__s129);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s129);
disp = 0;
for (i=0,ii=0; i<P_nrows; i+=__s129,ii+=1) {
// 9_1
int __m129 = i + __s129 > P_nrows ? P_nrows - i : __s129;
double *t47 = t48 + i*P_nrows;
double *t46 = t25 + i*K_ncols;
correct4_0[disp].P_nrows = P_nrows;
correct4_0[disp].C = C;
correct4_0[disp].K_ncols = K_ncols;
correct4_0[disp].t46 = t46;
correct4_0[disp].t47 = t47;
correct4_0[disp].__m129 = __m129;

pthread_create(&threads_0[disp], NULL, correct4_body_0, (void *)(correct4_0+disp));
++disp;
}
for (disp = 0; disp < nparts__s129; ++disp) {
pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(correct4_0);
correct4_1_msg_t *correct4_1 = malloc(sizeof(correct4_1_msg_t)*nparts__s130);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s130);
disp = 0;
for (i=0,ii=0; i<P_nrows; i+=__s130,ii+=1) {
// 10_1
int __m130 = i + __s130 > P_nrows ? P_nrows - i : __s130;
double *t51 = t52 + i*P_nrows;
double *t49 = I + i*P_nrows;
double *t50 = t28 + i*P_nrows;
correct4_1[disp].P_nrows = P_nrows;
correct4_1[disp].t50 = t50;
correct4_1[disp].t49 = t49;
correct4_1[disp].t51 = t51;
correct4_1[disp].__m130 = __m130;

pthread_create(&threads_1[disp], NULL, correct4_body_1, (void *)(correct4_1+disp));
++disp;
}
for (disp = 0; disp < nparts__s130; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(correct4_1);
correct4_2_msg_t *correct4_2 = malloc(sizeof(correct4_2_msg_t)*nparts__s131);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s131);
disp = 0;
for (i=0,ii=0; i<P_nrows; i+=__s131,ii+=1) {
// 12_1
int __m131 = i + __s131 > P_nrows ? P_nrows - i : __s131;
double *t54 = P + i*P_ncols;
double *t53 = t30 + i*P_nrows;
correct4_2[disp].P_ncols = P_ncols;
correct4_2[disp].P = P;
correct4_2[disp].P_nrows = P_nrows;
correct4_2[disp].t53 = t53;
correct4_2[disp].t54 = t54;
correct4_2[disp].__m131 = __m131;

pthread_create(&threads_2[disp], NULL, correct4_body_2, (void *)(correct4_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s131; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(correct4_2);
correct4_3_msg_t *correct4_3 = malloc(sizeof(correct4_3_msg_t)*nparts__s125);
pthread_t *threads_3 = malloc(sizeof(pthread_t)*nparts__s125);
disp = 0;
for (i=0,ii=0; i<xhn_ncols; i+=__s125,ii+=1) {
// 4_1
int __m125 = i + __s125 > xhn_ncols ? xhn_ncols - i : __s125;
double *t44 = xh + i;
double *t32 = xhn + i;
double *t35 = y + i;
correct4_3[disp].__m125 = __m125;
correct4_3[disp].xhn_ncols = xhn_ncols;
correct4_3[disp].t32 = t32;
correct4_3[disp].t44 = t44;
correct4_3[disp].P_nrows = P_nrows;
correct4_3[disp].K_ncols = K_ncols;
correct4_3[disp].K = K;
correct4_3[disp].t35 = t35;
correct4_3[disp].C = C;
correct4_3[disp].__s125 = __s125;

pthread_create(&threads_3[disp], NULL, correct4_body_3, (void *)(correct4_3+disp));
++disp;
}
for (disp = 0; disp < nparts__s125; ++disp) {
pthread_join(threads_3[disp],NULL);
}

free(threads_3);
free(correct4_3);
free(t52);
free(t48);
}
