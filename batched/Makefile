CC = icpc -g

# MKL_LINK =  -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm -ldl #
MKL_LINK = -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl #
MKL_OPT  = -DMKL_ILP64 -I${MKLROOT}/include #
MKL_SYS  = -DSYS=\"sys_mkl.h\"

CBLAS_LINK = -L/home/users/gravelle/soft/OpenBLAS/lib -lopenblas -lpthread
CBLAS_OPT  = -static -I/home/users/gravelle/soft/OpenBLAS/include

OPT  = -O3
OPT += -std=c++17 
OPT += -qopt-report
OPT += -march=skylake-avx512
OPT += -no-vec 
# OPT += -DUSE_CALI
# OPT += -I${CALIPER_DIR}/include
# OPT += -L${CALIPER_DIR}/lib
# OPT +=  -lcaliper 
OPT +=  -qopt-zmm-usage=high

TUNE  = batch_tuning/multiply_matrix_batch/_multiply.o
# TUNE  = batch_tuning/multiply_matrix_batch/_multiply.c

test_batched_fusion: test_batched_fusion.c linear_algebra.c matrix_batch.c
		$(CC) test_batched_fusion.c matrix_batch.c linear_algebra.c -o test_batched_fusion.out -fopenmp $(OPT)  $(MKL_OPT) $(MKL_LINK) -DNUM_ELMS=${ELMS} -DNUM_MATS=${MATS} -DNUM_REPS=${REPS} -DBATCH_SIZE=${BATCH}

test_linear:
		$(CC) test_linear_algebra.c matrix_batch.c linear_algebra.c -o test_linear.out -fopenmp $(OPT)  $(MKL_OPT) $(MKL_LINK) -DNUM_ELMS=${ELMS} -DNUM_MATS=${MATS} -DNUM_REPS=${REPS} -DBATCH_SIZE=${BATCH}

test_cblas:
		$(CC) test_linear_algebra.c matrix_batch.c linear_algebra.c $(TUNE) -o test_linear.out -DTUNED -fopenmp $(OPT)  $(CBLAS_OPT) $(CBLAS_LINK) -DNUM_ELMS=${ELMS} -DNUM_MATS=${MATS} -DNUM_REPS=${REPS} -DBATCH_SIZE=${BATCH}

test_tuned:
		$(CC) test_linear_algebra.c  matrix_batch.c linear_algebra.c $(TUNE) -o test_linear.out -DTUNED -fopenmp $(OPT)  $(MKL_OPT) $(MKL_LINK) -DNUM_ELMS=${ELMS} -DNUM_MATS=${MATS} -DNUM_REPS=${REPS} -DBATCH_SIZE=${BATCH}

test_kalman: 
		$(CC) -o test_kalman.out test-kalman.c kalman_filter.c linear_algebra.c $(CFLAGS)  $(LDFLAGS)

libs:
		$(CC) kalman_filter.c -g -c
		$(CC) linear_algebra.c -g -c

clean:
		rm -f *.log *.o *.dot *.optrpt