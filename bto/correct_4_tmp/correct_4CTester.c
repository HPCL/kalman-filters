#include <stdlib.h>
#include <stdio.h>
#include "testUtils.h"

extern void correct4(int C_nrows, int C_ncols, double C[C_nrows][C_ncols], int I_nrows, int I_ncols, double I[I_nrows][I_ncols], int K_nrows, int K_ncols, double K[K_nrows][K_ncols], int xhn_nrows, int xhn_ncols, double xhn[xhn_nrows][xhn_ncols], int y_nrows, int y_ncols, double y[y_nrows][y_ncols], int P_nrows, int P_ncols, double P[P_nrows][P_ncols], int xh_nrows, int xh_ncols, double xh[xh_nrows][xh_ncols]);

void blas_correct4(int C_nrows, int C_ncols, double C[C_nrows][C_ncols], int I_nrows, int I_ncols, double I[I_nrows][I_ncols], int K_nrows, int K_ncols, double K[K_nrows][K_ncols], int xhn_nrows, int xhn_ncols, double xhn[xhn_nrows][xhn_ncols], int y_nrows, int y_ncols, double y[y_nrows][y_ncols], int P_nrows, int P_ncols, double P[P_nrows][P_ncols], int xh_nrows, int xh_ncols, double xh[xh_nrows][xh_ncols]) {
int i;
double *t4=(double*)malloc(sizeof(double)*K_ncols*xhn_ncols);
// t4 = C * xhn
cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,K_ncols,xhn_ncols,P_nrows,1.0,C,P_nrows,xhn,xhn_ncols,0.0,t4,xhn_ncols);
double *t5=(double*)malloc(sizeof(double)*K_ncols*xhn_ncols);
// t5 = y - t4
for (i = 0; i < K_ncols; ++i) {
cblas_dcopy(xhn_ncols,y+i*xhn_ncols,1,t5+i*xhn_ncols,1);
cblas_daxpy(xhn_ncols,-1.0,t4+i*xhn_ncols,1,t5+i*xhn_ncols,1);
}
double *t6=(double*)malloc(sizeof(double)*P_nrows*xhn_ncols);
// t6 = K * t5
cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,P_nrows,xhn_ncols,K_ncols,1.0,K,K_ncols,t5,xhn_ncols,0.0,t6,xhn_ncols);
// xh = xhn + t6
for (i = 0; i < P_nrows; ++i) {
cblas_dcopy(xhn_ncols,t6+i*xhn_ncols,1,xh+i*xhn_ncols,1);
cblas_daxpy(xhn_ncols,1.0,xhn+i*xhn_ncols,1,xh+i*xhn_ncols,1);
}
double *t9=(double*)malloc(sizeof(double)*P_nrows*P_nrows);
// t9 = K * C
cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,P_nrows,P_nrows,K_ncols,1.0,K,K_ncols,C,P_nrows,0.0,t9,P_nrows);
double *t10=(double*)malloc(sizeof(double)*P_nrows*P_nrows);
// t10 = I - t9
for (i = 0; i < P_nrows; ++i) {
cblas_dcopy(P_nrows,I+i*P_nrows,1,t10+i*P_nrows,1);
cblas_daxpy(P_nrows,-1.0,t9+i*P_nrows,1,t10+i*P_nrows,1);
}
// P = t10 * P
cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,P_nrows,P_ncols,P_nrows,1.0,t10,P_nrows,P,P_ncols,0.0,P,P_ncols);
free(t4);
free(t5);
free(t6);
free(t9);
free(t10);
}



int main (int argc, char *argv[]) {
int i;
int N = 6;
int start = 6;
int step = 1;



int cnt = 0;
int failedCnt = 0;
int K_ncols = 6;
int P_ncols = 6;
int P_nrows = 6;
int xhn_ncols = 6;
double* C = (double*) malloc(sizeof(double)*K_ncols*P_nrows);
for (i=0; i < K_ncols*P_nrows; ++i)
C[i] = val();
double* I = (double*) malloc(sizeof(double)*P_nrows*P_nrows);
for (i=0; i < P_nrows*P_nrows; ++i)
I[i] = val();
double* K = (double*) malloc(sizeof(double)*P_nrows*K_ncols);
for (i=0; i < P_nrows*K_ncols; ++i)
K[i] = val();
double* P = (double*) malloc(sizeof(double)*3*P_nrows*P_ncols);
double* refP = P+P_nrows*P_ncols;
double* origP = P+P_nrows*P_ncols*2;
for (i=0; i < P_nrows*P_ncols; ++i)
origP[i] = val();
double* xh = (double*) malloc(sizeof(double)*3*P_nrows*xhn_ncols);
double* refxh = xh+P_nrows*xhn_ncols;
double* origxh = xh+P_nrows*xhn_ncols*2;
for (i=0; i < P_nrows*xhn_ncols; ++i)
origxh[i] = val();
double* xhn = (double*) malloc(sizeof(double)*P_nrows*xhn_ncols);
for (i=0; i < P_nrows*xhn_ncols; ++i)
xhn[i] = val();
double* y = (double*) malloc(sizeof(double)*K_ncols*xhn_ncols);
for (i=0; i < K_ncols*xhn_ncols; ++i)
y[i] = val();


for (K_ncols=start; K_ncols <= N; K_ncols+=step) {
for (P_ncols=start; P_ncols <= N; P_ncols+=step) {
for (P_nrows=start; P_nrows <= N; P_nrows+=step) {
for (xhn_ncols=start; xhn_ncols <= N; xhn_ncols+=step) {
++cnt;
memcpy(P,origP,sizeof(double)*P_nrows*P_ncols);
memcpy(xh,origxh,sizeof(double)*P_nrows*xhn_ncols);
correct4(K_ncols, P_nrows, C, P_nrows, P_nrows, I, P_nrows, K_ncols, K, P_nrows, xhn_ncols, xhn, K_ncols, xhn_ncols, y, P_nrows, P_ncols, P, P_nrows, xhn_ncols, xh);
memcpy(refP,origP,sizeof(double)*P_nrows*P_ncols);
memcpy(refxh,origxh,sizeof(double)*P_nrows*xhn_ncols);
blas_correct4(K_ncols, P_nrows, C, P_nrows, P_nrows, I, P_nrows, K_ncols, K, P_nrows, xhn_ncols, xhn, K_ncols, xhn_ncols, y, P_nrows, P_ncols, refP, P_nrows, xhn_ncols, refxh);
if (checkMatrix(P,refP,P_nrows,P_ncols,P_ncols,CblasRowMajor,P_nrows-1+P_nrows +(1 +(K_ncols-1+K_ncols)))){
++failedCnt;
#ifdef END_EARLY
goto END;
#endif
continue;
}
if (checkMatrix(xh,refxh,P_nrows,xhn_ncols,xhn_ncols,CblasRowMajor,1 +(K_ncols-1+K_ncols +(1 +(P_nrows-1+P_nrows))))){
++failedCnt;
#ifdef END_EARLY
goto END;
#endif
continue;
}
}
}
}
}
END:
reportStatus(cnt, failedCnt, NULL);
free(C);
free(I);
free(K);
free(P);
free(xh);
free(xhn);
free(y);
return 0;
}
