## Implementation

- **What are the core data structures?**
    The core data structure for each component of vector functions is a Directed Acyclic Graph (DAG) with multiple inputs and multiple outputs.

    In the DAG, each node represents one of the operations in the computational graph of our function. We store our operations in this DAG so that we can traverse the nodes of the DAG (in reverse) when computing the reverse mode.

    e.g. f(x, y, z) = (x + y^2, x - z)

- **What classes will you implement? What method and name attributes will your classes have?**  
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

    The classes `UnaryOperator` and `BinaryOperator` have been added to assist in operator overloading. And the classes `ForwardFunctions` and `BackwardFunctions` implement the core logic for the unary and binary functions.

    Other than classes, there are also some type definitions with namespace OP that are helpful.
    - `Expression`: An alias for `Node&`. Each `Expression` is a scalar function of vector input.
    - `Input`: An alias for `std::vector<std::reference_wrapper<Node>>`, which is a vector of input `Variable`s.
    - `output`: An alias for `std::vector<std::reference_wrapper<Node>>`, which is a vector of output `Variable`s.
    - `Vec`: An alias for `std::vector<float>`.
    - `Mat`: An alias for `std::vector<std::vector<float>>`.
