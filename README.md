# n-body

A N-Body simulation.

This repo contains my Bachelor's thesis.

It has three configurations:
* brute: brute force method
* bhtree: tree based method
* parallel: tree based method (parallel)

## Inputs

Input must come in a file format, in which the first line indicates the number of bodies and the second the radius of the universe.

From the third line, each line represents a body, with the parameters as follows:

```
mass posx posy velx vly
```

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