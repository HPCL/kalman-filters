#!/bin/bash



MKL_LINK='-L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl'
MKL_OPT='-DMKL_ILP64 -I${MKLROOT}/include'

CBLAS_LINK='-L/home/users/gravelle/soft/OpenBLAS/lib -lopenblas -lpthread'
CBLAS_OPT='-L/home/users/gravelle/soft/OpenBLAS/include'

DIR=cali_tcm_scaling 
mkdir $DIR
export CMD=./test_linear.out
export CALI_CONFIG_FILE=~/soft/src/Caliper/examples/configs/papi_cycles.conf
# export CALI_PAPI_COUNTERS=FP_ARITH:512B_PACKED_DOUBLE
export CALI_PAPI_COUNTERS=PAPI_L2_TCM

export OMP_NUM_THREADS=4

bats=256
# for elms in 10 15 20
for elms in 5 10 15 20 25
do
  # for bats in 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 524288
  for bats in 16
  do
    export CALI_REPORT_FILENAME=$DIR/cali_simd512_many_$elms-$bats.json
    make test_linear MATS=524288 ELMS=$elms REPS=3 BATCH=$bats
    echo
    ./test_linear.out
    echo
  done
done
 

# DIR=cali_tcm_scaling
# mkdir $DIR
# export CMD=./test_linear.out
# export CALI_CONFIG_FILE=~/soft/src/Caliper/examples/configs/papi_cycles.conf
# export CALI_PAPI_COUNTERS=PAPI_L2_TCM
# # for elms in 10 15 20
# for elms in 5 10 15 20 25
# do
#   # for bats in 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 16777216
#   for bats in 8 16777216
#   do
#     export CALI_REPORT_FILENAME=$DIR/cali_tcm_many_$elms-$bats.json
#     make test_linear MATS=16777216 ELMS=$elms REPS=10 BATCH=$bats
#     echo
#     ./test_linear.out
#     echo
#   done
# done
 


# DIR=cali_scalar_scaling
# mkdir $DIR
# export CMD=./test_linear.out
# export CALI_CONFIG_FILE=~/soft/src/Caliper/examples/configs/papi_cycles.conf
# export CALI_PAPI_COUNTERS=FP_ARITH:SCALAR_DOUBLE
# # for elms in 10 15 20
# for elms in 5 10 15 20 25
# do
#   # for bats in 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 16777216
#   for bats in 8 16777216
#   do
#     export CALI_REPORT_FILENAME=$DIR/cali_scalar_many_$elms-$bats.json
#     make test_linear MATS=16777216 ELMS=$elms REPS=10 BATCH=$bats
#     echo
#     ./test_linear.out
#     echo
#   done
# done
 


# for elms in 128
# do
#   for mats in 3000 4000 5000
#   do
#     icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c batch_tuning/multiply_matrix_batch/_multiply.o -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DTUNED
#     echo
#     ./test_linear.out
#     echo
#   done
# done

# for elms in 256
# do
#   for mats in 100 500 1000 3000 5000
#   do
#     icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c batch_tuning/multiply_matrix_batch/_multiply.o -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DTUNED
#     echo
#     ./test_linear.out
#     echo
#   done
# done

# for elms in 8 32 64
# do
#   for mats in 100 500 1000 3000 5000
#   do
#     # icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c  -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=500   $MKL_OPT $MKL_LINK 
#     icpc -g -static test_linear_algebra.c matrix_batch.c linear_algebra.c batch_tuning/multiply_matrix_batch/_multiply.o -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=500 -DTUNED   $CBLAS_OPT $CBLAS_LINK
#     echo
#     ./test_linear.out
#     echo
#   done
# done


# for elms in 128
# do
#   for mats in 100 500 1000 3000 5000
#   do
#     #icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=10  $MKL_OPT $MKL_LINK 
#     icpc -g -static test_linear_algebra.c matrix_batch.c linear_algebra.c batch_tuning/multiply_matrix_batch/_multiply.o -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=10 -DTUNED  $CBLAS_OPT $CBLAS_LINK
#     echo
#     ./test_linear.out
#     echo
#   done
# done


# for elms in 256
# do
#   for mats in 100 500 1000 3000 5000
#   do
#     # icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=1  $MKL_OPT $MKL_LINK 
#      icpc -g -static test_linear_algebra.c matrix_batch.c linear_algebra.c batch_tuning/multiply_matrix_batch/_multiply.o -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=1 -DTUNED   $CBLAS_OPT $CBLAS_LINK
#     echo
#     ./test_linear.out
#     echo
#   done
# done
 

# for elms in 8 32 64 128 256
# do
#   for mats in 64
#   do
#     # icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=1000  $MKL_OPT $MKL_LINK 
#     icpc -g -static test_linear_algebra.c matrix_batch.c linear_algebra.c batch_tuning/multiply_matrix_batch/_multiply.o -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=1000 -DTUNED  $CBLAS_OPT $CBLAS_LINK
#     echo
#     ./test_linear.out
#     echo
#   done
# done
 



