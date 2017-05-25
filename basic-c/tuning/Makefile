UNTUNED_FILES  = non_tuned.c #
UNTUNED_FILES += add_mat/add_mat.c #
UNTUNED_FILES += cofactor_matrix/cofactor_matrix.c #
UNTUNED_FILES += compute_LUP/compute_LUP.c #
UNTUNED_FILES += compute_LUP_inline/compute_LUP_inline.c #
UNTUNED_FILES += determinant_matrix/determinant_matrix.c #
UNTUNED_FILES += multiply_matrix/multiply_matrix.c #
UNTUNED_FILES += multiply_matrix_by_scalar/multiply_matrix_by_scalar.c #
UNTUNED_FILES += transpose_matrix/transpose_matrix.c #

TUNED_FILES  = non_tuned.c #
TUNED_FILES += add_mat/_add_mat.c #
TUNED_FILES += cofactor_matrix/_cofactor_matrix.c #
TUNED_FILES += compute_LUP/_compute_LUP.c #
TUNED_FILES += compute_LUP_inline/_compute_LUP_inline.c #
TUNED_FILES += determinant_matrix/_determinant_matrix.c #
TUNED_FILES += multiply_matrix/_multiply_matrix.c #
TUNED_FILES += multiply_matrix_by_scalar/_multiply_matrix_by_scalar.c #
TUNED_FILES += transpose_matrix/_transpose_matrix.c #

test_linear:
	gcc ../test_linear_algebra.c $(UNTUNED_FILES) -o test_linear.out

test_tuned_linear:
	gcc ../test_linear_algebra.c $(TUNED_FILES) -o test_linear.out

clean:
	rm -f *.json *.dot *.o *.log

