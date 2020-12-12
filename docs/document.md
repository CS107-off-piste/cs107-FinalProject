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


## Implementation

### What are the core data structures?
    The core data structure for each component of vector functions is a Directed Acyclic Graph (DAG) with multiple inputs and multiple outputs.
    e.g. f(x, y, z) = (x + y^2, x - z)
  
### What classes will you implement? What method and name attributes will your classes have?
- 
    There are three basic classes needed to be implemented: `Node`, `Variable`, `Function`:
    - `Node`: A node of the computational DAG. It has the following attributes and methods:
        - `.backward()`: compute the gradients of all descendents of this node. If not zero_grad the whole computational DAG, the gradients of the descendents 
        will accumulate from their previous gradients. 
        - `._forward_func_ptr()`: represents the operation of this node, including binary and unary operation, e.g. +, -, exp, sin.
        - `._backward_func_ptr()`: represents how the gradient will pass this node in reverse mode.
        - `.val`: the value of this node.
        - `.dval`: the derivative of this node. Used ONLY in forward mode.
        - `.grad`: the gradient of this node w.r.t the node that calls `.backward()`.Used ONLY in reverse mode.
        - `._parents`: a `std::vector<Node*>` containing the pointers to all _parents of this node. A `Node` can have multiple parents.
        - `._children`: a `std::vector<Node*>` containing the pointers to all _children of this node. A `Node` has at most TWO children.
    
    - `Variable`: A derived class of `Node` that represents each input node.
    
    - `Function`: A DAG that containing Nodes, with multiple inputs and multiple outputs.
        - `Function(Input, Output)`: use `Input` and `Output` to initialize a computational DAG.
        - `.evaluate()`: evaluate computational DAG, and return values of output nodes in `std::vector<float>`.
        - `.set_seed(Vec seeds)`: set the seed for each input node in forward mode.
        - `.forward_derivative(Node &output_node, Node &wrt)`: compute the dval of `Node &output_node` wrt `Node &wrt` using forward mode.
        - `.forward_jacobian()`: compute the jacobian using forward mode and return `std::vector<std::vector<float>>`.
        - `.zero_grad()`: set `.grad` of all `Node`s in the computational DAG to 0.
        - `.backward_jabobian()`: compute the jabobian using reverse mode and return `std::vector<std::vector<float>>`.
        - `.bfs()`: a private method that add every node in the graph and its in-degree into `std::map<Node*, size_t> in_deg_book_keeper`.
        - `.generate_aov_sequence`: a private method that generate an feasible AOV sequence of this DAG and store it in `std::vector<Node*> aov_sequence`.
        - `.input_node_ptrs`: a `std::vector<Node*>` that stores the pointers to all input nodes.
        - `.output_node_ptrs`: a `std::vector<Node*>` that stores the pointers to all output nodes.
        - `.in_deg_book_keeper`: a `std::map<Node*, size_t>` with key `Node*` and value the number of the node's children.
        - `.aov_sequence`: a `std::vector<Node*>` that stores a feasible AOV sequence of this DAG. It is obtained by invoking `.generate_aov_sequence()`.
        - `.node2aov_idx`: a `std::map<Node*, size_t>` with key `Node*` and value the index of the `Node` in `.aov_sequence`.
  
    Other than classes, there are also some type definitions with namespace OP that are helpful.
    - `Expression`: An alias for `Node&`. Each `Expression` is a scalar function of vector input.
    - `Input`: An alias for `std::vector<std::reference_wrapper<Node>>`, which is a vector of input `Variable`s.
    - `output`: An alias for `std::vector<std::reference_wrapper<Node>>`, which is a vector of output `Variable`s.
    - `Vec`: An alias for `std::vector<float>`.
    - `Mat`: An alias for `std::vector<std::vector<float>>`.

### What external dependencies will you rely on?
    1. cmath
    2. STL
    
### How will you deal with elementary functions like sin, sqrt, log, and exp (and all the others)?
    Overwrite those functions in `cmath` so that they can take `Node` as input and build the graph accordingly.
    
## Extensions

### updates from Miletone2
The work done so far supports the calculation of derivatives for basic __scalar functions__ of __scalar values__, using the __Forward Mode__ of Automatic Differentiation. As an extension to this, we would like to support the following features:
* Implement support for derivatives of __vector functions__ of __vector values__ (done)
* Implement Reverse Mode of AD. Consumers of our library can then choose to use either the forward mode or the reverse mode for their operations. (done)

### new feature
#### Reverse Mode

Reverse mode is better for functions way more inputs than outputs. Reverse mode AD involves 2 passes:
* A __forward pass__ in which the function is decomposed into a set of primitive expressions
* A __reverse pass__ which takes advantage of the Chain rule for multiple variables, to calculate the derivative of each node of the computation graph, with respect to its parents.

## Future

### support sparse matrix inputs

There are many physical phenomena involving ordinary differential equations and partial differential equations. And most of them do not have an analytical solution. The most common approach is to discretize the spatial-temporal scope into finite-difference grids. And the point variables usually only tangle with its’ neighbors in the discretized equations. Considering of the number of the grid variables in a common pde problem, it is quite necessary for our package to support sparse matrix inputs and comes out with a sparse Jacobian or Hessian matrix to plug into the implicit methods.

### Support back propagation

Since our package have implemented the reverse mode for computing derivatives. It would be rather easy to wrap it up with a back propagation API. Back-propagation is the central component in neural networks, which have demonstrated it’s increasing power in many areas nowadays.

### Support vector inputs

We also want to add an additional support for vector inputs. This functionality is extremely important in inverse rendering in computer graphics. Rendering process is composed of a render tree which recursively traces the parent rays starting from eyes. Inverse graphics techniques seek to find the scene parameters given observed images, for example, the shape and texture of a face, lighting, spatially varying material properties, matching photographs of fabrics, etc. Vision as inverse graphics has a long history in both computer graphics and computer vision. Many techniques in inverse graphics utilize derivatives of the rendering process for inference.

### Support sampling function plug-in for differentials of an integral 

Another promising application is to support sampling function plug-in for differentials of an integral. Note our automatic differentiation is not capable of dealing with integrals because integrals, not like differention, do not obey the chain rule. But integrals is essential to deal with real world problem since it is almost impossible to write out explicit functions for every events. Therefore Monte Carlo method comes in as a popular helper to deal with integrals.
![importance_sampling](./assets/importance_sampling.png)
