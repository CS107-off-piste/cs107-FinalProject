/* googletest header files */
#include "gtest/gtest.h"

/* source / header files */
#include "ForwardFunctions.hpp"
#include "Node.hpp"
#include "Variable.hpp"
#include "test_vars.h"

// add an AD shortcut for brevity
using namespace OP;

//--------------------------- Binary Functions --------------------------------
TEST(ForwardFunctions, Add) {
  // Init
  Node node;
  Node child1(2.0, 1.5);
  Node child2(3.0, 2.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Add
  add_forward(node);

  // Validate
  EXPECT_NEAR(node.val, 5.0, 1E-6);
  EXPECT_NEAR(node.dval, 3.5, 1E-6);
}

TEST(ForwardFunctions, Subtract) {
  // Init
  Node node;
  Node child1(2.0, 1.5);
  Node child2(3.0, 2.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Subtract
  sub_forward(node);

  // Validate
  EXPECT_NEAR(node.val, -1.0, 1E-6);
  EXPECT_NEAR(node.dval, -0.5, 1E-6);
}

TEST(ForwardFunctions, Multiply) {
  // Init
  Node node;
  Node child1(2.0, 1.5);
  Node child2(3.0, 2.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Multiply
  mul_forward(node);

  // Validate
  EXPECT_NEAR(node.val, 6.0, 1E-6);
  EXPECT_NEAR(node.dval, 8.5, 1E-6);
}

TEST(ForwardFunctions, Divide) {
  // Init
  Node node;
  Node child1(1.0, 1.9);
  Node child2(2.0, 4.4);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Divide
  div_forward(node);

  // Validate
  EXPECT_NEAR(node.val, 0.5, 1E-4);
  EXPECT_NEAR(node.dval, -0.15, 1E-2);
}

TEST(ForwardFunctions, Power) {
  // Init
  Node node;
  Node child1(1.0, 1.9);
  Node child2(3.0, 0.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Power
  pow_forward(node);

  // Validate
  EXPECT_NEAR(node.val, 1.0, 1E-6);
  EXPECT_NEAR(node.dval, 5.7, 1E-2);
}

//--------------------- Negate, Exponent, Log ---------------------------------
TEST(ForwardFunctions, Negate) {
  // Init
  Node node;
  Node child1(2.0, 1.5);
  node._children.push_back(&child1);

  // Negate
  neg_forward(node);

  // Validate
  EXPECT_NEAR(node.val, -2.0, 1E-6);
  EXPECT_NEAR(node.dval, -1.5, 1E-6);
}

TEST(ForwardFunctions, Exponent) {
  // Init
  Node node;
  Node child1(3.0, 2.0);
  node._children.push_back(&child1);

  // Exponent
  exp_forward(node);

  // Validate
  EXPECT_NEAR(node.val, 20.09, 1E-2);
  EXPECT_NEAR(node.dval, 40.17, 1E-2);
}

TEST(ForwardFunctions, Logarithm) {
  // Init
  Node node;
  Node child1(2.0, 1.5);
  node._children.push_back(&child1);

  // Logarithm
  log_forward(node);

  // Validate
  EXPECT_NEAR(node.val, 0.6931, 1E-4);
  EXPECT_NEAR(node.dval, 0.75, 1E-4);
}

//--------------------------- Trigonometric Functions -------------------------
TEST(ForwardFunctions, Sine) {
  // Init
  Node node;
  Node child1(3.0, 2.0);
  node._children.push_back(&child1);

  // Sine
  sin_forward(node);

  // Validate
  EXPECT_NEAR(node.val, 0.1411, 1E-4);
  EXPECT_NEAR(node.dval, -1.98, 1E-2);
}

TEST(ForwardFunctions, Cosine) {
  // Init
  Node node;
  Node child1(3.0, 2.0);
  node._children.push_back(&child1);

  // Cosine
  cos_forward(node);

  // Validate
  EXPECT_NEAR(node.val, -0.99, 1E-4);
  EXPECT_NEAR(node.dval, -0.28, 1E-2);
}

TEST(ForwardFunctions, Tangent) {
  // Init
  Node node;
  Node child1(3.0, 2.0);
  node._children.push_back(&child1);

  // Tangent
  tan_forward(node);

  // Validate
  EXPECT_NEAR(node.val, -0.1425, 1E-4);
  EXPECT_NEAR(node.dval, 2.04, 1E-2);
}
