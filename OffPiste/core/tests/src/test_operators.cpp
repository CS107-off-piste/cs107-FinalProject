/* system header files */
#include <stdio.h>
#include <stdlib.h>

#include <string>
/* googletest header files */
#include "gtest/gtest.h"

/* source / header files */
#include "OffPiste.cpp"
#include "test_vars.h"

// add an AD shortcut for brevity
typedef AutoDiff AD;

void OffPiste_testcheck() { printf("Starting Off Piste tests...\n"); }
TEST(Equal, float) {
  float value = 1.8f;
  EXPECT_EQ(equal(value, 1.8f), true);
}

TEST(Init, float) {
  float value = 1.8f;
  AutoDiff x(value);
  EXPECT_NEAR(x.val(), 1.8, 1E-6);
}

TEST(Getter, int) {
  int value = 3;
  int seed = 7;
  AutoDiff x1(value, seed);

  /* test getters */
  EXPECT_NEAR(x1.val(), value, 1E-10);  // note: EXECT_EQ used only for integers
  EXPECT_NEAR(x1.dval(), seed, 1E-10);
}

TEST(Getter, float) {
  float value = 9.8f;
  float seed = 1.0f;
  AutoDiff x(value, seed);

  /* test getters */
  EXPECT_NEAR(x.val(), value, DTOL);
  EXPECT_NEAR(x.dval(), seed, DTOL);
}

TEST(Getter, double) {
  double value = 9.8;
  double seed = 1.0;
  AutoDiff x(value, seed);

  /* test getters */
  EXPECT_NEAR(x.val(), value, DTOL);
  EXPECT_NEAR(x.dval(), seed, DTOL);
}

TEST(Setter, int) {
  int value = 2;
  int seed = 1;
  AutoDiff x(value, seed);

  /* test getters */
  x.setval(3);
  EXPECT_NEAR(x.val(), 3, 1E-6);
}

TEST(Setter, float) {
  float value = 1.8f;
  float seed = 1.2f;
  AutoDiff x(value, seed);

  /* test getters */
  x.setval(3.3);
  EXPECT_NEAR(x.val(), 3.3, 1E-6);
}

TEST(Setter, double) {
  double value = 1.8;
  double seed = 1.2;
  AutoDiff x(value, seed);

  /* test getters */
  x.setval(3.3);
  EXPECT_NEAR(x.val(), 3.3, 1E-6);
}

TEST(Operators, Add_double) {
  double seed1 = 1.9;
  double seed2 = 4.4;

  AutoDiff x1(1.0, seed1);
  AutoDiff x2(2.0, seed2);

  /* add operator */
  AutoDiff c = x1 + x2;
  AutoDiff d = 2.0 + x1;
  AutoDiff e = x1 + 2.0;
  x1 += x2;
  x2 += 2.0;

  EXPECT_NEAR(c.val(), 3.0, 1E-6);
  EXPECT_NEAR(c.dval(), 6.3, 1E-6);
  EXPECT_NEAR(x1.val(), 3.0, 1E-6);
  EXPECT_NEAR(x1.dval(), 6.3, 1E-6);
  EXPECT_NEAR(d.val(), 3.0, 1E-6);
  EXPECT_NEAR(d.dval(), 1.9, 1E-6);
  EXPECT_NEAR(e.val(), 3.0, 1E-6);
  EXPECT_NEAR(e.dval(), 1.9, 1E-6);
  EXPECT_NEAR(x2.val(), 4.0, 1E-6);
  EXPECT_NEAR(x2.dval(), 4.4, 1E-6);
}

TEST(Operators, Sub_unary) {
  double seed1 = 1.9;

  AutoDiff x1(1.5, seed1);

  // negate x1
  AD c = -x1;

  // expect that value and derivative are negated
  EXPECT_NEAR(c.val(), -1.5, 1E-6);
  EXPECT_NEAR(c.dval(), -1.9, 1E-6);
}

TEST(Operators, Sub_double) {
  double seed1 = 1.9;
  double seed2 = 4.4;

  AutoDiff x1(1.0, seed1);
  AutoDiff x2(2.0, seed2);

  /* add operator */
  AutoDiff c = x1 - x2;
  AutoDiff d = x1 - 5.0;
  AutoDiff e = 5.0 - x1;
  x1 -= x2;
  x2 -= 2.0;

  EXPECT_NEAR(c.val(), -1.0, 1E-6);
  EXPECT_NEAR(c.dval(), -2.5, 1E-6);
  EXPECT_NEAR(d.val(), -4.0, 1E-6);
  EXPECT_NEAR(d.dval(), seed1, 1E-6);
  EXPECT_NEAR(x1.val(), -1.0, 1E-6);
  EXPECT_NEAR(x1.dval(), -2.5, 1E-6);
  EXPECT_NEAR(e.val(), 4.0, 1E-6);
  EXPECT_NEAR(e.dval(), -1.9, 1E-6);
  EXPECT_NEAR(x2.val(), 0.0, 1E-6);
  EXPECT_NEAR(x2.dval(), 4.4, 1E-6);
}

TEST(Operators, mul_double) {
  double seed1 = 1.9;
  double seed2 = 4.4;

  AutoDiff x1(1.0, seed1);
  AutoDiff x2(2.0, seed2);

  /* multiplication operator */
  AutoDiff c = x1 * x2;
  AutoDiff d = x1 * 5.0;
  AutoDiff e = 5.0 * x1;
  x1 *= x2;
  x2 *= 5.0;

  EXPECT_NEAR(c.val(), 2.0, 1E-6);
  EXPECT_NEAR(c.dval(), 8.2, 1E-6);
  EXPECT_NEAR(d.val(), 5, 1E-6);
  EXPECT_NEAR(d.dval(), seed1 * 5, 1E-6);
  EXPECT_NEAR(x1.val(), 2.0, 1E-6);
  EXPECT_NEAR(x1.dval(), 8.2, 1E-6);
  EXPECT_NEAR(e.val(), 5.0, 1E-6);
  EXPECT_NEAR(e.dval(), seed1 * 5, 1E-6);
  EXPECT_NEAR(x2.val(), 10.0, 1E-6);
  EXPECT_NEAR(x2.dval(), seed2 * 5, 1E-6);
}

TEST(Operators, div_double) {
  double seed1 = 1.9;
  double seed2 = 4.4;

  AutoDiff x1(1.0, seed1);
  AutoDiff x2(2.0, seed2);
  AutoDiff x3(0.0, seed2);
  /* division operator */
  try {
    x1 / x3;
  } catch (const char* msg) {
    EXPECT_EQ(msg, "Divide by zero");
  }

  try {
    x1 /= x3;
  } catch (const char* msg) {
    EXPECT_EQ(msg, "Divide by zero");
  }

  AutoDiff c = x1 / x2;

  AutoDiff d = x1 / 5.0;
  AutoDiff e = 5.0 / x2;

  x1 /= x2;
  x2 /= 2.0;
  EXPECT_NEAR(c.val(), 0.5, 1E-6);
  EXPECT_NEAR(c.dval(), -0.15, 1E-6);
  EXPECT_NEAR(d.val(), 1.0 / 5.0, 1E-6);
  EXPECT_NEAR(d.dval(), seed1 / 5, 1E-6);
  EXPECT_NEAR(e.val(), 5.0 / 2.0, 1E-6);
  EXPECT_NEAR(e.dval(), (-(5.0 * seed2)) / std::pow(2.0, 2), 1E-6);

  EXPECT_NEAR(x1.val(), 0.5, 1E-6);
  EXPECT_NEAR(x1.dval(), -0.15, 1E-6);
  EXPECT_NEAR(x2.val(), 1.0, 1E-6);
  EXPECT_NEAR(x2.dval(), 2.2, 1E-6);
}

TEST(Operators, pow_double) {
  double seed1 = 1.9;
  double seed2 = 4.4;

  AutoDiff x1(1.0, seed1);
  AutoDiff x2(2.0, seed2);

  AutoDiff y = x1 ^ 3;
  AutoDiff z = x1 ^ x2;
  AutoDiff k = 3 ^ x2;

  EXPECT_NEAR(y.val(), 1.0, 1E-6);
  EXPECT_NEAR(y.dval(), 5.7, 1E-6);
  EXPECT_NEAR(z.val(), 1.0, 1E-6);
  EXPECT_NEAR(z.dval(), 3.8, 1E-6);
  EXPECT_NEAR(k.val(), 9.0, 1E-6);
  EXPECT_NEAR(k.dval(), 43.505, 1E-3);
}

// test that sine operator computes correct value and derivative
TEST(Operators, sine) {
  double seed1 = 1.0;
  double seed2 = 2.0;

  // x1 has value of 2, and a derivative of 1.0
  AD x1(2.0, seed1);
  // x2 has value of 3, and a derivative of 2.0
  AD x2(3.0, seed2);

  // take sine of each one
  AD y1 = AD::sin(x1);
  AD y2 = AD::sin(x2);

  // for the function y = sin(x), we expect that
  //  -> y_value = sin(x_value)
  //  -> y_derivative = cos(x_value) * x_derivative

  // for our object x1, x_value = 2 and x_derivative = 1
  // so we expect to see y1 having a value of: sin(2) ≈ 0.9093
  EXPECT_NEAR(y1.val(), 0.9093, 1E-1);
  // and we expect a derivative of: cos(2) * 1 ≈ -0.4161
  EXPECT_NEAR(y1.dval(), -0.4161, 1E-1);

  // for our object x2, x_value = 3 and x_derivative = 2
  // so we expect to see y1 having a value of: sin(3) ≈ 0.1411
  EXPECT_NEAR(y2.val(), 0.1411, 1E-1);
  // and we expect a derivative of: cos(3) * 2 ≈ -1.97998
  EXPECT_NEAR(y2.dval(), -1.97998, 1E-1);
}

// test that cosine operator computes correct value and derivative
TEST(Operators, cosine) {
  double seed1 = 1.0;
  double seed2 = 2.0;

  // x1 has value of 2, and a derivative of 1.0
  AD x1(2.0, seed1);
  // x2 has value of 3, and a derivative of 2.0
  AD x2(3.0, seed2);

  // take cosine of each one
  AD y1 = AD::cos(x1);
  AD y2 = AD::cos(x2);

  // for the function y = cos(x), we expect that:
  //   -> y_value = cos(x_value)
  //   -> y_derivative = -1 * sin(x_value) * x_derivative

  // for our object x1, x_value = 2 and x_derivative = 1
  // so we expect to see y1 having a value of: cos(2) ≈ -0.4161
  EXPECT_NEAR(y1.val(), -0.4161, 1E-1);
  // and we expect a derivative of: -sin(2) * 1 ≈ -0.9093
  EXPECT_NEAR(y1.dval(), -0.9093, 1E-1);

  // for our object x2, x_value = 3 and x_derivative = 2
  // so we expect to see y1 having a value of: cos(3) ≈ -0.9900
  EXPECT_NEAR(y2.val(), -0.99, 1E-1);
  // and we expect a derivative of: -sin(3) * 2 ≈ -0.2822
  EXPECT_NEAR(y2.dval(), -0.2822, 1E-1);
}

// test that tangent operator computes correct value and derivative
TEST(Operators, tangent) {
  double seed1 = 1.0;
  double seed2 = 2.0;

  // x1 has value of 2, and a derivative of 1.0
  AD x1(2.0, seed1);
  // x2 has value of 3, and a derivative of 2.0
  AD x2(3.0, seed2);

  // take tangent of each one
  AD y1 = AD::tan(x1);
  AD y2 = AD::tan(x2);

  // for the function y = tan(x), we expect that:
  //   -> y_value = tan(x_value)
  //   -> y_derivative = (sec(x_value))^2 * x_derivative
  // Since sec(x) = 1 / cos(x), this is:
  // (1 / cos(x_value))^2 * x_derivative

  // for our object x1, x_value = 2 and x_derivative = 1
  // so we expect to see y1 having a value of: tan(2) ≈ -2.1850
  EXPECT_NEAR(y1.val(), -2.1850, 1E-1);
  // and we expect a derivative of: (sec(2)^2) * 1 ≈ 5.7743
  EXPECT_NEAR(y1.dval(), 5.7744, 1E-1);

  // for our object x2, x_value = 3 and x_derivative = 2
  // so we expect to see y1 having a value of: tan(3) ≈ -0.1425
  EXPECT_NEAR(y2.val(), -0.1425, 1E-1);
  // and we expect a derivative of: (sec(3)^2) * 2 ≈ 2.0406
  EXPECT_NEAR(y2.dval(), 2.0406, 1E-1);
}

// test that exponential operator computes correct value and derivative
TEST(Operators, exp) {
  double seed1 = 1.0;
  double seed2 = 2.0;

  // x1 has value of 2, and a derivative of 1.0
  AD x1(2.0, seed1);
  // x2 has value of 3, and a derivative of 2.0
  AD x2(3.0, seed2);

  // take exp() of each one
  AD y1 = AD::exp(x1);
  AD y2 = AD::exp(x2);

  // for the function y = exp(x), we expect that
  //  -> y_value = exp(x_value)
  //  -> y_derivative = exp(x_value) * x_derivative

  // for our object x1, x_value = 2 and x_derivative = 1
  // so we expect to see y1 having a value of: exp(2) ≈ 7.38905
  EXPECT_NEAR(y1.val(), 7.38905, 1E-1);
  // and we expect a derivative of: exp(2) * 1 ≈ 7.38905
  EXPECT_NEAR(y1.dval(), 7.38905, 1E-1);

  // for our object x2, x_value = 3 and x_derivative = 2
  // so we expect to see y1 having a value of: exp(3) ≈ 20.08553
  EXPECT_NEAR(y2.val(), 20.08553, 1E-1);
  // and we expect a derivative of: exp(3) * 2 ≈ 40.17107
  EXPECT_NEAR(y2.dval(), 40.17107, 1E-1);
}
