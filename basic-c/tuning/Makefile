tuned_o: non_tuned.c
	icc -c non_tuned.c
	icc -O3 -c transpose_matrix/_transpose_matrix.c
	icc -O3 -c multiply_matrix_by_scalar/_multiply_matrix_by_scalar.c
	icc -O1 -c multiply_matrix/_multiply_matrix.c
	icc -O3 -c compute_LUP_inline/_compute_LUP_inline.c
	icc -O2 -c add_mat/_add_mat.c

test_tuned_linear:
	gcc ../test_linear_algebra.c tuned_linear_algebra.c -o test_linear.out

clean:
	rm -f *.json *.dot *.o *.log
	./rm_logs.sh

