# n-body

A N-Body simulation.

This repo contains my Bachelor's thesis. It is a n-body simulation.

It has three configurations:
* brute: brute force method
* bhtree: tree based method
* parallel: tree based method (parallel)

## Dependencies

* Qt 5.
* C++11 onwards
* Boost

On a Debian-based system, Qt 5 is under the name of `qt5-default`. Boost libraries can be found in the package `libboost-all-dev`.

## Instructions

```
qmake
make
bin/nbody model [iterations] [trace]
```