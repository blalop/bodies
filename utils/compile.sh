#!/usr/bin/env bash

# compile the three configurations
for target in brute bhtree parallel; do
    rm -rf build
    qmake -config $target
    make && make clean
done
#rm -rf build