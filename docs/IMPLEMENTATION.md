## Implementation

- **What are the core data structures?**
    The core data structure for each component of vector functions will be a Directed Acyclic Graph (DAG) with multiple inputs and multiple outputs.
    e.g. f(x, y, z) = (x + y^2, x - z)
  
- **What classes will you implement? What method and name attributes will your classes have?**  
    The core class for milestone 2 is `AutoDiff`:
    - `private` member:
        - `T v`: The value of this node
        - `T dv`: The derivative of this node
        
    - `public` member:
        - `AutoDiff()`: Default constructor
        - `AutoDiff(T val, T dval=1.0)`: Contructor with `v` and `dv`
        - `T val()`: Getter function of `v`
        - `T dval()`: Getter function of `dv`
        - `void setval(T val)`: Setter function of `v`
        - `void setval(T dval)`: Setter function of `dv`
        
        - Operator overloading. Support unary and binary operation:
            - Unary operators: power(^), sin, cos, tan, exp, +=, -=, *=, /=.
            - Binary operators: addition(+), subtraction(-), multiply(*), divide(/).  
            *P.S. The binary operator are **only** between `AutoDiff` object for this milestone)*
    
- **What external dependencies you rely on?**
    - cmath: For computing the value of some functions, e.g. sin, cos, exp.
    
