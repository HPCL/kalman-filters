#!/bin/bash

elms='8 32 64 128 256'
mats=1000
reps=900

export CMD=./test_linear.out

export CALI_CONFIG_FILE=~/soft/src/Caliper/examples/configs/papi_cycles.conf

for e in $elms
do
  make test_tuned MATS=$mats ELMS=$e REPS=$reps

  export CALI_REPORT_FILENAME=cali_tot_cyc_many_$e.json
  export CALI_PAPI_COUNTERS=PAPI_TOT_CYC
  $CMD

  export CALI_REPORT_FILENAME=cali_lst_ins_many_$e.json
  export CALI_PAPI_COUNTERS=PAPI_LST_INS
  $CMD

  export CALI_REPORT_FILENAME=cali_l1_tcm_many_$e.json
  export CALI_PAPI_COUNTERS=PAPI_L1_TCM
  $CMD

  export CALI_REPORT_FILENAME=cali_l2_tca_many_$e.json
  export CALI_PAPI_COUNTERS=PAPI_L2_TCA
  $CMD

  export CALI_REPORT_FILENAME=cali_l2_tcm_many_$e.json
  export CALI_PAPI_COUNTERS=PAPI_L2_TCM
  $CMD

  export CALI_REPORT_FILENAME=cali_128_packed_ops_many_$e.json
  # note the difference from TAU counters - no PAPI_NATIVE_
  export CALI_PAPI_COUNTERS=FP_ARITH:128B_PACKED_DOUBLE
  $CMD

  export CALI_REPORT_FILENAME=cali_256_packed_ops_many_$e.json
  # note the difference from TAU counters - no PAPI_NATIVE_
  export CALI_PAPI_COUNTERS=FP_ARITH:256B_PACKED_DOUBLE
  $CMD

  export CALI_REPORT_FILENAME=cali_512_packed_ops_many_$e.json
  # note the difference from TAU counters - no PAPI_NATIVE_
  export CALI_PAPI_COUNTERS=FP_ARITH:512B_PACKED_DOUBLE
  $CMD

  export CALI_REPORT_FILENAME=cali_scalar_double_many_$e.json
  export CALI_PAPI_COUNTERS=FP_ARITH:SCALAR_DOUBLE
  $CMD

  export CALI_REPORT_FILENAME=cali_scalar_single_many_$e.json
  export CALI_PAPI_COUNTERS=FP_ARITH:SCALAR_SINGLE
  $CMD

  if [[ "$reps" = 900 ]]; then
    reps=300
  elif [[ "$reps" = 300 ]]; then
    reps=100
  elif [[ "$reps" = 100 ]]; then
    reps=10
  elif [[ "$reps" = 10 ]]; then
    reps=1
  fi


done

