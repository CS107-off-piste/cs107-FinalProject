#ifndef CS107_FINALPROJECT_NODE_HPP
#define CS107_FINALPROJECT_NODE_HPP

#include <cmath>
#include <vector>

namespace OP {

/**
* Check if two numbers are equal.
* @param a The first number to check
* @param b The number to compare against
* @returns true if the two numbers are equal, false otherwise.
*/
static bool equal(double a, double b) {
  if (std::abs(a - b) < 1e-15) return true;
  return false;
}

class Function;

/**
* A Node represents a node in the computational graph.
*/
class Node {
 public:
  /** 
  * Construct a Node with the provided initial values.
  * @param val The initial value of this Node.
  * @param dval The initial derivative value of this Node.
  * @param grad The initial gradient of this Node.
  */ 
  Node(float val = 0.f, float dval = 0.f, float grad = 0.f)
      : val(val), dval(dval), grad(grad){}; 

  /**
  * Compute gradient of this output-node using reverse-mode
  * This traverses the graph all the way back to the Input Node, 
  * updating gradients along the way.
  * NOTE: because backward() computes the simple gradient for each input node
  * i.e. it does not apply the seed vector. If you want to apply a seed vector,
  * see Function::backward_jacobian()
  */
  void backward();

  /**
  * A function pointer that defines the behaviour of this Node in forward mode. 
  * For example, if forward_func_ptr is set to OP::mul_forward() 
  * then this Node is a multiplication node that adds its child nodes when computing 
  * this Node's value and derivative in forward mode.
  * @see ForwardFunctions.hpp
  */
  void (*_forward_func_ptr)(Node &this_node){};
  /**
  * A function pointer that defines the behaviour of this Node in reverse mode. 
  * For example, if backward_func_ptr is set to OP::mul_backward() 
  * then this Node is a multiplication node that adds its child nodes when computing 
  * this Node's value and derivative in forward mode.
  * @see BackwardFunctions.hpp
  */
  void (*_backward_func_ptr)(Node &this_node){};

  /**
  * The computed value of this Node
  */
  float val;  
  /** 
  * The derivative (or seed) of this Node (used in forward mode)
  */
  float dval; 
  /**
  * The gradient of this Node (used in reverse mode)
  */
  float grad;

  /**
  * Pointers to this Node's child Nodes (i.e. its inputs). 
  * A node has up to 2 child Nodes.
  @see *_forward_func_ptr
  @see *_backward_func_ptr
  */
  std::vector<Node *> _children;
  /**
  * Pointers to this Node's parent Nodes.
  * A node can have multiple parents
  */
  std::vector<Node *> _parents;
  /**
  * The Function this Node is a member of
  * @see Function
  */ 
  Function *function_ptr =nullptr;
};

}  // namespace OP
#endif  // CS107_FINALPROJECT_NODE_HPP
