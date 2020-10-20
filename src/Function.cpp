//
// Created by Zeren Long on 2020/10/19.
//

#include <deque>
#include <iostream>
#include "Function.hpp"

namespace OP {

    Function::Function(EXPRESSIONS &output_nodes) {
        for (auto it: output_nodes) {
            output_node_ptrs.push_back(&it.get());
        }

        // bfs
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
            if (book_keeper.count(ptr) == 0) {
                book_keeper[ptr] = ptr->children.size();
            }
            queue.pop_front();
            for (Node* child : ptr->children) {
                queue.push_back(child);
            }
        }
    }

    void Function::generate_aov_sequence() {

        std::map<Node*, size_t> tmp_book_keeper = book_keeper;  // keep track of the current in degree of each node
        std::vector<Node*> stack;

        size_t count=0;
        for (auto & iter : tmp_book_keeper) {
            if (iter.second == 0) {  // the node that it pointing at has no child
                stack.push_back(iter.first);
            }
        }

        while (!stack.empty()) {
            Node* ptr = stack[stack.size()-1];  // get a node whose in degree is zero
            aov_sequence.push_back(ptr);
            stack.pop_back();
            count++;

            for (auto & iter : ptr->parents) {
                tmp_book_keeper[iter]--;    // reduce one in degree
                if (tmp_book_keeper[iter] == 0) {
                    stack.push_back(iter);
                }
            }
        }

        if (count != book_keeper.size()) {
            std::cerr<<"Building AOV network failed due to cycle in the graph."<<std::endl;
        }
    }

    float Function::evaluate(Node &output_node) {
        for (auto & it : aov_sequence) {
            it->forward(*it);
        }
        return output_node.value;
    }

    float Function::forward_derivative(Node &output_node, Node &wrt) {
        wrt.derivative = 1.f;
        for (auto & it : aov_sequence) {
            it->forward(*it);
        }
        wrt.derivative=0.f;
        return output_node.derivative;
    }

}