/* googletest header files */
#include "gtest/gtest.h"

/* source / header files */
#include "BinaryOperator.hpp"
#include "Function.cpp"
#include "Function.hpp"
#include "Node.cpp"
#include "Node.hpp"
#include "UnaryOperator.hpp"
#include "Variable.hpp"
#include "test_vars.h"

// add an AD shortcut for brevity
using namespace OP;

/**
This file tests that the backwards and forwards mode generate the same results.
*/

//--------------------------- Test Operators ----------------------------------
//-----------------------------------------------------------------------------

void check_jacobians_equal(Mat a, Mat b) {
  ASSERT_EQ(a.size(), b.size());  // check same number of rows
  for (int i = 0; i < a.size(); i++) {
    ASSERT_EQ(a.at(i).size(), b.at(i).size());  // check same number of columns
    for (int j = 0; j < a.at(i).size(); j++) {
      // check element i,j is same for each matrix
      EXPECT_NEAR(a.at(i).at(j), b.at(i).at(j), 1E-2);
    }
  }
}

//--------------------------- Binary Functions --------------------------------
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
  // f.zero_grad();
  // u.backward();
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
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  Mat correct_answer = {{1.5, -2.0}};
  ASSERT_EQ(jacob_f, correct_answer);
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
  // f.zero_grad();
  // u.backward();
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
  // f.zero_grad();
  // u.backward();
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
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

TEST(Operators, Comparison) {
  // Init
  Node a(2.0);
  Node b(3.0);
  Node c(3.0);

  // Validate
  ASSERT_EQ(a > b, false);
  ASSERT_EQ(a < b, true);
  ASSERT_EQ(a == b, false);
  ASSERT_EQ(c == b, true);
  ASSERT_EQ(a != b, true);
  ASSERT_EQ(a >= b, false);
  ASSERT_EQ(a <= b, true);
  ASSERT_EQ(b <= c, true);
}

//--------------------- Negate, Sqrt, Exponent, Log ---------------------------
TEST(Operators, Negate) {
  // Init
  Variable a(2.0, 1.5);

  // Negate
  Expression u = -a;
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

TEST(Operators, Sqrt) {
  // Init
  Variable a(2.0, 1.5);

  // Sqrt
  Expression u = sqrt(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

TEST(Operators, Exponent) {
  // Init
  Variable a(2.0, 1.5);

  // Exponent
  Expression u = exp(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

TEST(Operators, Logarithm) {
  // Init
  Variable a(2.0, 1.5);

  // Logarithm
  Expression u = log(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

//--------------------------- Trigonometric Functions -------------------------
TEST(Operators, Sine) {
  // Init
  Variable a(0.9, 0.2);

  // Sine
  Expression u = sin(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  ASSERT_EQ(jacob_f, jacob_b);
}

TEST(Operators, Cosine) {
  // Init
  Variable a(0.9, 0.2);

  // Cosine
  Expression u = cos(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  check_jacobians_equal(jacob_f, jacob_b);
}

TEST(Operators, Tangent) {
  // Init
  Variable a(0.9, 0.2);

  // Tangent
  Expression u = tan(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  check_jacobians_equal(jacob_f, jacob_b);
}

TEST(Operators, Asin) {
  // Init
  Variable a(0.9, 0.2);

  // Asin
  Expression u = asin(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  check_jacobians_equal(jacob_f, jacob_b);
}

TEST(Operators, Acos) {
  // Init
  Variable a(0.9, 0.2);

  // Acos
  Expression u = acos(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  check_jacobians_equal(jacob_f, jacob_b);
}

TEST(Operators, Atan) {
  // Init
  Variable a(0.9, 0.2);

  // Atan
  Expression u = atan(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  check_jacobians_equal(jacob_f, jacob_b);
}

TEST(Operators, Sinh) {
  // Init
  Variable a(0.9, 0.2);

  // Sinh
  Expression u = sinh(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  check_jacobians_equal(jacob_f, jacob_b);
}

TEST(Operators, Cosh) {
  // Init
  Variable a(0.9, 0.2);

  // Cosh
  Expression u = cosh(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  check_jacobians_equal(jacob_f, jacob_b);
}

TEST(Operators, Tanh) {
  // Init
  Variable a(0.9, 0.2);

  // Tanh
  Expression u = tanh(a);
  Function f({a}, {u});

  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  check_jacobians_equal(jacob_f, jacob_b);
}

//--------------------------- Test Functions ----------------------------------
//-----------------------------------------------------------------------------
TEST(Functions, ForwardDerivative) {
  // Init
  Variable a(0.9, 0.2);

  // Sine
  Expression u = sin(a);
  Function f({a}, {u});
  Vec seeds = {1};
  f.set_seed(seeds);

  float der = f.forward_derivative(u, a);
  EXPECT_NEAR(der, 0.6216, 1E-4);
}

//--------------------------- Test Complex Function ---------------------------
//-----------------------------------------------------------------------------
TEST(Operators, ComplexFunction) {
  // Init
  Variable a(0.9, 0.2);
  Variable b(1.2, 0.02);
  Variable c(10.0, 2.3);

  // Sine
  Expression u = sin(a) + b * exp(c) + pow(b, 2);
  Function f({a, b, c}, {u});
  Vec seeds = {1, 2, 3, 4};

  // should throw an error because there are 4 seeds but only 3 inputs
  EXPECT_THROW(f.set_seed(seeds), std::runtime_error);

  // try again with correct seed length
  seeds = {1, 2, 3};
  f.set_seed(seeds);
  
  // Evaluate Forward Jacobian
  Vec result_f_mode = f.evaluate();
  Mat jacob_f = f.forward_jacobian();
  // Evaluate Backward Jacobian
  // f.zero_grad();
  // u.backward();
  Mat jacob_b = f.backward_jacobian();

  // Validate
  Mat correct_answer = {{0.62160998582839966, 44057.73046875, 79295.2734375}};
  check_jacobians_equal(jacob_f, jacob_b);
  check_jacobians_equal(jacob_f, correct_answer);
}