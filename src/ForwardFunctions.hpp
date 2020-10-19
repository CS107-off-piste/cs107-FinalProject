//
// Created by Zeren Long on 2020/10/19.
//

#ifndef CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP
#define CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP

#include "Node.hpp"
#include <cmath>

namespace OP {

    void identity_forward(Node &node) {}

    void add_forward(Node &node) {
        for (Node* child: node.children) {
            node.value += child->value;
            node.derivative += child->derivative;
        }
    }

    void sub_forward(Node &node) {
        for (Node* child: node.children) {
            node.value -= child->value;
            node.derivative -= child->derivative;
        }
    }

    void exp_forward(Node &node) {
        node.value = std::exp(node.children[0]->value);
        node.derivative = node.value*node.children[0]->derivative;
    }

}
#endif //CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP
