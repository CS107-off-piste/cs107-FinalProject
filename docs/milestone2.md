# Milestone 2

## Introduction

Differentiation has its applications everywhere. Some examples are:
* Finding zeros of functions - many problems in Engineering and Science require determining the maximum and minimum values such as the amount of material required in the construction industry, profit and loss calculation, etc.
* Modelling the behaviour of moving objects
* The Back propagation algorithm in Deep Neural Networks

In this repository, we implement a library that uses __Automatic Differentiation__ to find the derivatives of real and vector valued functions.

<hr/>

## Background

### Why Automatic Differentiation

The other prominent choices for implementing differentiation are __Symbolic Differentiation__ and __Finite Difference__. However, both methods have their drawbacks.
* __Symbolic Differentiation__ - This involves breaking down a given expression into subsequently simpler expressions and we are able to achieve machine precision. However, in doing so, this method tends to be slow and expensive to evaluate.
* __Finite Difference__ - Relies on the Taylor Series expansion and is very fast to evaluate. However, it suffers from poor accuracy, owing to a difficulty in selecting an appropriate value for h, since very small h values run up against floating-point imprecision:
![finite difference](./assets/finite_difference.png)

Automatic Differentiation overcomes both these limitations.

### How it Works

Automatic Differentiation is a set of techniques that allow us to efficiently compute derivatives of functions that are implemented as programs. It is able to provide derivatives with machine precision, with almost the same time as it takes to evaluate the function itself. It does so by taking advantage of an important trait of __Dual Numbers__.

#### Dual Numbers

These are numbers of the form <i>a + bε</i>, where ε<sup>2</sup> = 0. Because of this property, applying the Taylor Series expansion to a function about a dual number will result in: f(a + ε) = f(a) + εf'(a).

#### AD Modes

Automatic Differentiation is implemented in 2 flavors.

##### Forward Mode

In this mode, the function and the derivative are evaluated with respect to each input variable. The derivative is computed along with the value of the function about the given input and there is no memory overhead. For the vector valued function <i>f : R<sup>n</sup> → R<sup>m</sup></i>, the derivative of each output with respect to each input is represented using a Jacobian Matrix.
![jacobian matrix](./assets/jacobian_matrix.png)

The forward mode is more suitable for functions where `m >> n`.

##### Reverse Mode

This mode, on the other hand, is better for functions with `n >> m`. Reverse mode AD involves 2 passes:
* A __forward pass__ in which the function is decomposed into a set of primitive expressions
* A __reverse pass__ which takes advantage of the Chain rule for multiple variables, to calculate the derivative of each node of the computation graph, with respect to its parents.
![chain rule](./assets/chain_rule.png)

<hr/>

## How to use *OffPiste*

*OffPiste* will be used as an API.   

### **What should users import?**  

An example is included in the `example_usage` directory. Briefly, the steps to use the library are:

1. Clone our repository.
2. Compile the OffPiste library by the configure script we provide in the project's root directory:
```$ bash config.sh -lib -testsOFF```
3. Compile the source code that uses the `OffPiste` library by:
* `#include`ing the `OffPiste.hpp` in the source code
* Linking to the compiled `OffPiste` library using:
```
$ export LIBRARY_PATH=${REPO_ROOT}/OffPiste/install/lib
$ g++ -Wall ${SRC_FILES} -o example.o -L${LIBRARY_PATH} -lOffPiste
```

(With `${REPO_ROOT}` as the folder this folder you cloned the repository into, and `${SRC_FILES}` as location of your source files).

### **How can users instantiate AD objects?**  

#### For scalar function
```c++
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
    // AD is just a shortcut for AutoDiff
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

<hr/>

## Software Organisation

### What will the directory structure look like?

The project's main directories are:

* `OffPiste/` which contains the C++ source files, header files, and tests for the core automatic differentiation library.
    * `OffPiste/core/src` contains the source code for OffPiste library
    * `OffPiste/core/tests` contains unit and functional tests for the OffPiste library 
    * `OffPiste/include` contains the header files for the OffPiste library
    * `OffPiste/coverage` contains information relating to the code coverage of the unit and functional tests
    * `OffPiste/install` contains the compiled `.so` library. 
* `docs/` which contains files such as this one, documenting the library and development process. 
    * `docs/doxygen` contains html documentation for the `AutoDiff` library's functions.
* `example_usage` contains an example project showing how you can use the `OffPiste` library
* `3PL` contains 3rd party components. At present, this is just Google test.

### What are the basic modules?

The core module is implemented in `OffPiste/core/src`. This is where the source code for the automatic differentiation library is held. The header file for this source code is in `Offpiste/include`. This header file also includes the in-line documentation for each function.

The root directory has a `./config.sh` file. This is a shell script that reads in a user's command and executes actions (such as compiling the library, generating documentation, or generating coverage information). Depending on the arguments passed to it, `./config.sh` calls `OffPiste/config.sh`, `OffPiste/coverage.sh`, and / or `CMake`.

`C++` compilation is handled through `CMake`, using the `CMakeLists.txt` files in `OffPiste/` and its subdirectories. 

### Where do tests live?

As described above, tests for each operation supported by the library are located in `OffPiste/core/tests`.

As described in the `README.md`, tests are run with the command 

```bash
$ ./config.sh --clean # clean up, if needed
# $ ./config.sh --3pl # compile Google Test if needed
$ ./config.sh --library
```

which will re-compile the source code and run the test suite. 

### How can a person install your library?

A user can install our library by cloning the repository from github and running

```
./config.sh
```

to compile the library. This will produce a `.so` (or `.dylib` on a Mac) and `.h` file in `OffPiste/install`. These do not rely on any external components, so the user can use these as described above in the section above titled "How to use OffPiste".  

<hr/>

## Implementation

- **What are the core data structures?**
    The core data structure that will underly our AD tool is a Directed Acyclic Graph (DAG) with multiple inputs and single output.
    e.g. `f(x, y, z) = x + y^2 + z^3`.  
    By invoking a unary operation on a node, a parent node of the previous node is constructed whose value and derivative is set according to the unary operation.
    By invoking a binary operation between two nodes, a parent node of two previous nodes is constructed whose value and derivative is set according to the binary operation.
  
- **What classes will you implement? What method and name attributes will your classes have?**  
    The core class for milestone 2 is `AutoDiff`:
    - `private` members:
        - `T v`: The value of this node
        - `T dv`: The derivative of this node
        
    - `public` members:
        - `AutoDiff()`: Default constructor
        - `AutoDiff(T val, T dval=1.0)`: Contructor with fixed initial `v` and `dv`
        - `T val()`: Getter function of `v`
        - `T dval()`: Getter function of `dv`
        - `void setval(T val)`: Setter function of `v`
        - `void setval(T dval)`: Setter function of `dv`
        
        - Operator overloading. Support unary and binary operations on `AutoDiff` objects:
            - Unary operators: power(^), sin, cos, tan, exp.
            - Binary operators: addition(+), subtraction(-), multiply(*), divide(/), +=, -=, *=, /=.  
            *P.S. The binary operator are **only** between `AutoDiff` object for this milestone)*

- The functions above are described in further detail via code comments in `OffPiste.cpp` and `.hpp`, as well as in the Doxygen documentation available at `docs/doxygen/html`. An example of using the autodiff operators is included in `../example_usage`.

- As set out in a previous milestone document, we intend to implement reverse mode and so, going forward, we will need to store a graph of operations. Our intended class structure for this remains as set out in that previous milestone document. 
    
- **What external dependencies you rely on?**
    - We do not use any external dependencies in our source code. However, we do use the c standard libraries such as `cmath` for computing the value of some functions, e.g. sin, cos, exp. 
    - We use some external dependencies outside of our `c++` source code, such as `doxygen` for documentation generation, and `clang-format` for code formatting.

## Future Features

The work done so far supports the calculation of derivatives for basic __scalar functions__ of __scalar values__, using the __Forward Mode__ of Automatic Differentiation. As an extension to this, we would like to support the following features:
* Implement support for derivatives of __vector functions__ of __vector values__
* Implement Reverse Mode of AD. Consumers of our library can then choose to use either the forward mode or the reverse mode for their operations.
