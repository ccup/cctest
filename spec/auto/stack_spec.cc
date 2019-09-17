#include "cctest/auto/auto_test_method.h"
#include "cctest/auto/auto_test_fixture.h"
#include <gtest/gtest.h>
#include <stack>


using namespace cctest;

namespace {

struct StackSpec;
static AutoTestFixture<StackSpec> suite1;

struct StackSpec : TestFixture {
  std::stack<int> v;

  void setUp() override {
    v.push(1);
    v.push(2);
  }

  void test1() {
    ASSERT_EQ(2, v.top());
  }

  AutoTestMethod m1{1, "apply pop 0 time", &StackSpec::test1};

  void test2() {
    v.pop();
    ASSERT_EQ(1, v.top());
  }

  AutoTestMethod m2{2, "apply pop 1 time", &StackSpec::test2};

  void test3() {
    v.pop();
    v.pop();
    ASSERT_TRUE(v.empty());
  }

  AutoTestMethod m3{3, "apply pop 2 times", &StackSpec::test3};
};

} // namespace
