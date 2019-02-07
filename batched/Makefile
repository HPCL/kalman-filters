CC = icc

FILES  = tuning_omp/_add_mat.o
FILES += tuning_omp/_compute_LUP_inline.o
FILES += tuning_omp/_multiply_matrix.o
FILES += tuning_omp/_multiply_matrix_by_scalar.o
FILES += tuning_omp/_transpose_matrix.o
FILES += tuning_omp/non_tuned.o

test_linear:
		$(CC) test_linear_algebra.c matrix_batch.c -o test_linear.out

test_linear_omp:
		$(CC) test_linear_algebra.c $(FILES) -o test_linear.out -fopenmp

test_kalman:
		$(CC) test-kalman.c kalman_filter.c linear_algebra.c -o test_kalman.out

test_kalman_db:
		$(CC) test-kalman.c kalman_filter.c linear_algebra.c -g -o test_kalman.out
 
libs:
		$(CC) kalman_filter.c -g -c
		$(CC) linear_algebra.c -g -c

clean:
		rm -f *.log *.o *.dot