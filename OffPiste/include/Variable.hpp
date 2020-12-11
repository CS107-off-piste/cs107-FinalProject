#ifndef CS107_FINALPROJECT_VARIABLE_HPP
#define CS107_FINALPROJECT_VARIABLE_HPP

#include "BackwardFunctions.hpp"
#include "ForwardFunctions.hpp"
#include "Node.hpp"

namespace OP {
class Variable : public Node {
 public:
  Variable(float val = 0.f, float dval = 0.f, float grad = 0.f)
      : Node(val, dval, grad) {
    _forward_func_ptr = identity_forward;
    _backward_func_ptr = identity_backward;
  }
};
}  // namespace OP
#endif  // CS107_FINALPROJECT_VARIABLE_HPP
