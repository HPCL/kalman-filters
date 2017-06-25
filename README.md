# kalman filters
some kalman filters

## Quick start
  * If it is a new computer go to data_generator and run 'make' to get the data files
  * go to experiments
  * use make sansa_projectile_tester
    * makes projectile_tester.out with original basic c kalman
  * use make sansa_projectile_tester_tuned
    * makes tuned_projectile_tester.out with tuned linear algebra
    * still use untuned kalman
  * for tuning go to basic-c/tuning/
    * each function has its own folder
    * tune.sh runs orio on all the functions
    * make tuned_o to put all the linear algebra stuff into .o
    * in the tuned_o target be sure to set the proper -OX
  * tuning_kalman is for tuning the kalman filters
    * but it hasn't been done yet


## TODO
  * tune kalman
  * finish tuning linear algebra
  * compiling functions separately with proper -O
  * blas

## basic-c
  * kalman filter and linear algebra
  * all pure C

## data_generator
  * stuff to make synthetic data
  * also contains the resulting data

## experiments
  * code for running tests and trying stuff out
  * in progress
  * note there are 2 x and y things
    * x and y in the Kalman filter for the state and measurement
    * x and y in tracking for horizontal and vertical
    * sorry this code is a mess

## kalman-cpp
  * a modified example kalman filter
  * includes version using Eigen library
  * also one that uses the basic-c filter

## kalman-lapack
  * incomplete
  * kalman filter written in lapack
  * intended for comparison

## simple-opencv-kalman-filter
  * example code using Opencv's kalman filter

