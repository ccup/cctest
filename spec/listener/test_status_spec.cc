#include "cctest/cctest.h"
#include "cctest/listener/collector/test_status.h"
#include "cctest/core/test_result.h"

using namespace cctest;

namespace {

FIXTURE(TestStatusSpec) {
  TestResult result;
  TestStatus status;

  BEFORE {
    result.addListener(status);
  }

  void run(cctest::Test& test) {
    test.run(result);
  }

  TEST("should be successful") {
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

  TEST("should be failed") {
    FailureOnRunningTest test;
    run(test);
    ASSERT_FALSE(status.successful());
  }
};

} // namespace
