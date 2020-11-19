# Example Usage

This folder gives an example of using the `OffPiste` library, in the file `example.cpp` and the accompanying `Makefile`.

## Steps
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
