#include "gtest/gtest.h"
#include "cctest/core/assertion_error.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_case.h"

using namespace cctest;

namespace {

struct TestResultSpec : testing::Test {
protected:
  void run(cctest::Test& test) {
    test.run(result);
  }

protected:
  TestResult result;
};

struct FailureOnRunTest : TestCase {
private:
  void runTest() override {
    throw AssertionError("product.cc:57", "expected value == 2, but got 3");
  }
};

TEST_F(TestResultSpec, throw_assertion_error_on_run_test) {
  FailureOnRunTest test;
  run(test);

  ASSERT_EQ(1, result.failCount());
}

struct FailureOnSetUp : TestCase {
  bool wasRun = false;

private:
  void setUp() override {
    throw AssertionError("product.cc:57", "expected value == 2, but got 3");
  }

  void runTest() override {
    wasRun = true;
  }
};

TEST_F(TestResultSpec, throw_assertion_error_on_setup) {
  FailureOnSetUp test;
  run(test);

  ASSERT_EQ(1, result.failCount());
  ASSERT_FALSE(test.wasRun);
}

} // namespace
