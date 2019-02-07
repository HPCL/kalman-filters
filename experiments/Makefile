CC = icpc -std=c++11

KALMAN_FILES  = linear_algebra.o # 
KALMAN_FILES += kalman_filter.o #

all: Target.o projectile_tester

projectile_tester: projectile_tester.cpp Target.o
	$(CC) -c ../batched/kalman_filter.c
	$(CC) -c ../batched/linear_algebra.c -DUSE_CALI -lcaliper
	$(CC) projectile_tester.cpp Target.o $(KALMAN_FILES) -o projectile_tester.out -DUSE_CALI -lcaliper


Target.o: Target.cpp Target.hpp
	$(CC) Target.cpp -c

clean:
	rm -f *.o
	rm -f *.out
