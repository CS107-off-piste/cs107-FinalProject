/** @file BackwardFunctions.hpp
* This file contains function pointers for reverse-mode automatic differentiation
* @see OP::Node::_backward_func_ptr
*/

#ifndef CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP
#define CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP

#include <cmath>

#include "Node.hpp"

/**
* OP is the namespace for methods provided by the OffPiste library
*/
namespace OP {

/**
* Identity operation for reverse-mode.
* The identity operation does not change any gradients.
* @param &node The parent node to apply the operation to.
*/
static void identity_backward(Node &node) {}

//====================================================//
//                Binary Operators                    //
//====================================================//

/**
* Addition operation for reverse-mode.
* This operation adds the two child nodes.
* @param &node The parent node to apply the operation to.
*/
static void add_backward(Node &node) {
  node._children[0]->grad += node.grad;
  node._children[1]->grad += node.grad;
}

/**
* Subtraction operation for reverse-mode.
* This operation subtracts the first child node from the second child node.
* @param &node The parent node to apply the operation to.
*/
static void sub_backward(Node &node) {
  node._children[0]->grad += node.grad;
  node._children[1]->grad += -node.grad;
}

/**
* Multiplication operation for reverse-mode.
* This operation multiplies the two child nodes.
* @param &node The parent node to apply the operation to.
*/
static void mul_backward(Node &node) {
  node._children[0]->grad += node.grad * node._children[1]->val;
  node._children[1]->grad += node.grad * node._children[0]->val;
}

/**
* Division operation for reverse-mode.
* This operation divides the first child node by the second child node.
* @param &node The parent node to apply the operation to.
* @throws std::runtime_error If the divisor is 0
*/
static void div_backward(Node &node) {
  if (equal(node._children[1]->val, 0.0)) {
    throw "Divide by zero";
  }
  node._children[0]->grad += node.grad / node._children[1]->val;
  node._children[1]->grad += -node.grad * node._children[0]->val /
                             (node._children[1]->val * node._children[1]->val);
}

/**
* Power operation for reverse-mode.
* This operation raises the first child node to the power of the second child node.
* @param &node The parent node to apply the operation to.
*/
static void pow_backward(Node &node) {
  node._children[0]->grad +=
      node.grad * node._children[1]->val *
      std::pow(node._children[0]->val, node._children[1]->val - 1);
  node._children[1]->grad +=
      node.grad * std::log(node._children[0]->val) *
      std::exp(node._children[1]->val * std::log(node._children[0]->val));
}

//====================================================//
//                 Unary Operators                    //
//====================================================//

/**
* Unary negation operation for reverse-mode.
* This operation negates the child node.
* i.e. y = -x
* @param &node The parent node to apply the operation to.
*/
static void neg_backward(Node &node) { node._children[0]->grad += -node.grad; }

/**
* Square root operation for reverse-mode.
* This operation applies a square root to the child node.
* @param &node The parent node to apply the operation to.
*/
static void sqrt_backward(Node &node) {
  node._children[0]->grad =
      node.grad * 0.5f * std::pow(node._children[0]->val, -0.5f);
}

/**
* Exponential operation for reverse-mode.
* This operation applies the exponential function e^x to the child node.
* @param &node The parent node to apply the operation to.
*/
static void exp_backward(Node &node) {
  node._children[0]->grad += node.grad * std::exp(node._children[0]->val);
}

/**
* Logarithm operation for reverse-mode.
* This operation applies the natural log (ln)to the child node.
* @param &node The parent node to apply the operation to.
*/
static void log_backward(Node &node) {
  node._children[0]->grad += node.grad * 1.f / node._children[0]->val;
}

/**
* Sine operation for reverse-mode.
* This operation applies the sine function to the child node.
* @param &node The parent node to apply the operation to.
*/
static void sin_backward(Node &node) {
  node._children[0]->grad += node.grad * std::cos(node._children[0]->val);
}

/**
* Cosine operation for reverse-mode.
* This operation applies the cosine function to the child node.
* @param &node The parent node to apply the operation to.
*/
static void cos_backward(Node &node) {
  node._children[0]->grad += node.grad * -std::sin(node._children[0]->val);
}

/**
* Tangent operation for reverse-mode.
* This operation applies the tangent function to the child node.
* @param &node The parent node to apply the operation to.
*/
static void tan_backward(Node &node) {
  node._children[0]->grad +=
      node.grad * 1 / std::pow(std::cos(node._children[0]->val), 2);
}

/**
* Arcsine operation for reverse-mode.
* This operation applies the arcsine function to the child node.
* @param &node The parent node to apply the operation to.
*/
static void asin_backward(Node &node) {
  node._children[0]->grad +=
      node.grad * 1.f / (std::sqrt(1 - std::pow(node._children[0]->val, 2)));
}

/**
* Arccos operation for reverse-mode.
* This operation applies the arccos function to the child node.
* @param &node The parent node to apply the operation to.
*/
static void acos_backward(Node &node) {
  node._children[0]->grad +=
      node.grad * -1.f / (std::sqrt(1 - std::pow(node._children[0]->val, 2)));
}

/**
* Arctangent operation for reverse-mode.
* This operation applies the arctangent function to the child node.
* @param &node The parent node to apply the operation to.
*/
static void atan_backward(Node &node) {
  node._children[0]->grad +=
      node.grad * 1.f / (1 + std::pow(node._children[0]->val, 2));
}

/**
* Hyperbolic sine operation for reverse-mode.
* This operation applies the hyperbolic sine function to the child node.
* @param &node The parent node to apply the operation to.
*/
static void sinh_backward(Node &node) {
  node._children[0]->grad += node.grad * std::cosh(node._children[0]->val);
}

/**
* Hyperbolic cosine operation for reverse-mode.
* This operation applies the hyperbolic cosine function to the child node.
* @param &node The parent node to apply the operation to.
*/
static void cosh_backward(Node &node) {
  node._children[0]->grad += node.grad * std::sinh(node._children[0]->val);
}

/**
* Hyperbolic tangent operation for reverse-mode.
* This operation applies the hyperbolic tangent function to the child node.
* @param &node The parent node to apply the operation to.
*/
static void tanh_backward(Node &node) {
  node._children[0]->grad +=
      node.grad * 1.f / std::pow(std::cosh(node._children[0]->val), 2);
}

}  // namespace OP
#endif  // CS107_FINALPROJECT_BACKWARDFUNCTIONS_HPP
