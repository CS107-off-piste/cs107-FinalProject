//
// Created by Zeren Long on 2020/10/19.
//

#ifndef CS107_FINALPROJECT_VARIABLE_HPP
#define CS107_FINALPROJECT_VARIABLE_HPP

#include "Node.hpp"
#include "ForwardFunctions.hpp"
#include "BackwardFunctions.hpp"

namespace OP {
    class Variable : public Node{
    public:
        Variable() : Node() {
            forward = identity_forward;
            backward = identity_backward;
        }
    };
}
#endif //CS107_FINALPROJECT_VARIABLE_HPP
