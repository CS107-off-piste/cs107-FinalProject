#ifndef CS107_FINALPROJECT_FUNCTION_HPP
#define CS107_FINALPROJECT_FUNCTION_HPP

#include <map>
#include <vector>
#include "Node.hpp"


namespace OP {

    typedef Node& Expression;
    typedef std::vector<std::reference_wrapper<Node>> Input;
    typedef std::vector<std::reference_wrapper<Node>> Output;
    typedef std::vector<float> Vec;
    typedef std::vector<std::vector<float>> Mat;

    class Function {
    public:
        // constructor
        explicit Function(Input &input_nodes, Output &output_nodes);
        explicit Function(Input &&input_nodes, Output &&output_nodes) : Function(input_nodes, output_nodes){}

        friend Node;

        void set_seed(Vec seeds);
        void set_seed(Vec &&seeds);

        Vec evaluate();                // evaluate each scalar function within Function

        Mat forward_jacobian();      // using forward mode to compute jacobian matrix
        float forward_derivative(Node &output_node, Node &wrt);

        void zero_grad();               // set grads of all nodes in the graph f to zero
        Mat backward_jacobian();     // using reverse mode to compute jabobian matrix


    private:
        void bfs(Node &output_node);
        void generate_aov_sequence();

        std::vector<Node*> input_node_ptrs;
        std::vector<Node*> output_node_ptrs;
        std::map<Node*, size_t> in_deg_book_keeper;
        std::vector<Node*> aov_sequence;
        std::map<Node*, size_t> node2aov_idx;
    };
}
#endif //CS107_FINALPROJECT_FUNCTION_HPP
