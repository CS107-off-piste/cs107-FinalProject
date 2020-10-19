## Implementation

- **What are the core data structure?**  
    The core data structure for each component of vector functions is a DAG multiple inputs and multiple outputs.
    e.g. f(x, y, z) = (x + y^2, x - z)
  
- **What classes will you implement? What method and name attributes will your classes have?**  
    There are three basic classes needed to be implement:
    - `Node`: A node of the DAG. It has the following attributes and methods:
        - `.value`: the value of this node.
        - `.derivative`: the derivative of this node.
        - `.parents`: a vector containing the parents of this node.
        - `.children`: a vector containing the children of this node.
        - `.forward()`: represent the operation of this node, including binary and unary operation, e.g. +, -, exp, sin.
        - `.backward()`: used in reverse mode when computing the derivative of each node.
    
    - `Variable`: A derived class of `Node` that represents each input.
    
    - `Graph`: A DAG that containing Nodes, with multiple inputs and multiple outputs.
        - `Graph(EXPRESSIONS)`: use `EXPRESSIONS` to initialize a DAG.
        - `.evaluate(Node &output_node)`: compute the output wrt `Node &output_node`.
        - `.forward_derivative(Node &output_node, Node &wrt)`: compute the derivative of `Node &output_node` wrt `Node &wrt`.

- **What external dependencies will you rely on?**
    - cmath
    - STL
    
- **How will you deal with elementary functions like sin, sqrt, log, and exp (and all the others)?**  
    Overwrite those functions in `cmath` so that they can take `Node` as input and build graph correspondingly.
    