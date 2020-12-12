/* googletest header files */
#include "gtest/gtest.h"

/* source / header files */
#include "BinaryOperator.hpp"
#include "Function.hpp"
#include "Function.cpp"
#include "Node.cpp"
#include "Variable.hpp"
#include "test_vars.h"

// add an AD shortcut for brevity
using namespace OP;

TEST(Operators, Add) {
  // Init
  Variable a(2.0, 1.5);
  Variable b(3.0, 2.0);

  // Add
  Expression u = a + b;
  Function f({a, b}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();

  // Evaluate Backward Jacobian
  f.zero_grad();
  u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

TEST(Operators, Subtract) {
  // Init
  Variable a(2.0, 1.5);
  Variable b(3.0, 2.0);

  // Subtract
  Expression u = a - b;
  Function f({a, b}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();

  // Evaluate Backward Jacobian
  f.zero_grad();
  u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

TEST(Operators, Multiply) {
  // Init
  Variable a(2.0, 1.5);
  Variable b(3.0, 2.0);

  // Multiply
  Expression u = a * b;
  Function f({a, b}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();

  // Evaluate Backward Jacobian
  f.zero_grad();
  u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

TEST(Operators, Divide) {
  // Init
  Variable a(2.0, 1.5);
  Variable b(3.0, 2.0);

  // Divide
  Expression u = a / b;
  Function f({a, b}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();

  // Evaluate Backward Jacobian
  f.zero_grad();
  u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

TEST(Operators, Power) {
  // Init
  Variable a(2.0, 1.5);
  Variable b(3.0, 2.0);

  // Power
  Expression u = pow(a, b);
  Function f({a, b}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();

  // Evaluate Backward Jacobian
  f.zero_grad();
  u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}
