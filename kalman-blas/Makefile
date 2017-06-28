BLAS_LINK = -I/opt/at8.0/include/ -lboost_blas -lrt

test_linear:
		g++ test_blas.c -o test_blas.out $(BLAS_LINK)

test_kalman:
		g++ test-kalman.c kalman_filter.c -o test-kalman.out $(BLAS_LINK)


blas_o:
	g++ kalman_filter.c -c $(BLAS_LINK) 
