# Example Usage

This folder gives an example of using the `OffPiste` library, in the file `example.cpp` and the accompanying `Makefile`.

## Steps to Run the Example Code
1. Compile the `OffPiste` library using:
```
$ cd example_usage/
$ make compile_dependencies
```
This will compile the source code for the dependency into a `.so` (Linux) / `.dylib` (Mac) dynamically linked library which is placed under `../OffPiste/install/lib`.

2. Compile the code that uses the `OffPiste` library and run it:
```
$ make run
```

## General Steps for Using the OffPiste Library

1. Compile the OffPiste Library by cloning the repo and running:
```
$ bash config.sh -lib -testsOFF
```

2. Compile the source code that uses the `OffPiste` library by:
* Including the `OffPiste.hpp` in the source code
* Linking to the compiled `OffPiste` library using:
```
$ export LIBRARY_PATH=${REPO_ROOT}/OffPiste/install/lib
$ g++ -Wall ${SRC_FILES} -o example.o -L${LIBRARY_PATH} -lOffPiste
```
