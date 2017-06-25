#!/bin/bash

for d in */ ; do
    cd $d
    rm -f *.log *.json *.dot *.out *.o timer_cpu.c
    cd ..
done
