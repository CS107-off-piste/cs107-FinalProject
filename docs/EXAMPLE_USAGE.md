## How to use *OffPiste*

*OffPiste* will be used as an API.   

### **What should users import?**  

An example is included in the `example_usage` directory. Users can choose to compile our library from the source code and link it to their driver scripts, or use the artifacts published in Github Releases.

#### Compile OffPiste from Source Code
1. Clone this repo
2. Compile the `OffPiste` library using:
```
$ cd example_usage/
$ make compile_dependencies
```
This will compile the source code for the dependency into a `.so` (Linux) / `.dylib` (Mac) dynamically linked library which is placed under `../OffPiste/install/lib`.
3. Compile the code that uses the `OffPiste` library (as an example, `example.cpp`) and run it:
```
$ make run
```

#### Use the published Artifacts
1. Obtain the header file and compiled `.so` (Linux) / `.dylib` (Mac) from the latest [Github Release](https://github.com/CS107-off-piste/cs107-FinalProject/releases)
2. Compile the source code that uses the `OffPiste` library by:
* `#include`ing the downloaded `OffPiste.hpp` in the source code
* Linking to the compiled `OffPiste` library using:
```
$ g++ --std=c++14 -Wall ${SRC_FILES} -o example.o -L${LIBRARY_PATH} -lOffPiste
```
(with `${LIBRARY_PATH}` as the folder containing the downloaded library file, and `${SRC_FILES}` as the paths of the source files).

### **How can users instantiate AD objects?**  

The OffPiste library has an intuitive interface that is achieved by mimicking `cmath` functions and overloading operators. Sample code may be found in [example.cpp](../example_usage/example.cpp).
