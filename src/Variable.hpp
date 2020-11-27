//
// Created by Zeren Long on 2020/10/19.
//

#ifndef CS107_FINALPROJECT_VARIABLE_HPP
#define CS107_FINALPROJECT_VARIABLE_HPP

#include "Node.hpp"
#include "ForwardFunctions.hpp"
#include "BackwardFunctions.hpp"

namespace OP {
    class Variable : public Node {
    public:
        Variable(float val=0.f, float dval=0.f) : Node(val, dval) {
            forward = identity_forward;
            backward = identity_backward;
        }
    };
}
#endif //CS107_FINALPROJECT_VARIABLE_HPP
