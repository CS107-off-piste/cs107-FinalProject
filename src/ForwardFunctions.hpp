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
        node.val = node.children[0]->val + node.children[1]->val;
        node.dval = node.children[0]->dval + node.children[1]->dval;
    }

    void sub_forward(Node &node) {
        node.val = node.children[0]->val - node.children[1]->val;
        node.dval = node.children[0]->dval - node.children[1]->dval;
    }

    void exp_forward(Node &node) {
        node.val = std::exp(node.children[0]->val);
        node.dval = node.val*node.children[0]->dval;
    }

}
#endif //CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP
