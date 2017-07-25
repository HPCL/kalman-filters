MKL_LINK = -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl #
MKL_OPT  = -DMKL_ILP64 -I${MKLROOT}/include #
ATLAS_SYS  = -DSYS=\"sys_mkl.h\"

ATLAS_LINK = -L${ATLASLIB} -lcblas -llapack -lptcblas -lpthread -latlas
ATLAS_INC  = -I${ATLASINC}
ATLAS_SYS  = -DSYS=\"sys_atlas.h\"

CBLAS_LINK = -I${OPENBLASINC} -L${OPENBLASLIB} -lopenblas -lgfortran
CBLAS_SYS  = -DSYS=\"sys_cblas.h\"

test_linear:
		icc test_blas.c -o test_blas.out $(MKL_OPT) $(MKL_LINK)

test_kalman:
		icc test-kalman.c kalman_filter.c -o test-kalman.out $(MKL_OPT) $(MKL_LINK) 

test_kalman_atlas:
	icc test-kalman.c kalman_filter.c $(ATLAS_SYS) -o test-kalman.out $(ATLAS_LINK) $(ATLAS_INC)

test_kalman_blas:
	icc test-kalman.c kalman_filter.c $(CBLAS_SYS) -o test-kalman.out $(CBLAS_LINK) 

mkl_o:
	icc kalman_filter.c -c $(MKL_OPT) $(MKL_LINK) 

atlas_o:
	icc kalman_filter.c -c $(ATLAS_SYS) $(ATLAS_LINK) $(ATLAS_INC)

blas_o:
	icc kalman_filter.c -c $(CBLAS_SYS) $(CBLAS_LINK) $(CBLAS_INC)
