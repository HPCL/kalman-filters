// use to make it work with OpenBLAS
#include <cblas.h> 
#include <lapacke.h>
#define MKL_INT int

#define DGETRF LAPACKE_dgetrf
#define DGETRI LAPACKE_dgetri

#define IPIV_TYPE int
