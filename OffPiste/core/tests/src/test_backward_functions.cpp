/* googletest header files */
#include "gtest/gtest.h"

/* source / header files */
#include "BackwardFunctions.hpp"
#include "Node.hpp"
#include "test_vars.h"

// add an AD shortcut for brevity
using namespace OP;

TEST(BackwardFunctions, Identity) {
  // Init
  Node node(1.0, 2.0, 3.0);

  // Identity
  identity_backward(node);

  // Validate
  EXPECT_NEAR(node.val, 1.0, 1E-8);
  EXPECT_NEAR(node.dval, 2.0, 1E-8);
  EXPECT_NEAR(node.grad, 3.0, 1E-8);
}

//--------------------------- Binary Functions --------------------------------
TEST(BackwardFunctions, Add) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 10.0);
  Node child2(3.0, 2.0, 20.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Add
  add_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 11.0, 1E-6);
  EXPECT_NEAR(child2.grad, 21.0, 1E-6);
}

TEST(BackwardFunctions, Subtract) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 10.0);
  Node child2(3.0, 2.0, 20.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Subtract
  sub_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 11.0, 1E-6);
  EXPECT_NEAR(child2.grad, 19.0, 1E-6);
}

TEST(BackwardFunctions, Multiply) {
  // Init
  Node node(0.0, 0.0, 2.0);
  Node child1(2.0, 1.5, 10.0);
  Node child2(3.0, 2.0, 20.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Multiply
  mul_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 16.0, 1E-6);
  EXPECT_NEAR(child2.grad, 24.0, 1E-6);
}

TEST(BackwardFunctions, Divide) {
  // Init
  Node node1;
  Node node2;
  Node child1(1.0, 1.9, 2.0);
  Node child2(2.0, 4.4, 3.0);
  Node child3(0.0, 0.0, 4.0);

  node1._children.push_back(&child1);
  node1._children.push_back(&child2);

  node2._children.push_back(&child1);
  node2._children.push_back(&child3);

  // Divide
  div_backward(node1);

  // Validate
  EXPECT_NEAR(child1.grad, 2.0, 1E-4);
  EXPECT_NEAR(child2.grad, 3.0, 1E-4);

  // Validate Divide by 0
  try {
    div_backward(node2);
  } catch (const char* msg) {
    EXPECT_EQ(msg, "Divide by zero");
  }
  EXPECT_NEAR(child1.grad, 2.0, 1E-8);
  EXPECT_NEAR(child3.grad, 4.0, 1E-8);
}

TEST(BackwardFunctions, Power) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 10.0);
  Node child2(3.0, 2.0, 20.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Power
  pow_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 22.0, 1E-6);
  EXPECT_NEAR(child2.grad, 25.5452, 1E-4);
}

//--------------------- Negate, Sqrt, Exponent, Log ---------------------------
TEST(BackwardFunctions, Negate) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Negate
  neg_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 2.0, 1E-4);
}

TEST(BackwardFunctions, Sqrt) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Sqrt
  sqrt_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 0.3536, 1E-4);
}

TEST(BackwardFunctions, Exponent) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Exponent
  exp_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 10.3891, 1E-4);
}

TEST(BackwardFunctions, Logarithm) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Logarithm
  log_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 3.5, 1E-4);
}

//--------------------------- Trigonometric Functions -------------------------
TEST(BackwardFunctions, Sine) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Sine
  sin_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 2.5839, 1E-4);
}

TEST(BackwardFunctions, Cosine) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Cosine
  cos_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 2.0907, 1E-4);
}

TEST(BackwardFunctions, Tangent) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Tangent
  tan_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 8.7744, 1E-4);
}

TEST(BackwardFunctions, Asin) {
  // Init
  Node node(0.1, 0.0, 0.9);
  Node child1(-0.2, 1.5, 0.6);
  node._children.push_back(&child1);

  // Asin
  asin_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 1.5186, 1E-4);
}

TEST(BackwardFunctions, Acos) {
  // Init
  Node node(0.1, 0.0, 0.9);
  Node child1(-0.2, 1.5, 0.6);
  node._children.push_back(&child1);

  // Acos
  acos_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, -0.3186, 1E-4);
}

TEST(BackwardFunctions, Atan) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Atan
  atan_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 3.2, 1E-4);
}

TEST(BackwardFunctions, Sinh) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Sinh
  sinh_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 6.7622, 1E-4);
}

TEST(BackwardFunctions, Cosh) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Cosh
  cosh_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 6.6269, 1E-4);
}

TEST(BackwardFunctions, Tanh) {
  // Init
  Node node(0.0, 0.0, 1.0);
  Node child1(2.0, 1.5, 3.0);
  node._children.push_back(&child1);

  // Tanh
  tanh_backward(node);

  // Validate
  EXPECT_NEAR(child1.grad, 3.0707, 1E-4);
}
