## How to use *AutoD*

*AutoD* will be used as an API.   

### **What should users import?**  

An example is included in the `example_usage` directory. Briefly, the steps to use the library are:

1. Clone our repository.
2. Compile the OffPiste library by the configure script we provide.
```$ bash config.sh -lib -testsOFF```
3. Compile the source code that uses the `OffPiste` library by:
* Including the `OffPiste.hpp` in the source code
* Linking to the compiled `OffPiste` library using:
```
$ export LIBRARY_PATH=${REPO_ROOT}/OffPiste/install/lib
$ g++ -Wall ${SRC_FILES} -o example.o -L${LIBRARY_PATH} -lOffPiste
```

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
