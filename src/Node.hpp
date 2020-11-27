//
// Created by Zeren Long on 2020/10/18.
//

#ifndef CS107_FINALPROJECT_NODE_HPP
#define CS107_FINALPROJECT_NODE_HPP

#include <vector>

namespace OP {

    class Node {
    public:
        Node(float val=0.f, float dval=0.f) : val(val), dval(dval) {};  // constructor of this Node


        /** The two function pointers below will be bound to specific functions in ForwardFUnctions.hpp and BackwardFunctions.hpp
         to identify the behavior of this node. For example, if (*forward) is bound to add_forward and (*backward) is bound
         to add_backward, then this Node is an Add Node which adds its children nodes.**/
        void (*forward)(Node &this_node){};
        void (*backward)(Node &this_node){};


        // Below are some important attributes of this Node.
        float val;  // The value of this Node
        float dval; // The derivative (seed) of this Node

        std::vector<Node*> children;    // The pointers to this Node's children Nodes. At most TWO children of a Node.
        std::vector<Node*> parents;     // The pointers to this Node's parent Nodes.
    };
}
#endif //CS107_FINALPROJECT_NODE_HPP
