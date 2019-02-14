#!/bin/bash

export CMD=./tuned_LA_projectile_tester.out
# CMD=./projectile_tester.out

export CALI_CONFIG_FILE=~/soft/src/Caliper/examples/configs/papi_cycles.conf

export CALI_REPORT_FILENAME=cali_tot_cyc_many.json
export CALI_PAPI_COUNTERS=PAPI_TOT_CYC
$CMD

export CALI_REPORT_FILENAME=cali_vec_dp_many.json
export CALI_PAPI_COUNTERS=PAPI_VEC_DP
$CMD

export CALI_REPORT_FILENAME=cali_dp_ops_many.json
export CALI_PAPI_COUNTERS=PAPI_DP_OPS
$CMD

export CALI_REPORT_FILENAME=cali_128_packed_ops_many.json
# note the difference from TAU counters - no PAPI_NATIVE_
export CALI_PAPI_COUNTERS=FP_ARITH:128B_PACKED_DOUBLE
$CMD


export CALI_REPORT_FILENAME=cali_256_packed_ops_many.json
# note the difference from TAU counters - no PAPI_NATIVE_
export CALI_PAPI_COUNTERS=FP_ARITH:256B_PACKED_DOUBLE
$CMD


export CALI_REPORT_FILENAME=cali_512_packed_ops_many.json
# note the difference from TAU counters - no PAPI_NATIVE_
export CALI_PAPI_COUNTERS=FP_ARITH:512B_PACKED_DOUBLE
$CMD


export CALI_REPORT_FILENAME=cali_scalar_double_many.json
export CALI_PAPI_COUNTERS=FP_ARITH:SCALAR_DOUBLE
$CMD


export CALI_REPORT_FILENAME=cali_scalar_single_many.json
export CALI_PAPI_COUNTERS=FP_ARITH:SCALAR_SINGLE
$CMD

