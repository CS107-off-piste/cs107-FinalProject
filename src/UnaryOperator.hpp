//
// Created by Zeren Long on 2020/10/18.
//

#ifndef CS107_FINALPROJECT_UNARYOPERATOR_HPP
#define CS107_FINALPROJECT_UNARYOPERATOR_HPP

#include <cmath>
#include "Node.hpp"
#include "ForwardFunctions.hpp"
#include "BackwardFunctions.hpp"

#define UNARY_CONNECT(input, output)         \
    Node& tmp_input = const_cast<Node&>(input); \
    tmp_input.parents.push_back(output); \
    output->children.push_back(&tmp_input);

namespace OP {

    inline Node& exp(const Node &v) {
        Node *output = new Node();

        output->forward = (exp_forward);
        output->backward = (exp_backward);

        UNARY_CONNECT(v, output);
        return *output;
    }

}
#endif //CS107_FINALPROJECT_UNARYOPERATOR_HPP
