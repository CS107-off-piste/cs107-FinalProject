//
// Created by Zeren Long on 2020/10/18.
//

#ifndef CS107_FINALPROJECT_NODE_HPP
#define CS107_FINALPROJECT_NODE_HPP

#include <vector>

namespace OP {

    class Node {
    public:
        Node() : value(0.f), derivative(0.f) {};

        void (*forward)(Node &this_node){};
        void (*backward)(Node &this_node){};

        float value;
        float derivative;

        std::vector<Node*> children;
        std::vector<Node*> parents;

    };

}
#endif //CS107_FINALPROJECT_NODE_HPP
