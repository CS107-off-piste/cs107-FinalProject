#include <deque>
#include <iostream>
#include "Function.hpp"

namespace OP {

    Function::Function(INPUTS &input_nodes, OUTPUTS &output_nodes) {
        // save pointers to all input nodes in input_node_ptrs
        for (auto &it : input_nodes) {
            input_node_ptrs.push_back(&it.get());
        }

        // save pointers to all output nodes in output_node_ptrs
        for (auto &it : output_nodes) {
            output_node_ptrs.push_back(&it.get());
        }

        // bfs and initialize in_deg_book_keeper
        for (Node* ptr : output_node_ptrs) {bfs(*ptr);}

        // building AOV network of DAG graph
        generate_aov_sequence();
    }

    void Function::bfs(Node &output_node) {
        std::deque<Node*> queue;
        queue.push_back(&output_node);

        // breadth first traverse starting from output_node to book keep all nodes
        while (!queue.empty()) {
            Node *ptr = queue[0];
            if (in_deg_book_keeper.count(ptr) == 0) {
                in_deg_book_keeper[ptr] = ptr->_children.size();
            }
            queue.pop_front();
            for (Node* child : ptr->_children) {
                queue.push_back(child);
            }
        }
    }

    void Function::generate_aov_sequence() {

        std::map<Node*, size_t> tmp_in_deg_book_keeper = in_deg_book_keeper;  // keep track of the current in-degree of each node
        std::vector<Node*> stack;

        size_t count=0;
        for (auto & iter : tmp_in_deg_book_keeper) {
            if (iter.second == 0) {  // the node that it pointing at has no child
                stack.push_back(iter.first);
            }
        }

        while (!stack.empty()) {
            Node* ptr = stack[stack.size()-1];  // get a node whose in degree is zero
            aov_sequence.push_back(ptr);
            node2aov_idx.insert(std::pair<Node*, size_t>(ptr, count));  // update node2aov_idx map
            ptr->function_ptr = this;

            stack.pop_back();
            count++;

            for (auto & iter : ptr->_parents) {
                tmp_in_deg_book_keeper[iter]--;    // reduce one in degree
                if (tmp_in_deg_book_keeper[iter] == 0) {
                    stack.push_back(iter);
                }
            }
        }

        if (count != in_deg_book_keeper.size()) {
            std::cerr<<"Building AOV network failed due to cycle in the graph."<<std::endl;
        }
    }

//    size_t Function::get_node_idx_in_aov(Node *node_ptr) {
//        return node2aov_idx[node_ptr];
//    }

    VECTOR Function::evaluate() {
        VECTOR vec(output_node_ptrs.size(), 0);
        for (auto & it : aov_sequence) {
            it->_forward_func_ptr(*it);
        }
        for (int i=0; i<output_node_ptrs.size(); i++) {
            vec[i] = output_node_ptrs[i]->val;
        }
        return vec;
    }

    MATRIX Function::forward_jacobian() {

        // initialize jacobian matrix and reserve space
        MATRIX jacob;
        jacob.resize(output_node_ptrs.size());
        for (auto &it : jacob) {
            it.resize(input_node_ptrs.size());
        }

        // book keeping all dval of each Variable for restoration at the end of this method
        std::vector<float> dval_keeper;
        for (auto &it : input_node_ptrs) {
            dval_keeper.push_back(it->dval);
        }

        // set all dval of input nodes to zero
        for (auto &it : input_node_ptrs) {it->dval = 0.f;}

        for (int j=0; j<input_node_ptrs.size(); j++) {
            input_node_ptrs[j]->dval = 1.0f;            // set the seed of corresponding node to 1
            evaluate();

            for (int i=0; i<output_node_ptrs.size(); i++) {
                jacob[i][j] = output_node_ptrs[i]->dval;
            }

            input_node_ptrs[j]->dval = 0.f;             // set the seed of corresponding node back to 0
        }

        // restore dval from dval_keeper
        for (int i=0; i<dval_keeper.size(); i++) {
            input_node_ptrs[i]->dval = dval_keeper[i];
        }

        return jacob;
    }

    float Function::forward_derivative(Node &output_node, Node &wrt) {

        // book keep all dval of each Variable for restoration at the end of this method
        std::vector<float> dval_keeper;
        for (auto &it : input_node_ptrs) {
            dval_keeper.push_back(it->dval);
        }

        // set all dval of input nodes to zero
        for (auto &it : input_node_ptrs) {it->dval = 0.f;}

        wrt.dval = 1.f;
        for (auto & it : aov_sequence) {
            it->_forward_func_ptr(*it);
        }

        // restore from dval_keeper
        for (int i=0; i<dval_keeper.size(); i++) {
            input_node_ptrs[i]->dval = dval_keeper[i];
        }

        return output_node.dval;
    }

    void Function::zero_grad() {
        for (auto &it : aov_sequence) {
            it->grad = 0.f;
        }
    }

    MATRIX Function::backward_jacobian() {
        MATRIX jacob;
        jacob.resize(output_node_ptrs.size());
        for (auto &it : jacob) {
            it.resize(input_node_ptrs.size());
        }

        for (int i=0; i<output_node_ptrs.size(); i++) {
            zero_grad();
            output_node_ptrs[i]->backward();
            for (int j=0; j<input_node_ptrs.size(); j++) {
                jacob[i][j] = input_node_ptrs[j]->grad;
            }
        }

        return jacob;
    }

}