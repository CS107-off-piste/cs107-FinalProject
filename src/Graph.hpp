//
// Created by Zeren Long on 2020/10/19.
//

#ifndef CS107_FINALPROJECT_GRAPH_HPP
#define CS107_FINALPROJECT_GRAPH_HPP

#define EXPRESSION OP::Node&
#define EXPRESSIONS std::vector<std::reference_wrapper<Node>>

#include <map>
#include <vector>
#include "Node.hpp"

namespace OP {
    class Graph {
    public:

        explicit Graph(EXPRESSIONS &output_nodes);
        float evaluate(Node& output_node);
        float forward_derivative(Node &output_node, Node &wrt);

    private:
        void bfs(Node &output_node);
        void generate_aov_sequence();

        std::vector<Node*> output_node_ptrs;
        std::map<Node*, size_t> book_keeper;
        std::vector<Node*> aov_sequence;
    };
}
#endif //CS107_FINALPROJECT_GRAPH_HPP
