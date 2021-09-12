#include "cctest/cctest.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_suite.h"
#include "cctest/listener/collector/test_collector.h"

using namespace cctest;

namespace {

FIXTURE(TestCollectorSpec) {
  TestCollector collector;
  TestResult result;

  BEFORE {
    result.addListener(collector);
  }

  void run(cctest::Test& test) {
    test.run(result);
  }

  TEST("run one simple test") {
    TestCase test;
    run(test);
    ASSERT_EQ(1, collector.runCount());
  }

  struct FailureOnRunningTest : TestCase {
  private:
    void runTest() override {
      throw AssertionError("product.cc:57", "expected value == 2, but got 3");
    }
  };


  TEST("throw assertion error on run test") {
    FailureOnRunningTest test;
    run(test);

    ASSERT_EQ(1, collector.failCount());
  }

  struct ErrorOnRunningTest : TestCase {
  void runTest() override {
      throw std::exception();
    }
  };

  TEST("throw std exception on run test") {
    ErrorOnRunningTest test;
    run(test);
    ASSERT_EQ(1, collector.errorCount());
  }

  TEST("count test cases from collector") {
    TestSuite suite;
    suite.add(new TestCase);
    suite.add(new FailureOnRunningTest);

    run(suite);

    ASSERT_EQ(2, collector.runCount());
    ASSERT_EQ(1, collector.passCount());
    ASSERT_EQ(1, collector.failCount());
  }
};

} // namespace

