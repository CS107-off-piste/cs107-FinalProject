#ifndef CS107_FINALPROJECT_NODE_HPP
#define CS107_FINALPROJECT_NODE_HPP

#include <vector>

namespace OP {

class Function;

class Node {
 public:
  Node(float val = 0.f, float dval = 0.f, float grad = 0.f)
      : val(val), dval(dval), grad(grad){};  // constructor of this Node

  /** compute gradient using reverse mode from the Node that calls this function
    all the way back to the input Nodes **/
  void backward();

  /** The two function pointers below will be bound to specific functions
   defined in ForwardFunctions.hpp and BackwardFunctions.hpp to identify the
   behavior of this node. For example, if (*forward) is bound to add_forward and
   (*backward) is bound to add_backward, then this Node is an Add Node which
   adds its children nodes.**/
  void (*_forward_func_ptr)(Node &this_node){};
  void (*_backward_func_ptr)(Node &this_node){};

  // Below are some important attributes of this Node.
  float val;  // The value of this Node
  float
      dval;  // The derivative (seed) of this Node (only used for forward mode)
  float grad;  // The gradient of this Node (only used for reverse mode)

  std::vector<Node *> _children;  // The pointers to this Node's child Nodes. A
                                  // Node has at most two children.
  std::vector<Node *> _parents;   // The pointers to this Node's parent Nodes. A
                                  // Node can have multiple parents.
  Function *function_ptr =
      nullptr;  // The pointer to the function that this node belongs to,
                // initialized when building AOV network
};

}  // namespace OP
#endif  // CS107_FINALPROJECT_NODE_HPP
