#!/bin/bash

cd correct/
orcc correct.c >> correct.out
cd ../predict/
orcc predict.c >> predict.out
cd ..

