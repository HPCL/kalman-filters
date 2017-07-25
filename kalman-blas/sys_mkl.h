// use to make it work with MKL
#include <mkl_cblas.h>
#include <mkl_lapacke.h>

#define DGETRF LAPACKE_dgetrf
#define DGETRI LAPACKE_dgetri

#define IPIV_TYPE long long