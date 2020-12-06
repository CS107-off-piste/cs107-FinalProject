#ifndef CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP
#define CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP

#include <cmath>
#include "Node.hpp"

namespace OP {

    void identity_backward(Node &node) {}

    /** backward methods for binary operation **/
    void add_backward(Node &node) {

        node._children[0]->grad += node.grad;
        node._children[1]->grad += node.grad;
    }

    void sub_backward(Node &node) {
        node._children[0]->grad += node.grad;
        node._children[1]->grad += -node.grad;
    }

    void mul_backward(Node &node) {
        node._children[0]->grad += node.grad * node._children[1]->val;
        node._children[1]->grad += node.grad * node._children[0]->val;
    }

    void div_backward(Node &node) {
        node._children[0]->grad += node.grad / node._children[1]->val;
        node._children[1]->grad += -node.grad * node._children[0]->val
                / (node._children[1]->val * node._children[1]->val);
    }


    /** backward methods for unary operation **/
    void neg_backward(Node &node) {
        node._children[0]->grad += -node.grad;
    }

    void exp_backward(Node &node) {
        node._children[0]->grad += node.grad * std::exp(node._children[0]->val);
    }
}
#endif //CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP
