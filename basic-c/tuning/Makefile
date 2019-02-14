

tuned_o: non_tuned.c
	icpc -O2 -c non_tuned.c -DUSE_CALI -lcaliper
	icpc -O2 -c transpose_matrix/_transpose_matrix.c -DUSE_CALI -lcaliper
	icpc -O2 -c multiply_matrix_by_scalar/_multiply_matrix_by_scalar.c -DUSE_CALI -lcaliper
	icpc -O2 -c multiply_matrix/_multiply_matrix.c -DUSE_CALI -lcaliper
	icpc -O2 -c compute_LUP_inline/_compute_LUP_inline.c -DUSE_CALI -lcaliper
	icpc -O2 -c add_mat/_add_mat.c -DUSE_CALI -lcaliper

gcc_tuned_o: non_tuned.c
	gcc-4.9 -c -g non_tuned.c
	gcc-4.9 -O3 -c -g transpose_matrix/_transpose_matrix.c
	gcc-4.9 -O3 -c -g multiply_matrix_by_scalar/_multiply_matrix_by_scalar.c
	gcc-4.9 -O1 -c -g multiply_matrix/_multiply_matrix.c
	gcc-4.9 -O3 -c -g compute_LUP_inline/_compute_LUP_inline.c
	gcc-4.9 -O2 -c -g add_mat/_add_mat.c

test_tuned_linear:
	gcc ../test_linear_algebra.c tuned_linear_algebra.c -o test_linear.out

clean:
	rm -f *.json *.dot *.o *.log
	./rm_logs.sh

