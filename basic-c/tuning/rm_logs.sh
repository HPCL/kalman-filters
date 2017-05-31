#!/bin/bash

for d in */ ; do
    cd $d
    rm -f *.log
    cd ..
done
