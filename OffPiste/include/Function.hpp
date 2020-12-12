#ifndef CS107_FINALPROJECT_FUNCTION_HPP
#define CS107_FINALPROJECT_FUNCTION_HPP

#include <functional>
#include <map>
#include <vector>

#include "Node.hpp"

namespace OP {

typedef Node &Expression;
typedef std::vector<std::reference_wrapper<Node>> Input;
typedef std::vector<std::reference_wrapper<Node>> Output;
typedef std::vector<float> Vec;
typedef std::vector<std::vector<float>> Mat;

/**
* A Function is composed of Nodes
*/
class Function {
 public:
  // constructor
  explicit Function(Input &input_nodes, Output &output_nodes);
  explicit Function(Input &&input_nodes, Output &&output_nodes)
      : Function(input_nodes, output_nodes) {}

  friend Node;

  /**
  * Set the derivative for all input Nodes of this function
  * @param seeds A vector containing the derivatives to apply. Values are applied in order to the input nodes.
  * @throws std::runtime_error if the length of the provided vector is not the same as the number of input nodes.
  */
  void set_seed(Vec seeds); 
  /**
  * See OP::Function::set_seed(Vec)
  * @see OP::Function::set_seed(Vec)
  */
  void set_seed(Vec &&seeds);

  /**
  * Evaluate the value of each output node in this Function by computing a forward mode pass
  */
  Vec evaluate();  

  /**
  * Compute Jacobian matrix using forward mode
  * @returns Mat The Jacobian matrix for this function.
  */
  Mat forward_jacobian();

  /**
  * Compute the derivative of this Function w.r.t the provided Node
  * Uses forward mode
  * @param &output_node The output node (i.e. function endpoint) to compute the derivative of
  * @param &wrt The input node (i.e. Variable) to compute the derivative w.r.t 
  * @returns The derivative
  */
  float forward_derivative(Node &output_node, Node &wrt);

  /**
  * Set gradient of all Nodes in this Function to 0
  */
  void zero_grad();
  /**
  * Compute Jacobian matrix using reverse mode
  * @returns Mat The Jacobian matrix for this function.
  */
  Mat backward_jacobian();  // using reverse mode to compute jabobian matrix

 private:
  void bfs(Node &output_node);
  void generate_aov_sequence();

  std::vector<Node *> input_node_ptrs;
  std::vector<Node *> output_node_ptrs;
  std::map<Node *, size_t> in_deg_book_keeper;
  std::vector<Node *> aov_sequence;
  std::map<Node *, size_t> node2aov_idx;
};
}  // namespace OP
#endif  // CS107_FINALPROJECT_FUNCTION_HPP
