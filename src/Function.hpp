//
// Created by Zeren Long on 2020/10/19.
//

#ifndef CS107_FINALPROJECT_FUNCTION_HPP
#define CS107_FINALPROJECT_FUNCTION_HPP

#define EXPRESSION OP::Node&
#define INPUTS std::vector<std::reference_wrapper<Node>>
#define OUTPUTS std::vector<std::reference_wrapper<Node>>
#define VECTOR std::vector<float>
#define MATRIX std::vector<std::vector<float>>

#include <map>
#include <vector>
#include "Node.hpp"


namespace OP {
    class Function {
    public:
        // constructor
        explicit Function(INPUTS &input_nodes, OUTPUTS &output_nodes);
        VECTOR evaluate();                // evaluate each scalar function within Function class
        MATRIX forward_jacobian();      // using forward mode to compute jacobian matrix

        float forward_derivative(Node &output_node, Node &wrt);

    private:
        void bfs(Node &output_node);
        void generate_aov_sequence();

        std::vector<Node*> input_node_ptrs;
        std::vector<Node*> output_node_ptrs;
        std::map<Node*, size_t> in_deg_book_keeper;
        std::vector<Node*> aov_sequence;
    };
}
#endif //CS107_FINALPROJECT_FUNCTION_HPP
