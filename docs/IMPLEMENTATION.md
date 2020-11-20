## Implementation

- **What are the core data structures?**
    The core data structure underlies our AD tool is a Directed Acyclic Graph (DAG) with multiple inputs and single output.
    e.g. f(x, y, z) = x + y^2 + z^3.  
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
        
        - Operator overloading. Support unary and binary operation:
            - Unary operators: power(^), sin, cos, tan, exp.
            - Binary operators: addition(+), subtraction(-), multiply(*), divide(/), +=, -=, *=, /=.  
            *P.S. The binary operator are **only** between `AutoDiff` object for this milestone)*

- The functions above are described in further detail via code comments in `OffPiste.cpp` and `.hpp`, as well as in the Doxygen documentation available at `docs/doxygen/html`.

- As set out in a previous milestone document, we intend to implement reverse mode and so, going forward, we will need to store a graph of operations. Our intended class structure for this remains as set out in that previous milestone document. 
    
- **What external dependencies you rely on?**
    - We do not use any external dependencies. However, we do use the c standard libraries such as `cmath` for computing the value of some functions, e.g. sin, cos, exp.
    
