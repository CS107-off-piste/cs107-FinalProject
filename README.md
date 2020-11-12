# cs107-FinalProject

[![Build Status](https://travis-ci.com/CS107-off-piste/cs107-FinalProject.svg?token=EpqTjCxd7qmi2ut6nRKz&branch=master)](https://travis-ci.com/CS107-off-piste/cs107-FinalProject)
[![codecov](https://codecov.io/gh/CS107-off-piste/cs107-FinalProject/branch/master/graph/badge.svg?token=ROWLO2X8Z5)](https://codecov.io/gh/CS107-off-piste/cs107-FinalProject/branch/master/)

Final Project for [CS107/AC207/CSCI E-207](https://harvard-iacs.github.io/2020-CS107/), built by group 1 ([*Off-piste*](https://en.wikipedia.org/wiki/Backcountry_skiing)), whose members are:

* Aleksander Aleksiev
* Krithika Sundararajan
* Yuxin Ye
* Zeren Long

## Local Development

An overview of important local development commands is provided below. For more information, see:

```
$ ./config.sh --help
```

### Compilation

The Off Piste library can be compiled with:

```
$ ./config.sh --3pl #build 3rd party testing libraries
$ ./config.sh --library #build Off Piste library
```

### Running Tests

Tests can be run locally using the following commands.

```
$ ./config.sh
```

### Code Coverage

**TBC**.

### Clean Up

The compiled binary and test coverage output can be removed using:
```
$ ./config.sh --clean
```

## Documentation

The `docs/` folder contains information on the implementation and the mathematical concepts used.
* [Background](./docs/BACKGROUND.md)
* [Example Usage](./docs/EXAMPLE_USAGE.md)
* [Software Organization](./docs/SOFTWARE_ORGANIZATION.md)
* [Implementation](./docs/IMPLEMENTATION.md)

## Continuous Integration

This repository is configured to work with Travis CI. With every commit, the following actions are performed.
* The code is compiled using the `gcc` compiler.
* If the compilation is successful, the binary is executed and `gcov` is used to analyse what portion of code is covered. The code coverage results are provided on CodeCov.
