# basic-c
C linear algebra and kalman filter designed for autotuning

## Build
  * hardhat recommended
  * to build tester for kalman filter run 'make test_kalman'
    * use 'make test_kalman_db' to include debugger stuff
  * to build tester for linear algebra run 'make test_linear'
  * for both testers edit the c ffile to choose the desired tests
    * simply comment/ uncomment the functions in the main


## Autotuning
  * this can be done in the tuning directory
  * non_tuned.c contains the functions that are not intended for auto tuning
  * each tunable function has a separate directory with the function name as the dir name
  * tuning of a functions can be performed by runnning 'sh tune.sh'
  * the makefile will build the tests in .. based on the files in the tuning directories
    * use 'make test_linear'
    * or 'make test_tuned_linear'
    * these utilize the functions in the tuning dirs rather than the regular file
  * The python file merge_functions can be used to combine the separate files into one larger C file