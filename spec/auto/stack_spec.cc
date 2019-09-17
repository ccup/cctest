#define GTEST_DONT_DEFINE_TEST 1
#include <gtest/gtest.h>
#include "cctest/cctest.h"
#include <stack>

using namespace cctest;

namespace {

FIXTURE(StackSpec) {
  std::stack<int> v;

  SETUP {
    v.push(1);
    v.push(2);
  }

  TEST("apply pop 0 time") {
    ASSERT_EQ(2, v.top());
  }

  TEST("apply pop 1 time") {
    v.pop();
    ASSERT_EQ(1, v.top());
  }

  TEST("apply pop 2 times") {
    v.pop();
    v.pop();
    ASSERT_TRUE(v.empty());
  }
};

} // namespace
