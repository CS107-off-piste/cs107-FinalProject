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

    void pow_backward(Node &node) {
        node._children[0]->grad += node.grad * node._children[1]->val
                * std::pow(node._children[0]->val, node._children[1]->val - 1);
        node._children[1]->grad += node.grad * std::log(node._children[0]->val)
                * std::exp(node._children[1]->val * std::log(node._children[0]->val));
    }


    /** backward methods for unary operation **/
    void neg_backward(Node &node) {
        node._children[0]->grad += -node.grad;
    }

    void sqrt_backward(Node &node) {
        node._children[0]->grad = node.grad * 0.5f * std::pow(node._children[0]->val, -0.5f);
    }


    void exp_backward(Node &node) {
        node._children[0]->grad += node.grad * std::exp(node._children[0]->val);
    }

    void log_backward(Node &node) {
        node._children[0]->grad += node.grad * 1.f / node._children[0]->val;
    }

    void sin_backward(Node &node) {
        node._children[0]->grad += node.grad * std::cos(node._children[0]->val);
    }

    void cos_backward(Node &node) {
        node._children[0]->grad += node.grad * -std::sin(node._children[0]->val);
    }

    void tan_backward(Node &node) {
        node._children[0]->grad += node.grad * 1 / std::pow(std::cos(node._children[0]->val), 2);
    }

    void asin_backward(Node &node) {
        node._children[0]->grad += node.grad * 1.f/(std::sqrt(1 - std::pow(node._children[0]->val, 2)));
    }

    void acos_backward(Node &node) {
        node._children[0]->grad += node.grad * -1.f/(std::sqrt(1 - std::pow(node._children[0]->val, 2)));
    }

    void atan_backward(Node &node) {
        node._children[0]->grad += node.grad * 1.f/(1 + std::pow(node._children[0]->val, 2));
    }

    void sinh_backward(Node &node) {
        node._children[0]->grad += node.grad * std::cosh(node._children[0]->val);
    }

    void cosh_backward(Node &node) {
        node._children[0]->grad += node.grad * std::sinh(node._children[0]->val);
    }

    void tanh_backward(Node &node) {
        node._children[0]->grad += node.grad * 1.f / std::pow(std::cosh(node._children[0]->val), 2);
    }

}
#endif //CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP
