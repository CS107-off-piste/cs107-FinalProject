## How to use *AutoD*

### **How do you envision that a user will interact with your package?**  
*AutoD* will be used as an API.   

### **What should they import?**  

An example usage is included in the example_usage directory.
1. Clone our repository.
2. Compile the OffPiste Library by the configure script we provide.

``` $ bash config.sh -lib -testsOFF```
3. Compile the source code that uses the `OffPiste` library by:
* Including the `OffPiste.hpp` in the source code
* Linking to the compiled `OffPiste` library using:
```
$ export LIBRARY_PATH=${REPO_ROOT}/OffPiste/install/lib
$ g++ -Wall ${SRC_FILES} -o example.o -L${LIBRARY_PATH} -lOffPiste
```


### **How can they instantiate AD objects?**  
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

#### For Vector function (unavailable now)
```
#include<iostream>
#include "OffPiste.hpp"

typedef AutoDiff AD;
using namespace AutoDiff;

int main(){
    
    / some test values
    double value1 = 1.2; 
    double value2 = 3.4;
    double seed1 = 1.0;
    double seed2 = 1.0;

    // construct an AD object 
    // AD is just a shortcut for AutoDiff<double>
    AD x(value1,seed1);
    AD y(value2,seed2);

    // perform the operation z = e^(sin(x + y))
    Func F = Func(exp(sin(x+y)),x^y+3);
    
    std::cout<<"F = "<<F.evaluate()<<std::endl;
    std::cout<<"dF/dx = "<<F.forward_derivative(x)<<std::endl;
    std::cout<<"dF/dy = "<<F.forward_derivative(y)<<std::endl;
    std::cout<<"dF/dz = "<<F.forward_derivative(z)<<std::endl;
    std::cout<<"Jacobian of F"<<F.Jacobian(x,y,z)<<std::endl;
}   
```
