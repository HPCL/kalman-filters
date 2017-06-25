#!/bin/bash

for d in */ ; do
    cd $d
    f=${d%/}.c
    make
    cd ..
done

make non_tuned_o
