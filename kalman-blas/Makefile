CBLAS_LINK = -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl #
CBLAS_OPT  = -DMKL_ILP64 -I${MKLROOT}/include #

test_linear:
		icc test_blas.c -o test_blas.out $(CBLAS_OPT) $(CBLAS_LINK)

test_kalman:
		icc test-kalman.c kalman_filter.c -o test-kalman.out $(CBLAS_OPT) $(CBLAS_LINK) 


blas_o:
	icc kalman_filter.c -c $(CBLAS_OPT) $(CBLAS_LINK)
