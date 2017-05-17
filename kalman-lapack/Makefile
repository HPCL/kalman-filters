CBLAS_LINK = -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl #
CBLAS_OPT  = -DMKL_ILP64 -I${MKLROOT}/include #

test_linear:
		icc test_lapack.c -o test_lapack.out $(CBLAS_OPT) $(CBLAS_LINK)
