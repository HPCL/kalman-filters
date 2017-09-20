#CBLAS_LINK = -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl #
#CBLAS_OPT  = -DMKL_ILP64 -I${MKLROOT}/include #
MKL_LINK = -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl #
MKL_OPT  = -DMKL_ILP64 -I${MKLROOT}/include #
MKL_SYS  = -DSYS=\"sys_mkl.h\"

ATLAS_LINK = -L/usr/local/atlas/lib -lcblas -llapack -lptcblas -lpthread -latlas
ATLAS_INC  = -I/usr/local/atlas/include
ATLAS_SYS  = -DSYS=\"sys_atlas.h\"

CBLAS_LINK = -L/usr/lib/ -llapacke -lopenblas
CBLAS_SYS  = -DSYS=\"sys_cblas.h\"

test_linear:
		gcc test_blas.c -o test_blas.out $(CBLAS_LINK)

test_kalman_atlas:
	gcc test-kalman.c kalman_filter.c $(ATLAS_SYS) -o test-kalman.out $(ATLAS_LINK) $(ATLAS_INC)

test_kalman_blas:
	gcc test-kalman.c kalman_filter.c $(CBLAS_SYS) -o test-kalman.out $(CBLAS_LINK)

atlas_o:
	gcc kalman_filter.c -c $(ATLAS_SYS) $(ATLAS_LINK) $(ATLAS_INC)

blas_o:
	  gcc kalman_filter.c -c $(CBLAS_SYS) $(CBLAS_LINK)
