## Implementation

- **What are the core data structure?**  
    The core data structure for each component of vector functions is a DAG multiple inputs and multiple outputs.
    e.g. f(x, y, z) = (x + y^2, x - z)
  
- **What classes will you implement? What method and name attributes will your classes have?**  
    There are three basic classes needed to be implement:
    - `Node`: A node of the DAG. It has the following attributes and methods:
        - `.forward()`: represent the operation of this node, including binary and unary operation, e.g. +, -, exp, sin.
        - `.backward()`: used in reverse mode when computing the derivative of each node.
        - `.value`: the value of this node.
        - `.derivative`: the derivative of this node.
        - `.parents`: a `std::vector<Node*>` containing the pointers to all parents of this node.
        - `.children`: `a std::vector<Node*>` containing the pointers to all children of this node.
    
    - `Variable`: A derived class of `Node` that represents each input.
    
    - `Graph`: A DAG that containing Nodes, with multiple inputs and multiple outputs.
        - `Graph(EXPRESSIONS)`: use `EXPRESSIONS` to initialize a DAG.
        - `.evaluate(Node &output_node)`: compute the output wrt `Node &output_node`.
        - `.forward_derivative(Node &output_node, Node &wrt)`: compute the derivative of `Node &output_node` wrt `Node &wrt`.
        - `.bfs()`: a private method that add every node in the graph and its in degree into `std::map<Node*, size_t> book_keeper`.
        - `.generate_aov_sequence`: a private method that generate an feasible AOV sequence of this DAG and store it in `std::vector<Node*> aov_sequence`
        - `.output_node_ptrs`: a `std::vector<Node*>` that stores the pointers to output nodes (top level nodes).
        - `.book_keeper`: a `std::map<Node*, size_t>` that stores pointers to each node and its the number of its children.
        - `.aov_sequence`: a `std::vector<Node*>` that stores a feasible AOV sequence of this DAG. It is obtained by invoking `.generate_aov_sequence()`.

- **What external dependencies will you rely on?**
    - cmath
    - STL
    
- **How will you deal with elementary functions like sin, sqrt, log, and exp (and all the others)?**  
    Overwrite those functions in `cmath` so that they can take `Node` as input and build graph correspondingly.
    