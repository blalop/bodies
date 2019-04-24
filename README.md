# n-body

A N-Body simulation.

This repo contains my Bachelor's thesis. The aim is to implement a Barnes-Hut simulation and parallelize it.

## Dependencies

Qt 5. I'm working with 5.9.5, but it should work with 5.x. C++11 is needed.

## Instructions

```
mkdir build
cd build
qmake ..
make
./nbody < inputfile [iterations]
```