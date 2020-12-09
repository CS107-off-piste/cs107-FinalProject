#ifndef CS107_FINALPROJECT_UNARYOPERATOR_HPP
#define CS107_FINALPROJECT_UNARYOPERATOR_HPP

#include <cmath>
#include "Node.hpp"
#include "ForwardFunctions.hpp"
#include "BackwardFunctions.hpp"

#define UNARY_CONNECT(input, output)         \
    Node& tmp_input = const_cast<Node&>(input); \
    tmp_input._parents.push_back(output); \
    output->_children.push_back(&tmp_input);

#define OVERLOAD_UNARY_OPERATOR(operator_symbol, forward_func, backward_func) \
    inline Node& operator_symbol(const Node &v) { \
                Node* output = new Node(); \
                output->_forward_func_ptr = forward_func; \
                output->_backward_func_ptr = backward_func; \
                UNARY_CONNECT(v, output); \
                return *output; \
        } \

namespace OP {

    /** overload unary operators: **/
    OVERLOAD_UNARY_OPERATOR(operator-, neg_forward, neg_backward)
    OVERLOAD_UNARY_OPERATOR(exp, exp_forward, exp_backward)
    OVERLOAD_UNARY_OPERATOR(sin, sin_forward, sin_backward)
    OVERLOAD_UNARY_OPERATOR(cos, cos_forward, cos_backward)
    OVERLOAD_UNARY_OPERATOR(tan, tan_forward, tan_backward)
    OVERLOAD_UNARY_OPERATOR(asin, asin_forward, asin_backward)
    OVERLOAD_UNARY_OPERATOR(acos, acos_forward, acos_backward)
    OVERLOAD_UNARY_OPERATOR(atan, atan_forward, atan_backward)

}
#endif //CS107_FINALPROJECT_UNARYOPERATOR_HPP
