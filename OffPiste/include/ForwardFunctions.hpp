/**
 * @file ForwardFunctions.hpp
 * Contains function pointers for forward-mode automatic differentiation
 * @see Node::*_forward_func_ptr
 */

#ifndef CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP
#define CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP

#include <cmath>

#include "Node.hpp"

namespace OP {

/**
 * Identity operation for forward-mode.
 * The identity operation does not change any gradients.
 * @param &node The parent node to apply the operation to.
 */
static void identity_forward(Node &node) {}

//====================================================//
//                Binary Operators                    //
//====================================================//

/**
 * Addition operation for forward-mode.
 * This operation adds the two child nodes.
 * @param &node The parent node to apply the operation to.
 */
static void add_forward(Node &node) {
  node.val = node._children[0]->val + node._children[1]->val;
  node.dval = node._children[0]->dval + node._children[1]->dval;
}

/**
 * Subtraction operation for forward-mode.
 * This operation subtracts the first child node from the second child node.
 * @param &node The parent node to apply the operation to.
 */
static void sub_forward(Node &node) {
  node.val = node._children[0]->val - node._children[1]->val;
  node.dval = node._children[0]->dval - node._children[1]->dval;
}

/**
 * Multiplication operation for forward-mode.
 * This operation multiplies the two child nodes.
 * @param &node The parent node to apply the operation to.
 */
static void mul_forward(Node &node) {
  node.val = node._children[0]->val * node._children[1]->val;
  node.dval = node._children[0]->dval * node._children[1]->val +
              node._children[0]->val * node._children[1]->dval;
}

/**
 * Division operation for forward-mode.
 * This operation divides the first child node by the second child node.
 * @param &node The parent node to apply the operation to.
 * @throws std::runtime_error If the divisor is 0
 */
static void div_forward(Node &node) {
  if (equal(node._children[1]->val, 0.0)) {
    throw "Divide by zero";
  }
  node.val = node._children[0]->val / node._children[1]->val;
  node.dval = (node._children[0]->dval * node._children[1]->val -
               node._children[0]->val * node._children[1]->dval) /
              (node._children[1]->val * node._children[1]->val);
}

/**
 * Power operation for forward-mode.
 * This operation raises the first child node to the power of the second child
 * node.
 * @param &node The parent node to apply the operation to.
 */
static void pow_forward(Node &node) {
  node.val = std::pow(node._children[0]->val, node._children[1]->val);
  node.dval = node._children[1]->val *
                  std::pow(node._children[0]->val, node._children[1]->val - 1) *
                  node._children[0]->dval +
              node._children[1]->dval *
                  std::pow(node._children[0]->val, node._children[1]->val) *
                  std::log(node._children[0]->val);
}

//====================================================//
//                 Unary Operators                    //
//====================================================//

/**
 * Unary negation operation for forward-mode.
 * This operation negates the child node.
 * i.e. y = -x
 * @param &node The parent node to apply the operation to.
 */
static void neg_forward(Node &node) {
  node.val = -node._children[0]->val;
  node.dval = -node._children[0]->dval;
}

/**
 * Square root operation for forward-mode.
 * This operation applies a square root to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void sqrt_forward(Node &node) {
  node.val = std::sqrt(node._children[0]->val);
  node.dval =
      0.5f * std::pow(node._children[0]->val, -0.5f) * node._children[0]->dval;
}

/**
 * Exponential operation for forward-mode.
 * This operation applies the exponential function e^x to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void exp_forward(Node &node) {
  node.val = std::exp(node._children[0]->val);
  node.dval = std::exp(node._children[0]->val) * node._children[0]->dval;
}

/**
 * Logarithm operation for forward-mode.
 * This operation applies the natural log (ln)to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void log_forward(Node &node) {
  node.val = std::log(node._children[0]->val);
  node.dval = 1 / node._children[0]->val * node._children[0]->dval;
}

/**
 * Sine operation for forward-mode.
 * This operation applies the sine function to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void sin_forward(Node &node) {
  node.val = std::sin(node._children[0]->val);
  node.dval = std::cos(node._children[0]->val) * node._children[0]->dval;
}

/**
 * Cosine operation for forward-mode.
 * This operation applies the cosine function to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void cos_forward(Node &node) {
  node.val = std::cos(node._children[0]->val);
  node.dval = -std::sin(node._children[0]->val) * node._children[0]->dval;
}

/**
 * Tangent operation for forward-mode.
 * This operation applies the tangent function to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void tan_forward(Node &node) {
  node.val = std::tan(node._children[0]->val);
  node.dval = 1.f / std::pow(std::cos(node._children[0]->val), 2) *
              node._children[0]->dval;
}

/**
 * Arcsine operation for forward-mode.
 * This operation applies the arcsine function to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void asin_forward(Node &node) {
  node.val = std::asin(node._children[0]->val);
  node.dval = 1.f / (std::sqrt(1 - std::pow(node._children[0]->val, 2))) *
              node._children[0]->dval;
}

/**
 * Arccos operation for reverse-mode.
 * This operation applies the arccos function to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void acos_forward(Node &node) {
  node.val = std::acos(node._children[0]->val);
  node.dval = -1.f / (std::sqrt(1 - std::pow(node._children[0]->val, 2))) *
              node._children[0]->dval;
}

/**
 * Arctangent operation for forward-mode.
 * This operation applies the arctangent function to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void atan_forward(Node &node) {
  node.val = std::atan(node._children[0]->val);
  node.dval =
      1.f / (1 + std::pow(node._children[0]->val, 2)) * node._children[0]->dval;
}

/**
 * Hyperbolic sine operation for forward-mode.
 * This operation applies the hyperbolic sine function to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void sinh_forward(Node &node) {
  node.val = std::sinh(node._children[0]->val);
  node.dval = std::cosh(node._children[0]->val) * node._children[0]->dval;
}

/**
 * Hyperbolic cosine operation for forward-mode.
 * This operation applies the hyperbolic cosine function to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void cosh_forward(Node &node) {
  node.val = std::cosh(node._children[0]->val);
  node.dval = std::sinh(node._children[0]->val) * node._children[0]->dval;
}

/**
 * Hyperbolic tangent operation for forward-mode.
 * This operation applies the hyperbolic tangent function to the child node.
 * @param &node The parent node to apply the operation to.
 */
static void tanh_forward(Node &node) {
  node.val = std::tanh(node._children[0]->val);
  node.dval = 1.f / std::pow(std::cosh(node._children[0]->val), 2) *
              node._children[0]->dval;
}

}  // namespace OP
#endif  // CS107_FINALPROJECT_FORWARDFUNCTIONS_HPP
