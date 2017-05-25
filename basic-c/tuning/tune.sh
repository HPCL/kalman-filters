#!/bin/bash

for d in */ ; do
    cd $d
    f=${d%/}.c
    o=${d%/}.out
    orcc $f >> $o & 
    cd ..
done
