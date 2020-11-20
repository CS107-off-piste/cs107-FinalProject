# cs107-FinalProject

[![Build Status](https://travis-ci.com/CS107-off-piste/cs107-FinalProject.svg?token=EpqTjCxd7qmi2ut6nRKz&branch=master)](https://travis-ci.com/CS107-off-piste/cs107-FinalProject)
[![codecov](https://codecov.io/gh/CS107-off-piste/cs107-FinalProject/branch/master/graph/badge.svg?token=ROWLO2X8Z5)](https://codecov.io/gh/CS107-off-piste/cs107-FinalProject/branch/master/)

Final Project for [CS107/AC207/CSCI E-207](https://harvard-iacs.github.io/2020-CS107/), built by group 1 ([*Off-piste*](https://en.wikipedia.org/wiki/Backcountry_skiing)), whose members are:

* Aleksander Aleksiev
* Krithika Sundararajan
* Yuxin Ye
* Zeren Long

## Local Development

The local development setup for this project is based on the skeleton project provided by Andrew Kirby [here](https://github.com/ackirby88/CS107/tree/master/skeleton-project).

An overview of important local development commands is provided below. For more information, see:

```
$ ./config.sh --help
```

### Compilation

The OffPiste library can be compiled with the following commands. By default, this compiles the library to a `.dylib` on a Mac and `.so` on other Unix systems.

```
$ ./config.sh --3pl #build 3rd party testing libraries
$ ./config.sh --library #build OffPiste library and run tests
```

The resultant library and header files can be found in `OffPiste/install/`.

### Running Tests

Tests can be run locally using the following command which will build the 3rd party libraries, the OffPiste library and run the tests.

```
$ ./config.sh
```

`./config.sh --library` will also run the tests, but will only re-compile the OffPiste library.

### Code Coverage

After the library has been built, use the following command to rebuild the OffPiste library with the coverage flags, run tests and gather the code coverage report.

```
$ ./config.sh --coverage
```

This command uses `lcov`, so will only work if `lcov` is installed on your system.

### Clean Up

The compiled binary and test coverage output can be removed using:
```
$ ./config.sh --clean
```

If you also want to clean the 3rd party libraries, use

```
$ ./config.sh --distclean
```

## Contributing to this Project

### Code Changes
You can contribute to this project by submitting a pull request. If your pull request changes any `c++` source files, please use the command

```
$ ./config.sh --format
```

to re-format the `c++` source code in the `OffPiste/` directory using `clang-format` before pushing your changes. This will ensure your files have a consistent style with the other files in this project. 

### Reporting Issues
Bugs and Feature requests may be submitted to Github Issues. For Bug Reports, please include a detailed description of the steps, the expected behavior and the actual behavior.

## Documentation

The `docs/` folder contains information on the implementation and the mathematical concepts used.
* [Background](./docs/BACKGROUND.md)
* [Example Usage](./docs/EXAMPLE_USAGE.md)
* [Software Organization](./docs/SOFTWARE_ORGANIZATION.md)
* [Implementation](./docs/IMPLEMENTATION.md)

### Source Code Documentation

The `docs/doxygen` folder includes a snapshot of the source code's documentation generated using in-line comments in the relevant source files. `docs/doxygen/index.html` can be used to launch and explore these docs.

The documentation can be manually re-generated using `./config.sh --gen-docs` if you have `doxygen` installed.

## Continuous Integration

This repository is configured to work with Travis CI. With every commit, the following actions are performed.
* The code is compiled using the `gcc` compiler, in the `linux` environment.
* If the compilation is successful, the tests are executed and `lcov` is used to analyse what portion of code is covered. The code coverage results are provided on `CodeCov`. The test results are provided on `Travis`. See the badges at the top of this `README.md` for the current status.
* Creating a tag on Github will trigger a build on TravisCI that compiles and tests the code on `linux` and `osx` environments. If successful, a Github release will be created with the compiled `.so` and `.dylib` files that can be used on Linus and Mac OS, respectively.
