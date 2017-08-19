#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define max(__a__,__b__) (__a__ > __b__ ? __a__ : __b__)


typedef struct { 
int xhn_ncols;
int P_nrows;
int K_ncols;
double *K;
double *C;
double *t50;
double *t47;
double *t59;
int __s206;
int __m207;
} correct4_2_msg_t;

typedef struct { 
int P_nrows;
double *t65;
double *t64;
double *t66;
int __s216;
int __m217;
} correct4_1_msg_t;

typedef struct { 
int P_nrows;
double *C;
int K_ncols;
double *t61;
double *t62;
int __s214;
int __m215;
} correct4_0_msg_t;

void *correct4_body_0(void *mesg) {
int disp, __zr__,j,k,l,p;
correct4_0_msg_t *msg = (correct4_0_msg_t*)mesg;
int P_nrows = msg->P_nrows;
double *C = msg->C;
int K_ncols = msg->K_ncols;
double *t61 = msg->t61;
double *t62 = msg->t62;
int __s214 = msg->__s214;
int __m215 = msg->__m215;

// ORIO A
for (j=0; j<=__m215-1; j+=__s214) {
  // 9_2
  int __m214 = j + __s214 > __m215 ? __m215 - j : __s214;
  // double *t86 = t62 + j*P_nrows;
  // double *t85 = t61 + j*K_ncols;
  for (k=0; k<=__m214-1; k+=1) {
    // 9_3
    // double *t110 = t62[j*P_nrows] + k*P_nrows;
    // double *t109 = t61[j*K_ncols] + k*K_ncols;
    for (__zr__ = 0; __zr__ <= P_nrows-1; ++__zr__) t62[j*P_nrows + k*P_nrows + __zr__] = 0.0;
    for (l=0; l<K_ncols; l+=1) {
      // 9_4
      double *t137 = C + l*P_nrows;
      for (p=0; p<=P_nrows-1; p+=1) {
        // 9_5
        t62[j*P_nrows + k*P_nrows + p] += (t61[j*K_ncols + k*K_ncols + l]*C[l*P_nrows + p]);
      }
    }
  }
}

return NULL;
}


void *correct4_body_1(void *mesg) {
int disp, __zr__,j,k,l;
correct4_1_msg_t *msg = (correct4_1_msg_t*)mesg;
int P_nrows = msg->P_nrows;
double *t65 = msg->t65;
double *t64 = msg->t64;
double *t66 = msg->t66;
int __s216 = msg->__s216;
int __m217 = msg->__m217;

//ORIO B
for (j=0; j<=__m217-1; j+=__s216) {
  // 10_2
  int __m216 = j + __s216 > __m217 ? __m217 - j : __s216;
  // double *t90 = t66 + j*P_nrows;
  // double *t88 = t64 + j*P_nrows;
  // double *t89 = t65 + j*P_nrows;
  for (k=0; k<=__m216-1; k+=1) {
    // 10_3
    // double *t114 = t66[j*P_nrows + k*P_nrows]; 
    // double *t112 = t64[j*P_nrows + k*P_nrows];
    // double *t113 = t65[j*P_nrows + k*P_nrows];
    for (l=0; l<=P_nrows-1; l+=1) {
      // 10_4
      t66[j*P_nrows + k*P_nrows + l] = (t64[j*P_nrows + k*P_nrows + l]-t65[j*P_nrows + k*P_nrows + l]);
    }
  }
}
return NULL;
}


void *correct4_body_2(void *mesg) {
int disp, __zr__,j,k,l,p;
correct4_2_msg_t *msg = (correct4_2_msg_t*)mesg;
int xhn_ncols = msg->xhn_ncols;
int P_nrows = msg->P_nrows;
int K_ncols = msg->K_ncols;
double *K = msg->K;
double *C = msg->C;
double *t50 = msg->t50;
double *t47 = msg->t47;
double *t59 = msg->t59;
int __s206 = msg->__s206;
int __m207 = msg->__m207;


//ORIO C
for (j=0; j<=__m207-1; j+=__s206) {
  // 4_2
  int __m206 = j + __s206 > __m207 ? __m207 - j : __s206;
  double *t96 = malloc(sizeof(double)*__s206);
  double *t79 = malloc(sizeof(double)*P_nrows*__s206);
  double *t76 = malloc(sizeof(double)*K_ncols*__s206);
  // double *t83 = t59 + j;
  // double *t71 = t47 + j;
  // double *t74 = t50 + j;
  for (k=0; k<=K_ncols-1; k+=1) {
    // 4_3
    // double *t100 = t76[k*__m206];
    // double *t95 = C[k*P_nrows];
    // double *t98 = t50[j + k*xhn_ncols];
    for (__zr__ = 0; __zr__ <= __m206-1; ++__zr__) t96[__zr__] = 0.0;
    for (l=0; l<=P_nrows-1; l+=1) {
      // 4_4
      // double *t121 = t47[j + l*xhn_ncols];
      for (p=0; p<=__m206-1; p+=1) {
        // 4_5
        t96[p] += (C[k*P_nrows + l]*t47[j + l*xhn_ncols+p]);
      }
    }
    for (l=0; l<=__m206-1; l+=1) {
      // 5_4
      t76[k*__m206 + l] = (t50[j + k*xhn_ncols+l]-t96[l]);
    }
  }
  for (k=0; k<=P_nrows-1; k+=1) {
    // 6_3
    // double *t103 = t79 + k*__m206;
    double *t102 = K[k*K_ncols];
    for (__zr__ = 0; __zr__ <=__m206-1; ++__zr__) t79[k*__m206+__zr__] = 0.0;
    for (l=0; l<=K_ncols-1; l+=1) {
      // 6_4
      double *t129 = t76 + l*__m206;
      for (p=0; p<=__m206-1; p+=1) {
        // 6_5
        t79[k*__m206+p] += (K[k*K_ncols+l]*t76[l*__m206+p]);
      }
    }
  }
  for (k=0; k<=P_nrows-1; k+=1) {
    // 7_3
    // double *t107 = t59[j + k*xhn_ncols];
    // double *t105 = t47[j + k*xhn_ncols];
    // double *t106 = t79 + k*__m206;
    for (l=0; l<=__m206-1; l+=1) {
      // 7_4
      t59[j + k*xhn_ncols+l] = (t47[j + k*xhn_ncols+l]+t79[k*__m206+l]);
    }
  }
  free(t96);
  free(t79);
  free(t76);
}
return NULL;
}


void correct4
(int C_nrows, int C_ncols, double* C, int I_nrows, int I_ncols, double* I, int K_nrows, int K_ncols, double* K, int xhn_nrows, int xhn_ncols, double* xhn, int y_nrows, int y_ncols, double* y, int P_nrows, int P_ncols, double* P, int xh_nrows, int xh_ncols, double* xh)
{
int disp, __zr__,i,ii,j,k,l;

int __s218 = 2;

int __s216 = 512;

int __s214 = 512;

int __s206 = 504;

int nparts__s217 = 12;
int __s217;
if (nparts__s217 > 1 && P_nrows > nparts__s217) {
__s217 = P_nrows/nparts__s217;
// this will fail if P_nrows%nparts__s217+__s217 > nparts__s217
// which primarily effects small sizes
if (P_nrows%nparts__s217)
++__s217;
}
else {
__s217 = P_nrows;
nparts__s217 = 1;
}

int nparts__s215 = 12;
int __s215;
if (nparts__s215 > 1 && P_nrows > nparts__s215) {
__s215 = P_nrows/nparts__s215;
// this will fail if P_nrows%nparts__s215+__s215 > nparts__s215
// which primarily effects small sizes
if (P_nrows%nparts__s215)
++__s215;
}
else {
__s215 = P_nrows;
nparts__s215 = 1;
}

int nparts__s207 = 12;
int __s207;
if (nparts__s207 > 1 && xhn_ncols > nparts__s207) {
__s207 = xhn_ncols/nparts__s207;
// this will fail if xhn_ncols%nparts__s207+__s207 > nparts__s207
// which primarily effects small sizes
if (xhn_ncols%nparts__s207)
++__s207;
}
else {
__s207 = xhn_ncols;
nparts__s207 = 1;
}

double *t67 = malloc(sizeof(double)*P_nrows*P_nrows);
double *t63 = malloc(sizeof(double)*P_nrows*P_nrows);
double *t45 = t67;
double *t41 = t67;
double *t44 = t67;
double *t43 = t63;
double *t40 = t63;
double *t36 = t63;
double *t38 = t63;
double *t37 = K;
double *t35 = K;
correct4_0_msg_t *correct4_0 = malloc(sizeof(correct4_0_msg_t)*nparts__s215);
pthread_t *threads_0 = malloc(sizeof(pthread_t)*nparts__s215);
disp = 0;
for (i=0,ii=0; i<P_nrows; i+=__s215,ii+=1) {
  // 9_1
  int __m215 = i + __s215 > P_nrows ? P_nrows - i : __s215;
  double *t62 = t63 + i*P_nrows;
  double *t61 = t37 + i*K_ncols;
  correct4_0[disp].P_nrows = P_nrows;
  correct4_0[disp].C = C;
  correct4_0[disp].K_ncols = K_ncols;
  correct4_0[disp].t61 = t61;
  correct4_0[disp].t62 = t62;
  correct4_0[disp].__s214 = __s214;
  correct4_0[disp].__m215 = __m215;

  pthread_create(&threads_0[disp], NULL, correct4_body_0, (void *)(correct4_0+disp));
  ++disp;
}
for (disp = 0; disp < nparts__s215; ++disp) {
  pthread_join(threads_0[disp],NULL);
}

free(threads_0);
free(correct4_0);
correct4_1_msg_t *correct4_1 = malloc(sizeof(correct4_1_msg_t)*nparts__s217);
pthread_t *threads_1 = malloc(sizeof(pthread_t)*nparts__s217);
disp = 0;
for (i=0,ii=0; i<P_nrows; i+=__s217,ii+=1) {
  // 10_1
  int __m217 = i + __s217 > P_nrows ? P_nrows - i : __s217;
  double *t66 = t67 + i*P_nrows;
  double *t64 = I + i*P_nrows;
  double *t65 = t43 + i*P_nrows;
  correct4_1[disp].P_nrows = P_nrows;
  correct4_1[disp].t65 = t65;
  correct4_1[disp].t64 = t64;
  correct4_1[disp].t66 = t66;
  correct4_1[disp].__s216 = __s216;
  correct4_1[disp].__m217 = __m217;

  pthread_create(&threads_1[disp], NULL, correct4_body_1, (void *)(correct4_1+disp));
  ++disp;
}
for (disp = 0; disp < nparts__s217; ++disp) {
pthread_join(threads_1[disp],NULL);
}

free(threads_1);
free(correct4_1);

//ORIO D
for (i=0; i<=P_nrows-1; i+=__s218) {
  // 12_1
  int __m218 = i + __s218 > P_nrows ? P_nrows - i : __s218;
  // double *t69 = P + i*P_ncols;
  double *t68 = t45 + i*P_nrows;
  for (j=0; j<=__m218-1; j+=1) {
    // 12_2
    // double *t93 = P[i*P_ncols + j*P_ncols];
    // double *t92 = t45[i*P_nrows + j*P_nrows];
    for (__zr__ = 0; __zr__ <=P_ncols-1; ++__zr__) P[i*P_ncols + j*P_ncols + __zr__] = 0.0;
    for (k=0; k<=P_nrows-1; k+=1) {
      // 12_3
      // double *t117 = P + k*P_ncols;
      for (l=0; l<=P_ncols-1; l+=1) {
        // 12_4
        P[i*P_ncols + j*P_ncols + l] += (t45[i*P_nrows + j*P_nrows + k]*P[k*P_ncols+l]);
      }
    }
  }
}

correct4_2_msg_t *correct4_2 = malloc(sizeof(correct4_2_msg_t)*nparts__s207);
pthread_t *threads_2 = malloc(sizeof(pthread_t)*nparts__s207);
disp = 0;
for (i=0,ii=0; i<xhn_ncols; i+=__s207,ii+=1) {
// 4_1
int __m207 = i + __s207 > xhn_ncols ? xhn_ncols - i : __s207;
double *t59 = xh + i;
double *t47 = xhn + i;
double *t50 = y + i;
correct4_2[disp].xhn_ncols = xhn_ncols;
correct4_2[disp].P_nrows = P_nrows;
correct4_2[disp].K_ncols = K_ncols;
correct4_2[disp].K = K;
correct4_2[disp].C = C;
correct4_2[disp].t50 = t50;
correct4_2[disp].t47 = t47;
correct4_2[disp].t59 = t59;
correct4_2[disp].__s206 = __s206;
correct4_2[disp].__m207 = __m207;

pthread_create(&threads_2[disp], NULL, correct4_body_2, (void *)(correct4_2+disp));
++disp;
}
for (disp = 0; disp < nparts__s207; ++disp) {
pthread_join(threads_2[disp],NULL);
}

free(threads_2);
free(correct4_2);
free(t67);
free(t63);
}
