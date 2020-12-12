#ifndef CS107_FINALPROJECT_VARIABLE_HPP
#define CS107_FINALPROJECT_VARIABLE_HPP

#include "BackwardFunctions.hpp"
#include "ForwardFunctions.hpp"
#include "Node.hpp"

namespace OP {

/**
* A Variable is a Node that represents an input to the expression. 
* (Rather than an intermediate output).
*/
class Variable : public Node {
 public:
 	/**
 	* Construct a Variable with the provided initial values.
 	* @param val The initial value of this Variable
 	* @param dval The initial (i.e. seed) derivative of this Variable
 	* @param grad The initial (i.e. seed) gradient of this Variable
 	*/
  Variable(float val = 0.f, float dval = 0.f, float grad = 0.f)
      : Node(val, dval, grad) {
    _forward_func_ptr = identity_forward;
    _backward_func_ptr = identity_backward;
  }
};

}  // namespace OP
#endif  // CS107_FINALPROJECT_VARIABLE_HPP
