## Implementation

- **What are the core data structures?**
    The core data structure for each component of vector functions is a Directed Acyclic Graph (DAG) with multiple inputs and multiple outputs.
    e.g. f(x, y, z) = (x + y^2, x - z)
  
- **What classes will you implement? What method and name attributes will your classes have?**  
    There are three basic classes needed to be implemented: `Node`, `Variable`, `Function`:
    - `Node`: A node of the DAG. It has the following attributes and methods:
        - `.forward()`: represents the operation of this node, including binary and unary operation, e.g. +, -, exp, sin.
        - `.backward()`: used in reverse mode when computing the dval of each node.
        - `.val`: the value of this node.
        - `.dval`: the derivative of this node.
        - `.parents`: a `std::vector<Node*>` containing the pointers to all parents of this node.
        - `.children`: a `std::vector<Node*>` containing the pointers to all children of this node. At most TWO children of each `Node`.
    
    - `Variable`: A derived class of `Node` that represents each input.
    
    - `Function`: A DAG that containing Nodes, with multiple inputs and multiple outputs.
        - `Function(EXPRESSIONS)`: use `EXPRESSIONS` to initialize a DAG.
        - `.evaluate(Node &output_node)`: compute the output wrt `Node &output_node`.
        - `.evaluate()`: compute the output wrt all output nodes, and return `std::vector<float>`.
        - `.set_seed()`: set the seed *p* when taking directional dval.
        - `.forward_derivative(Node &output_node, Node &wrt)`: compute the dval of `Node &output_node` wrt `Node &wrt` using forward mode.
        - `.forward_jacobian()`: compute the jacobian using forward mode and return `std::vector<std::vector<float>>`.
        - `.bfs()`: a private method that add every node in the graph and its in degree into `std::map<Node*, size_t> in_deg_book_keeper`.
        - `.generate_aov_sequence`: a private method that generate an feasible AOV sequence of this DAG and store it in `std::vector<Node*> aov_sequence`
        - `.output_node_ptrs`: a `std::vector<Node*>` that stores the pointers to output nodes (top level nodes).
        - `.in_deg_book_keeper`: a `std::map<Node*, size_t>` that stores pointer to each node and the number of the node's children.
        - `.aov_sequence`: a `std::vector<Node*>` that stores a feasible AOV sequence of this DAG. It is obtained by invoking `.generate_aov_sequence()`.
  
    Other than classes, there are also some definitions of macro that are helpful.
    - `EXPRESSION`: A macro for `Node&`. Each `EXPRESSION` is a scalar function of vector input.
    - `INPUTS`: A macro for `std::vector<std::reference_wrapper<Node>>`, which is a combination of input symbols.
    - `OUPUTS`: A macro for `std::vector<std::reference_wrapper<Node>>`, which is a combination of output symbols.

- **What external dependencies will you rely on?**
    - cmath
    - STL
    
- **How will you deal with elementary functions like sin, sqrt, log, and exp (and all the others)?**  
    Overwrite those functions in `cmath` so that they can take `Node` as input and build the graph accordingly.
