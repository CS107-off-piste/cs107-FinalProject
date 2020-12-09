#ifndef CS107_FINALPROJECT_BINARYOPERATOR_HPP
#define CS107_FINALPROJECT_BINARYOPERATOR_HPP

#include "Node.hpp"
#include "ForwardFunctions.hpp"
#include "BackwardFunctions.hpp"

#define BINARY_CONNECT(v1, v2, output)         \
        Node& tmp_v1 = const_cast<Node&>(v1);   \
        Node& tmp_v2 = const_cast<Node&>(v2);   \
        tmp_v1._parents.push_back(output);       \
        tmp_v2._parents.push_back(output);       \
        output->_children.push_back(&tmp_v1);    \
        output->_children.push_back(&tmp_v2);

#define MAKE_CONSTANT_NODE(constant) \
        Node *node = new Node();    \
        node->val = constant;     \
        node->_forward_func_ptr = identity_forward;   \
        node->_backward_func_ptr = identity_backward;

#define OVERLOAD_BINARY_OPERATOR(operator_symbol, forward_func, backward_func) \
\
        inline Node& operator_symbol(const Node &v1, const Node &v2) { \
            Node* output = new Node(); \
            output->_forward_func_ptr = forward_func; \
            output->_backward_func_ptr = backward_func; \
            BINARY_CONNECT(v1, v2, output); \
            return *output; \
        } \
        inline Node& operator_symbol(const Node& v1, float constant){ \
            MAKE_CONSTANT_NODE(constant); \
            return operator_symbol(v1, *node); \
        } \
        inline Node& operator_symbol(float constant, const Node& v1){  \
            MAKE_CONSTANT_NODE(constant); \
            return operator_symbol(v1, *node); \
        } \

namespace OP {

    /** overload binary operators: +, -, *, /, pow **/

    OVERLOAD_BINARY_OPERATOR(operator+, add_forward, add_backward)
    OVERLOAD_BINARY_OPERATOR(operator-, sub_forward, sub_backward)
    OVERLOAD_BINARY_OPERATOR(operator*, mul_forward, mul_backward)
    OVERLOAD_BINARY_OPERATOR(operator/, div_forward, div_backward)
    OVERLOAD_BINARY_OPERATOR(pow, pow_forward, pow_backward)

}

#endif //CS107_FINALPROJECT_BINARYOPERATOR_HPP
