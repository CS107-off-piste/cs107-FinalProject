#ifndef CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP
#define CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP

#include <cmath>
#include "Node.hpp"

namespace OP {

    void identity_forward(Node &node) {}

    /** forward methods for binary operation **/
    void add_forward(Node &node) {
        node.val = node._children[0]->val + node._children[1]->val;
        node.dval = node._children[0]->dval + node._children[1]->dval;
    }

    void sub_forward(Node &node) {
        node.val = node._children[0]->val - node._children[1]->val;
        node.dval = node._children[0]->dval - node._children[1]->dval;
    }

    void mul_forward(Node &node) {
        node.val = node._children[0]->val * node._children[1]->val;
        node.dval = node._children[0]->dval * node._children[1]->val +
                    node._children[0]->val * node._children[1]->dval;
    }

    void div_forward(Node &node) {
        node.val = node._children[0]->val / node._children[1]->val;
        node.dval = (node._children[0]->dval * node._children[1]->val -
                     node._children[0]->val * node._children[1]->dval) / (node._children[1]->val * node._children[1]->val);
    }


    /** forward methods for unary operation **/
    void neg_forward(Node &node) {
        node.val = -node._children[0]->val;
        node.dval = -node._children[0]->dval;
    }

    void exp_forward(Node &node) {
        node.val = std::exp(node._children[0]->val);
        node.dval = node.val*node._children[0]->dval;
    }

}
#endif //CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP
