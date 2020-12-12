#ifndef CS107_FINALPROJECT_FUNCTION_HPP
#define CS107_FINALPROJECT_FUNCTION_HPP

#include <functional>
#include <map>
#include <vector>

#include "Node.hpp"

namespace OP {

/**
 * An Expression is a reference to a Node.
 */
typedef Node &Expression;
/**
 * An Input is a vector of Nodes representing the input Nodes of a function
 */
typedef std::vector<std::reference_wrapper<Node>> Input;
/**
 * An Output is a vector of Nodes representing the output Nodes of a function
 */
typedef std::vector<std::reference_wrapper<Node>> Output;
/**
 * A Vec is a shortcut for a vector of values
 */
typedef std::vector<float> Vec;
/**
 * A Mat is a shortcut for a vector of vectors (i.e. a Matrix)
 */
typedef std::vector<std::vector<float>> Mat;

/**
 * A Function is composed of Nodes
 */
class Function {
 public:
  /**
   * Construct a Function (and associated computation graph) connecting the
   * Input to the Output
   * @param &input_nodes the input Nodes (i.e. Variables) for this Function
   * @param &output_nodes the terminal Nodes (i.e. outputs) of this Function
   */
  explicit Function(Input &input_nodes, Output &output_nodes);
  /**
   * @see Function(Input&, Output&)
   */
  explicit Function(Input &&input_nodes, Output &&output_nodes)
      : Function(input_nodes, output_nodes) {}

  friend Node;

  /**
   * Set the derivative for all input Nodes of this function
   * @param seeds A vector containing the derivatives to apply. Values are
   * applied in order to the input nodes.
   * @throws std::runtime_error if the length of the provided vector is not the
   * same as the number of input nodes.
   */
  void set_seed(Vec seeds);
  /**
   * See OP::Function::set_seed(Vec)
   * @see OP::Function::set_seed(Vec)
   */
  void set_seed(Vec &&seeds);

  /**
   * Evaluate the value of each output node in this Function by computing a
   * forward mode pass
   */
  Vec evaluate();

  /**
   * Compute Jacobian matrix using forward mode
   * Note: strictly speaking, automatic differentiation does not compute the
   * Jacobian matrix Instead, it computes the Jacobian matrix multiplied by the
   * seed vector If you want the plain Jacobian matrix, set your seed values
   * to 1.
   * @returns Mat The Jacobian matrix for this function.
   * @see set_seed(Vec seeds)
   */
  Mat forward_jacobian();

  /**
   * Compute the derivative of this Function w.r.t the provided Node
   * Uses forward mode
   * @param &output_node The output node (i.e. function endpoint) to compute the
   * derivative of
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
   * Note: strictly speaking, automatic differentiation does not compute the
   * Jacobian matrix. Instead, it computes the Jacobian matrix multiplied by the
   * seed vector. If you want the plain Jacobian matrix, set your seed values
   * to 1.
   *
   * Further, the reverse mode of automatic differentiation sometimes returns
   * the transpose of the Jacobian. OffPiste does not return a transposed
   * Jacobian.
   * @returns Mat The Jacobian matrix for this function.
   * @see set_seed(Vec seeds)
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
