#include "cctest/listener/collector/test_status.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_case.h"
#include "cctest/except/assertion_error.h"
#include "gtest/gtest.h"

using namespace cctest;

namespace {

struct TestStatusSpec : testing::Test {
protected:
  void run(cctest::Test& test) {
    test.run(result);
  }

private:
  void SetUp() override {
    result.addListener(status);
  }

protected:
  TestResult result;
  TestStatus status;
};

TEST_F(TestStatusSpec, should_be_successful) {
  TestCase test;
  run(test);
  ASSERT_TRUE(status.successful());
}

struct FailureOnRunningTest : TestCase {
private:
  void runTest() override {
    throw AssertionError("product.cc:57", "expected value == 2, but got 3");
  }
};

TEST_F(TestStatusSpec, should_be_failed) {
  FailureOnRunningTest test;
  run(test);
  ASSERT_FALSE(status.successful());
}

} // namespace