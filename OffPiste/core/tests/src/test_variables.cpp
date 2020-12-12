/* googletest header files */
#include "gtest/gtest.h"

/* source / header files */
#include "Variable.hpp"
#include "test_vars.h"

// add an AD shortcut for brevity
using namespace OP;

void OffPiste_testcheck() { printf("Starting Off Piste tests...\n"); }

TEST(Init, float) {
  float value = 1.8f;
  Variable a(value, 1.0);

  EXPECT_NEAR(a.val, 1.8, 1E-6);
  EXPECT_NEAR(a.dval, 1.0, 1E-6);
  EXPECT_NEAR(a.grad, 1.0, 1E-6);
}
