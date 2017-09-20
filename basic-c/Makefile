CC = gcc
BTO_FILES  = ../bto/kalman_filter.c
BTO_FILES += ../bto/predict_1.c
#BTO_FILES += ../bto/predict_2.c
BTO_FILES += ../bto/correct_3a.c
BTO_FILES += ../bto/correct_3b.c
BTO_FILES += ../bto/correct_4.c

test_linear:
		$(CC) test_linear_algebra.c linear_algebra.c -o test_linear.out

test_kalman:
		$(CC) test-kalman.c kalman_filter.c linear_algebra.c -o test_kalman.out

test_kalman_bto:
		$(CC) test-kalman.c $(BTO_FILES) linear_algebra.c -o test_kalman_bto.out -lpthread

test_kalman_db:
		$(CC) test-kalman.c kalman_filter.c linear_algebra.c -g -o test_kalman.out

run_orio_linear:
		orcc -v -d linear_algebra.c

run_orio_test:
		orcc -v -d orio_test.c
 
clean:
		rm -f *.log *.o *.dot