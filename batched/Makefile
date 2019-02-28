CC = icpc -g


# CFLAGS  = -I${CALIPER_DIR}/include
CFLAGS += -DUSE_CALI

# LDFLAGS  = -L${CALIPER_DIR}/lib
LDFLAGS  = -lcaliper

OPT  = -O2 
# OPT += -qopt-report
OPT += -march=native

TUNE  = batch_tuning/multiply_matrix_batch/_multiply.o
# TUNE  = batch_tuning/multiply_matrix_batch/_multiply.c

test_linear:
		$(CC) test_linear_algebra.c matrix_batch.c linear_algebra.c -o test_linear.out -fopenmp $(OPT)

test_tuned:
		$(CC) test_linear_algebra.c  matrix_batch.c linear_algebra.c $(TUNE) -o test_linear.out -DTUNED -fopenmp $(OPT)

test_kalman: 
		$(CC) -o test_kalman.out test-kalman.c kalman_filter.c linear_algebra.c $(CFLAGS)  $(LDFLAGS)

libs:
		$(CC) kalman_filter.c -g -c
		$(CC) linear_algebra.c -g -c

clean:
		rm -f *.log *.o *.dot *.optrpt