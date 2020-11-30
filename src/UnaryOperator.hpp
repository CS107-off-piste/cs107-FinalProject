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

#define OVERLOAD_UNARY_OPERATOR(operator_symbol, forward_func, backward_func) \
    inline Node& operator_symbol(const Node &v) { \
                Node* output = new Node(); \
                output->forward = forward_func; \
                output->backward = backward_func; \
                UNARY_CONNECT(v, output); \
                return *output; \
        } \

namespace OP {

    /** overload unary operators: **/
    OVERLOAD_UNARY_OPERATOR(operator-, neg_forward, neg_backward)
    OVERLOAD_UNARY_OPERATOR(exp, exp_forward, exp_backward)

}
#endif //CS107_FINALPROJECT_UNARYOPERATOR_HPP
