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
$ g++ -Wall ${SRC_FILES} -o example.o -L${LIBRARY_PATH} -lOffPiste
```
(with `${LIBRARY_PATH}` as the folder containing the downloaded library file, and `${SRC_FILES}` as the paths of the source files).


### **How can users instantiate AD objects?**  

#### For scalar function
```
#include<iostream>
#include "OffPiste.hpp"

typedef AutoDiff AD;
using namespace AutoDiff;

int main(){
   
    // some test values
    double value1 = 1.2; 
    double value2 = 3.4;
    double seed1 = 1.0;
    double seed2 = 1.0;

    // construct an AD object 
    // AD is just a shortcut for AutoDiff<double>
    AD x(value1,seed1);
    AD y(value2,seed2);

    // print initial value and seed
    std::cout << "Initial x, y value: " << x.val() << ", "<< y.val() << "\n"; 
    std::cout << "Initial x, y deriv: " << x.dval() << ", "<< y.dval() << "\n";

    // perform the operation z = e^(sin(x + y))
    AD z = exp(sin(x+y));
    std::cout << "Z value, derivative: " << z.val() << ", "<< z.dval() << "\n"; 
    
}
```

#### For Vector functions (TBD)

This feature is a work in progress and will be documented once complete.
