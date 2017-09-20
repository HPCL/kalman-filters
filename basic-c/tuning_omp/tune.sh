#!/bin/bash

for d in */ ; do
    cd $d
    echo $d
    f=${d%/}.c
    o=${d%/}.out
    # orcc --validate $f >> $o &
    orcc $f >> $o
    cd ..
done

