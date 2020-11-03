# Milestone 1

## Background

Differentiation has its applications everywhere from finding zeros of functions to the back propagation algorithm in Deep Neural Networks. In this repository, we implement a library that uses Automatic Differentiation to find the derivatives of real and vector valued functions.

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
* A `forward pass` in which the function is decomposed into a set of primitive expressions
* A `reverse pass` which takes advantage of the Chain rule for multiple variables, to calculate the derivative of each node of the computation graph, with respect to its parents.
![chain rule](./assets/chain_rule.png)

<hr/>

## How to use *AutoD*

### **How do you envision that a user will interact with your package?**  
*AutoD* will be used as an API.   

### **What should they import?**  
They should download *AutoD.lib* , set the search directory and include the header file `#include<AutoD.h>`.  

### **How can they instantiate AD objects?**  
#### For single-variable function
```
#include<iostream>
#include<AutoD.h>
using namespace AutoD;

int main(){
    
    Variable x = 2.0;
    Function f = func(exp(cos(x + 3) + pow(x, 4)) + 1);
    std::cout<<"f = "<<f.evaluate()<<std::endl;
    std::cout<<"df/dx = "<<f.forward_derivative(x)<<std::endl;
    
}
```
#### For Multi-variable function
```
#include<iostream>
#include<AutoD.h>
using namespace AutoD;

int main(){
    
    Variable x = 2.0, y = 3.0, z = 4.0;
    Function u = func(exp(cos(x + 3) + pow(y, 4)) + z);
    std::cout<<"f = "<<f.evaluate()<<std::endl;
    std::cout<<"df/dx = "<<f.forward_derivative(x)<<std::endl;
    std::cout<<"df/dy = "<<f.forward_derivative(y)<<std::endl;
    std::cout<<"df/dz = "<<f.forward_derivative(z)<<std::endl;
    std::cout<<"Gradient of f"<<f.forward_gradient()<<std::endl;  //gradient of f: (dfdx, dfdy, dfdz)
    
}
```
#### For Vector function
```
#include<iostream>
#include<AutoD.h>
using namespace AutoD;

int main(){
    
    Variable x = 2.0, y = 3.0, z = 4.0;
    Expression u = exp(cos(x + 3) + pow(y, 4)) + z;
    Expression v = x + y;
    
    Function F = func(u,v) //F is the vector function.
    
    std::cout<<"F = "<<F.evaluate()<<std::endl;
    std::cout<<"dF/dx = "<<F.forward_derivative(x)<<std::endl;
    std::cout<<"dF/dy = "<<F.forward_derivative(y)<<std::endl;
    std::cout<<"dF/dz = "<<F.forward_derivative(z)<<std::endl;
    std::cout<<"Jacobian of F"<<F.Jacobian(x,y,z)<<std::endl;
}   
```

<hr/>

## Software Organisation

### What will the directory structure look like?

The project's main directories will be:

* `src/` which will contain our C++ source files,
* `test/` which will contain tests, and
* `docs/` which will contain files such as this one, which relate to documenting our development process. Documentation will also be stored here.

### What external modules do you plan on including? What is their basic functionality?

At this stage, we do not intend to rely on any external modules. However, we will use standard C++ headers, such as `<cmath>` and the various STL classes for `strings` and I/O.

### Where will your test suite live? Will you use TravisCI? CodeCov?

As described above, we intend to have a separate `test/` directory in which test files will be placed. Our intention is to use [Google's C++ testing library](https://github.com/google/googletest) to perform testing in this directory. This will include both "unit" tests to test specific functions, and broader "functional" tests to check that our library is performing as expected on tasks such as computing the derivative and value from a user-inputted function. We will also look into using their [benchmarking library](https://github.com/google/benchmark) to provide performance reports, so that we can notice if a commit has caused performance of core functions (such as building a computational graph or calculating its derivative and value using the reverse mode) to deteriorate.

We have already set up TravisCI and CodeCov as part of the previous Milestone. We will update our `travis.yml` and `Makefile` to automate the running of tests following pushes to the project repository.

### How will you distribute your package (e.g. PyPI)?

Unfortunately, C++ does not have a well-established and widely-used package index like PyPI. However, we intend to investigate, and consider distributing the package through [Conan](https://conan.io/), a C++ package manager.

We will also make a pre-built dynamically linked library version of project available in the repository. 

### How will you package your software?

In the root directory of this repository, we have set up a `Makefile` for compiling and testing our source code. We will continue to augment this file as the project progresses.

### Other considerations?

We plan to use Doxygen to generate documentation from inline comments in our source code.

<hr/>

## Implementation

- **What are the core data structures?**
    The core data structure for each component of vector functions is a Directed Acyclic Graph (DAG) with multiple inputs and multiple outputs.

    In the DAG, each node represents one of the operations in the computational graph of our function. We store our operations in this DAG so that we can traverse the nodes of the DAG (in reverse) when computing the reverse mode.

    e.g. f(x, y, z) = (x + y^2, x - z)
  
- **What classes will you implement? What method and name attributes will your classes have?**  
    There are three basic classes needed to be implemented: `Node`, `Variable`, `Function`:
    - `Node`: A node of the DAG. It has the following attributes and methods:
        - `.forward()`: represents the operation of this node, including binary and unary operation, e.g. +, -, exp, sin.
        - `.backward()`: used in reverse mode when computing the derivative of each node.
        - `.value`: the value of this node.
        - `.derivative`: the derivative of this node.
        - `.parents`: a `std::vector<Node*>` containing the pointers to all parents of this node.
        - `.children`: `a std::vector<Node*>` containing the pointers to all children of this node.
    
    - `Variable`: A derived class of `Node` that represents an input node.
    
    - `Function`: A DAG that contains Nodes, with multiple inputs and multiple outputs.
        - `Function(EXPRESSIONS)`: use `EXPRESSIONS` to initialize a DAG. 
        - `.evaluate(Node &output_node)`: compute the output of `Node &output_node`.
        - `.evaluate()`: compute the output with respect to all output nodes, and return `std::vector<float>`.
        - `.set_seed(std::vector<float> p)`: set the seed *p* when taking directional derivative.
        - `.forward_derivative(Node &output_node, Node &wrt)`: compute the derivative of `Node &output_node` with respect to `Node &wrt`.
        - `.jacobian()`: compute the jacobian of vector function of vector input represented by this graph, and return `std::vector<std::vector<float>>`.
        - `.bfs()`: a private method that adds every node in the graph and its in degree into a `std::map<Node*, size_t> book_keeper`.
        - `.generate_aov_sequence()`: a private method that generates a feasible AOV sequence of this DAG and store it in `std::vector<Node*> aov_sequence`
        - `.output_node_ptrs`: a `std::vector<Node*>` that stores the pointers to output nodes (top level nodes).
        - `.book_keeper`: a `std::map<Node*, size_t>` that stores pointers to each node and its number of children.
        - `.aov_sequence`: a `std::vector<Node*>` that stores a feasible AOV sequence of this DAG. It is obtained by invoking `.generate_aov_sequence()`.
  
    Other than classes, there are also some definitions of macros that are helpful.
    - `EXPRESSION`: A macro for `Node&`.

    - `EXPRESSIONS`: A macro for `std::vector<std::reference_wrapper<Node>>`.

- **What external dependencies will you rely on?**
    - `cmath`
    - `STL`
    
- **How will you deal with elementary functions like sin, sqrt, log, and exp (and all the others)?**  
    Overload the relevant functions in `cmath` so that they can take `Nodes` as input and return new `Nodes`, so that we can build the graph accordingly.

# Feedback

- **Feedback 1: Can we hear more about the reasoning behind choosing DAG as your core data structure? Is it necessary because of the reverse mode feature?** 
    - We would not need a permanent data structure if we were only implementing the forward mode. However, as was discussed in lecture, since we intend to implement reverse mode, we need some data structure to store our operations. 
    - This is because, in forward mode, we only make one "pass" through the function, computing both the value and derivative of the function after each operation. As a result, we would not need to keep an internal record of values / derivatives from earlier operations, since we do not return to them after they are computed. 
    - In contrast, for the reverse mode, after completing the forward pass to calculate the each operation's *values*, we then need to complete the reverse pass to calculate those operations' *derivatives*. We can only "go back" through our operations from the forward pass if we have kept a navigable record of the operations completed in the forward pass... so, we need some data structure to store this record.  
    - It is not strictly necessary that data structure be a DAG. We could, for example, have represented our `Function` as a list or tree of operations. But we felt that: a) a DAG would allow us to represent multiple inputs / multiple outputs in a cleaner way than, for example, a simple list of operations, and b) a DAG has the additional benefit of lining up neatly with the "computational graph" representation of automatic differention that we have seen in lecture. 
- **Feedback 2: Solid plan for unit testing. What can we expect to see functionality-wise and performance-wise?** 
    - As described in our updated testing section, we expect that our `tests/` directory will include functional tests to check that our library is correctly calculating values on user-inputted functions. At this stage, we also intend to include benchmarking tests in this to check if the performance of key operations has deteriorated as a result of a commit.