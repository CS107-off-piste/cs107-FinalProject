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
   * @param val The initial value for this Variable
   * @param dval The initial dval (i.e. forward-mode seed) for this Variable
   * @param grad The initial gradient (i.e. reverse-mode seed) for this Variable
   */
  Variable(float val, float dval, float grad) : Node(val, dval, grad) {
    _forward_func_ptr = identity_forward;
    _backward_func_ptr = identity_backward;
  }

  /**
   * Equivalent to Variable(float val,float dval, float grad) except that since
   * no grad is provided, the dval is assumed to be the seed for both.
   * @see Variable(float,float,float)
   */
  Variable(float val = 0.f, float dval = 0.f) : Variable(val, dval, dval) {}
};

}  // namespace OP
#endif  // CS107_FINALPROJECT_VARIABLE_HPP
