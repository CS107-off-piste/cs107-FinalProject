# cs107-FinalProject

[![Build Status](https://travis-ci.com/CS107-off-piste/cs107-FinalProject.svg?token=EpqTjCxd7qmi2ut6nRKz&branch=master)](https://travis-ci.com/CS107-off-piste/cs107-FinalProject)

[![codecov](https://codecov.io/gh/CS107-off-piste/cs107-FinalProject/branch/master/graph/badge.svg?token=ROWLO2X8Z5)](https://codecov.io/gh/CS107-off-piste/cs107-FinalProject/branch/master/)

Final Project for [CS107/AC207/CSCI E-207](https://harvard-iacs.github.io/2020-CS107/), built by group 1 ([*Off-piste*](https://en.wikipedia.org/wiki/Backcountry_skiing)), whose members are:

* Aleksander Aleksiev
* Krithika Sundararajan
* Yuxin Ye
* Zeren Long

## Source Code

A simple C++ program `hello_world.cpp` has been added to the repo, for starters. This program can be compiled with:
```
make hello
```
and executed with:
```
./hello_world.o
```
Finally, the compiled binary can be removed using:
```
make clean
```

## CI

This repository is configured to work with Travis CI. With every commit, the CI will ensure that the code can be compiled successfully, using the `gcc` compiler.

## Code Coverage

This repository is configured to work with CodeCov. With every commit, `gcov` is used to analyse what portion of code is covered and the results are provided on CodeCov.
