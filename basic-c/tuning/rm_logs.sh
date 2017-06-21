#!/bin/bash

for d in */ ; do
    cd $d
    rm -f *.log *.json *.dot *.out *.o _* timer_cpu.c
    cd ..
done
