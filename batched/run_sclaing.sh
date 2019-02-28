#!/bin/bash

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
#     icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=500
#     # icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c batch_tuning/multiply_matrix_batch/_multiply.o -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=500 -DTUNED
#     echo
#     ./test_linear.out
#     echo
#   done
# done


# for elms in 128
# do
#   for mats in 100 500 1000 3000 5000
#   do
#     icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=10
#     # icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c batch_tuning/multiply_matrix_batch/_multiply.o -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=10 -DTUNED
#     echo
#     ./test_linear.out
#     echo
#   done
# done
 

for elms in 8 32 64 128 256
do
  for mats in 64
  do
    # icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c batch_tuning/multiply_matrix_batch/_multiply.o -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=1 -DTUNED
    icpc -g test_linear_algebra.c matrix_batch.c linear_algebra.c -o test_linear.out -fopenmp -O2  -march=native -DNUM_ELMS=$elms -DNUM_MATS=$mats -DNUM_REPS=1000
    echo
    ./test_linear.out
    echo
  done
done


