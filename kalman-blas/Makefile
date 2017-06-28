#CBLAS_LINK = -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl #
#CBLAS_OPT  = -DMKL_ILP64 -I${MKLROOT}/include #
CBLAS_LINK = -L/usr/lib/ -llapacke -lopenblas

test_linear:
		gcc test_blas.c -o test_blas.out $(CBLAS_LINK)

test_kalman:
		g++ test-kalman.c kalman_filter.c -o test-kalman.out $(CBLAS_LINK) 


blas_o:
	  gcc kalman_filter.c -c $(CBLAS_LINK)
