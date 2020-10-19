//
// Created by Zeren Long on 2020/10/18.
//

#ifndef CS107_FINALPROJECT_BINARYOPERATOR_HPP
#define CS107_FINALPROJECT_BINARYOPERATOR_HPP

#define BINARY_CONNECT(v1, v2, output)         \
        Node& tmp_v1 = const_cast<Node&>(v1);   \
        Node& tmp_v2 = const_cast<Node&>(v2);   \
        tmp_v1.parents.push_back(output);       \
        tmp_v2.parents.push_back(output);       \
        output->children.push_back(&tmp_v1);    \
        output->children.push_back(&tmp_v2);

#define CONSTANT_NODE(constant) \
        Node *node = new Node();    \
        node->value = constant;     \
        node->forward = identity_forward;   \
        node->backward = identity_backward;


#include "Node.hpp"
#include "ForwardFunctions.hpp"
#include "BackwardFunctions.hpp"

namespace OP {

    // overload binary operator

    // overload +
    inline Node& operator+(const Node &v1, const Node &v2) {

        Node* output = new Node();

        output->forward = (add_forward);
        output->backward = (add_backward);

        BINARY_CONNECT(v1, v2, output);

        return *output;
    }

    inline Node& operator+(const Node& v1, float constant){
        CONSTANT_NODE(constant)
        return v1 + *node;
    }

    inline Node& operator+(float constant, const Node& v1){
        CONSTANT_NODE(constant)
        return v1 + *node;
    }


    // overload *


    // overload /


}

#endif //CS107_FINALPROJECT_BINARYOPERATOR_HPP
