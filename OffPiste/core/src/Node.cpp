#include "Node.hpp"

#include "Function.hpp"

namespace OP {
void OP::Node::backward() {
  float save_grad = grad; // keep gradient around
  this->grad = 1.0f;  // dthis/dthis = 1.0f

  // get this Node's position in the Function
  size_t idx_in_aov_seq = this->function_ptr->node2aov_idx[this];

  // update Node->grad by calling _backward_func_ptr() in reverse order
  // starting from this Node's index
  for (int i = idx_in_aov_seq; i >= 0; i--) {
    Node* node = this->function_ptr->aov_sequence[i];
    node->_backward_func_ptr(*node);
  }
  this->grad = save_grad;
}
}  // namespace OP