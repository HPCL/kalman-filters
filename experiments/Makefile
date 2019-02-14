CC = icpc -std=c++11
OPT = -O2 -march=native

KALMAN_FILES  = linear_algebra.o # 
KALMAN_FILES += kalman_filter.o #


TUNED_LA_FILES  = ../basic-c/tuning/non_tuned.o
TUNED_LA_FILES += ../basic-c/tuning/_add_mat.o
TUNED_LA_FILES += ../basic-c/tuning/_compute_LUP_inline.o
TUNED_LA_FILES += ../basic-c/tuning/_multiply_matrix.o
TUNED_LA_FILES += ../basic-c/tuning/_multiply_matrix_by_scalar.o
TUNED_LA_FILES += ../basic-c/tuning/_transpose_matrix.o



all: Target.o projectile_tester

projectile_tester: projectile_tester.cpp Target.o
	$(CC) $(OPT) -c ../batched/kalman_filter.c
	$(CC) $(OPT) -c ../batched/linear_algebra.c -DUSE_CALI -lcaliper
	$(CC) $(OPT) projectile_tester.cpp Target.o $(KALMAN_FILES) -o projectile_tester.out -DUSE_CALI -lcaliper

projectile_tester_tuned_LA: projectile_tester.cpp Target.o
	$(CC) $(OPT) -c ../batched/kalman_filter.c
	$(CC) projectile_tester.cpp Target.o $(TUNED_LA_FILES) kalman_filter.o -o tuned_LA_projectile_tester.out -DUSE_CALI -lcaliper


Target.o: Target.cpp Target.hpp
	$(CC) Target.cpp -c

clean:
	rm -f *.o
	rm -f *.out
