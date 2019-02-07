CC = icpc -g


# CFLAGS  = -I${CALIPER_DIR}/include
CFLAGS += -DUSE_CALI

# LDFLAGS  = -L${CALIPER_DIR}/lib
LDFLAGS  = -lcaliper


test_linear:
		$(CC) test_linear_algebra.c matrix_batch.c linear_algebra.c -o test_linear.out -fopenmp

test_kalman: 
		$(CC) -o test_kalman.out test-kalman.c kalman_filter.c linear_algebra.c $(CFLAGS)  $(LDFLAGS)

libs:
		$(CC) kalman_filter.c -g -c
		$(CC) linear_algebra.c -g -c

clean:
		rm -f *.log *.o *.dot