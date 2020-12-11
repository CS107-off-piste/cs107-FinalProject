#ifndef CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP
#define CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP

#include <cmath>
#include "Node.hpp"

namespace OP {

    static void identity_forward(Node &node) {}

    /** forward methods for binary operation **/
    static void add_forward(Node &node) {
        node.val = node._children[0]->val + node._children[1]->val;
        node.dval = node._children[0]->dval + node._children[1]->dval;
    }

    static void sub_forward(Node &node) {
        node.val = node._children[0]->val - node._children[1]->val;
        node.dval = node._children[0]->dval - node._children[1]->dval;
    }

    static void mul_forward(Node &node) {
        node.val = node._children[0]->val * node._children[1]->val;
        node.dval = node._children[0]->dval * node._children[1]->val +
                    node._children[0]->val * node._children[1]->dval;
    }

    static void div_forward(Node &node) {
        node.val = node._children[0]->val / node._children[1]->val;
        node.dval = (node._children[0]->dval * node._children[1]->val -
                     node._children[0]->val * node._children[1]->dval) / (node._children[1]->val * node._children[1]->val);
    }

    static void pow_forward(Node &node) {
        node.val = std::pow(node._children[0]->val , node._children[1]->val);
        node.dval = node.val * (node._children[1]->dval * std::log(node._children[0]->val)
                + node._children[1]->val / node._children[0]->val * node._children[0]->dval);
    }


    /** forward methods for unary operation **/
    static void neg_forward(Node &node) {
        node.val = -node._children[0]->val;
        node.dval = -node._children[0]->dval;
    }

    static void exp_forward(Node &node) {
        node.val = std::exp(node._children[0]->val);
        node.dval = node.val * node._children[0]->dval;
    }

    static void log_forward(Node &node) {
        node.val = std::log(node._children[0]->val);
        node.dval = 1/node.val * node._children[0]->dval;
    }

    static void sin_forward(Node &node) {
        node.val = std::sin(node._children[0]->val);
        node.dval = std::cos(node.val) * node._children[0]->dval;
    }

    static void cos_forward(Node &node) {
        node.val = std::cos(node._children[0]->val);
        node.dval = -std::sin(node.val) * node._children[0]->dval;
    }

    static void tan_forward(Node &node) {
        node.val = std::tan(node._children[0]->val);
        node.dval = 1.f/std::pow(std::cos(node.val), 2) * node._children[0]->dval;
    }

    static void asin_forward(Node &node) {
        node.val = std::asin(node._children[0]->val);
        node.dval = 1.f/(std::sqrt(1 - std::pow(node.val, 2))) * node._children[0]->dval;
    }

    static void acos_forward(Node &node) {
        node.val = std::acos(node._children[0]->val);
        node.dval = -1.f/(std::sqrt(1 - std::pow(node.val, 2))) * node._children[0]->dval;
    }

    static void atan_forward(Node &node) {
        node.val = std::atan(node._children[0]->val);
        node.dval = 1.f/(1 + std::pow(node.val, 2)) * node._children[0]->dval;
    }

}
#endif //CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP
