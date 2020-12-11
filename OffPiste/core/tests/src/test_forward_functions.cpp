/* googletest header files */
#include "gtest/gtest.h"

/* source / header files */
#include "ForwardFunctions.hpp"
#include "Node.hpp"
#include "Variable.hpp"
#include "test_vars.h"

// add an AD shortcut for brevity
using namespace OP;

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
  Node child1(2.0, 1.5);
  Node child2(3.0, 2.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Divide
  div_forward(node);

  // Validate
  EXPECT_NEAR(node.val, 0.6667, 1E-4);
  EXPECT_NEAR(node.dval, 0.06, 1E-2);
}

TEST(ForwardFunctions, Power) {
  // Init
  Node node;
  Node child1(2.0, 1.5);
  Node child2(3.0, 2.0);
  node._children.push_back(&child1);
  node._children.push_back(&child2);

  // Power
  pow_forward(node);

  // Validate
  EXPECT_NEAR(node.val, 8.0, 1E-6);
  EXPECT_NEAR(node.dval, 29.09, 1E-2);
}
