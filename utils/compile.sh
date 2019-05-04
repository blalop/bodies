#!/usr/bin/env bash

# compile the three configurations
rm -rf bin build
for target in brute bhtree parallel; do
    qmake -config $target
    make && make clean
done
