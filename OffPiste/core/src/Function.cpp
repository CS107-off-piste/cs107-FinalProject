#include "Function.hpp"

#include <deque>
#include <iostream>

namespace OP {

Function::Function(Input &input_nodes, Output &output_nodes) {
  // save pointers to all input nodes in input_node_ptrs
  for (auto &it : input_nodes) {
    input_node_ptrs.push_back(&it.get());
  }

  // save pointers to all output nodes in output_node_ptrs
  for (auto &it : output_nodes) {
    output_node_ptrs.push_back(&it.get());
  }

  // bfs and initialize in_deg_book_keeper
  for (Node *ptr : output_node_ptrs) {
    bfs(*ptr);
  }

  // build AOV network of DAG graph
  generate_aov_sequence();
}

//    Function::Function(Inputs &&input_nodes, Outputs &&output_nodes) :
//    Function(input_nodes, output_nodes){}

void Function::bfs(Node &output_node) {
  std::deque<Node *> queue;
  queue.push_back(&output_node);

  // breadth first traverse starting from output_node to book keep all nodes
  while (!queue.empty()) {
    Node *ptr = queue[0];
    if (in_deg_book_keeper.count(ptr) == 0) {
      in_deg_book_keeper[ptr] = ptr->_children.size();
    }
    queue.pop_front();
    for (Node *child : ptr->_children) {
      queue.push_back(child);
    }
  }
}

void Function::generate_aov_sequence() {
  std::map<Node *, size_t> tmp_in_deg_book_keeper =
      in_deg_book_keeper;  // keep track of the current in-degree of each node
  std::vector<Node *> stack;

  size_t count = 0;
  for (auto &iter : tmp_in_deg_book_keeper) {
    if (iter.second == 0) {  // the node that it pointing at has no child
      stack.push_back(iter.first);
    }
  }

  while (!stack.empty()) {
    Node *ptr = stack[stack.size() - 1];  // get a node whose in degree is zero
    aov_sequence.push_back(ptr);
    node2aov_idx.insert(
        std::pair<Node *, size_t>(ptr, count));  // update node2aov_idx map
    ptr->function_ptr = this;

    stack.pop_back();
    count++;

    for (auto &iter : ptr->_parents) {
      tmp_in_deg_book_keeper[iter]--;  // reduce one in degree
      if (tmp_in_deg_book_keeper[iter] == 0) {
        stack.push_back(iter);
      }
    }
  }

  if (count != in_deg_book_keeper.size()) {
    std::cerr << "Building AOV network failed due to cycle in the graph."
              << std::endl;
  }
}

void Function::set_seed(Vec seeds) {
  if (seeds.size() != input_node_ptrs.size()) {
    throw std::runtime_error(
        "Number of seeds not equal number of input nodes!");
  }

  // update the dval for each input node using the provided seed
  for (int i = 0; i < seeds.size(); i++) {
    input_node_ptrs[i]->dval = seeds.at(i);
    input_node_ptrs[i]->grad = seeds.at(i);
  }
}

void Function::set_seed(Vec &&seeds) { set_seed(seeds); }

Vec Function::evaluate() {
  Vec vec(output_node_ptrs.size(), 0);  // create Vector to store output

  // for each Node in the aov_sequence...
  for (auto &it : aov_sequence) {
    it->_forward_func_ptr(
        *it);  // compute that Node's properties using its forward function
  }

  // fetch the values of the output Nodes and return them
  for (int i = 0; i < output_node_ptrs.size(); i++) {
    vec[i] = output_node_ptrs[i]->val;
  }
  return vec;
}

Mat Function::forward_jacobian() {
  // initialize jacobian matrix and reserve space
  Mat jacob;
  // resize Jacobian to have number of rows equal to the number of outputs
  jacob.resize(output_node_ptrs.size());

  // resize Jacobian so that each row has a columns for each inputs
  for (auto &it : jacob) {
    it.resize(input_node_ptrs.size());
  }

  std::vector<float> dval_keeper;
  for (auto &it : input_node_ptrs) {
    // keep a copy of the seed for each Variable
    // so that the seeds can be restored at the end of this method
    dval_keeper.push_back(it->dval);

    // then set each seed to 0
    it->dval = 0.f;
  }

  // for all the input Variables...
  for (int j = 0; j < input_node_ptrs.size(); j++) {
    input_node_ptrs[j]->dval =
        dval_keeper.at(j);  // set the seed of corresponding node to its seed
    evaluate();

    for (int i = 0; i < output_node_ptrs.size(); i++) {
      jacob[i][j] = output_node_ptrs[i]->dval;
    }

    // reset the seed of this Variable to 0
    input_node_ptrs[j]->dval = 0.f;
  }

  // restore seeds for Variables
  for (int i = 0; i < dval_keeper.size(); i++) {
    input_node_ptrs[i]->dval = dval_keeper[i];
  }

  return jacob;
}

float Function::forward_derivative(Node &output_node, Node &wrt) {
  // keep a copy of the seed for each Variable
  // so that the seeds can be restored at the end of this method
  std::vector<float> dval_keeper;
  for (auto &it : input_node_ptrs) {
    dval_keeper.push_back(it->dval);
  }

  // set the seed of all input Variables to zero
  for (auto &it : input_node_ptrs) {
    it->dval = 0.f;
  }

  // set the seed of the Node we're taking the derivative w.r.t to 1
  wrt.dval = 1.f;

  // take a forward pass through the computation graph
  // to compute derivative w.r.t the wrt Node
  for (auto &it : aov_sequence) {
    it->_forward_func_ptr(*it);
  }

  // restore seeds for each Variable
  for (int i = 0; i < dval_keeper.size(); i++) {
    input_node_ptrs[i]->dval = dval_keeper[i];
  }

  return output_node.dval;
}

void Function::zero_grad() {
  for (auto &it : aov_sequence) {
    it->grad = 0.f;
  }
}

Mat Function::backward_jacobian() {
  // initialize jacobian matrix and reserve space
  Mat jacob;
  // resize Jacobian to have number of rows equal to number of output nodes
  // and columns equal to number of input nodes (i.e. Variables)
  jacob.resize(output_node_ptrs.size());
  for (auto &it : jacob) {
    it.resize(input_node_ptrs.size());
  }

  // book keeping all grads for each Variable for restoration at the end of this
  // method
  std::vector<float> input_grad_keeper;
  for (auto &it : input_node_ptrs) {
    input_grad_keeper.push_back(it->grad);
  }

  // for each input-output pair...
  for (int inp = 0; inp < input_node_ptrs.size(); inp++) {
    for (int out = 0; out < output_node_ptrs.size(); out++) {
      zero_grad();  // reset gradients to zero

      // take reverse pass on the current output node
      output_node_ptrs[out]->backward();
      // save the result
      // which is the computed gradient for that input node times the input
      // node's seed (i.e. initial gradient)
      jacob[out][inp] = input_node_ptrs[inp]->grad * input_grad_keeper.at(inp);
    }
  }

  // restore gradients to initial values
  for (int i = 0; i < input_node_ptrs.size(); i++) {
    input_node_ptrs[i]->grad = input_grad_keeper.at(i);
  }

  return jacob;
}

}  // namespace OP
