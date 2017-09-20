// use to make it work with ATLAS
#include <cblas.h> 
#include <clapack.h>
#define MKL_INT int
#define LAPACK_ROW_MAJOR ORDER

#define DGETRF clapack_dgetrf
#define DGETRI clapack_dgetri

#define IPIV_TYPE MKL_INT
