#ifndef CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP
#define CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP

#include <cmath>
#include "Node.hpp"

namespace OP {

    static void identity_backward(Node &node) {}

    /** backward methods for binary operation **/
    static void add_backward(Node &node) {

        node._children[0]->grad += node.grad;
        node._children[1]->grad += node.grad;
    }

    static void sub_backward(Node &node) {
        node._children[0]->grad += node.grad;
        node._children[1]->grad += -node.grad;
    }

    static void mul_backward(Node &node) {
        node._children[0]->grad += node.grad * node._children[1]->val;
        node._children[1]->grad += node.grad * node._children[0]->val;
    }

    static void div_backward(Node &node) {
        node._children[0]->grad += node.grad / node._children[1]->val;
        node._children[1]->grad += -node.grad * node._children[0]->val
                / (node._children[1]->val * node._children[1]->val);
    }

    static void pow_backward(Node &node) {
        node._children[0]->grad += node.grad * node._children[1]->val
                * std::pow(node._children[0]->val, node._children[1]->val - 1);
        node._children[1]->grad += node.grad * std::log(node._children[0]->val)
                * std::exp(node._children[1]->val * std::log(node._children[0]->val));
    }


    /** backward methods for unary operation **/
    static void neg_backward(Node &node) {
        node._children[0]->grad += -node.grad;
    }

    static void exp_backward(Node &node) {
        node._children[0]->grad += node.grad * std::exp(node._children[0]->val);
    }

    static void log_backward(Node &node) {
        node._children[0]->grad += node.grad * 1.f / node._children[0]->val;
    }

    static void sin_backward(Node &node) {
        node._children[0]->grad += node.grad * std::cos(node._children[0]->val);
    }

    static void cos_backward(Node &node) {
        node._children[0]->grad += node.grad * -std::sin(node._children[0]->val);
    }

    static void tan_backward(Node &node) {
        node._children[0]->grad += node.grad * 1 / std::pow(std::cos(node._children[0]->val), 2);
    }

    static void asin_backward(Node &node) {
        node._children[0]->grad += node.grad * 1.f/(std::sqrt(1 - std::pow(node._children[0]->val, 2)));
    }

    static void acos_backward(Node &node) {
        node._children[0]->grad += node.grad * -1.f/(std::sqrt(1 - std::pow(node._children[0]->val, 2)));
    }

    static void atan_backward(Node &node) {
        node._children[0]->grad += node.grad * 1.f/(1 + std::pow(node._children[0]->val, 2));
    }

}
#endif //CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP
