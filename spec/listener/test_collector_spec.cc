#include "gtest/gtest.h"
#include "cctest/core/test_case.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_suite.h"
#include "cctest/except/assertion_error.h"
#include "cctest/listener/collector/test_collector.h"

using namespace cctest;

namespace {

struct TestCollectorSpec : testing::Test {
protected:
  void run(cctest::Test& test) {
    test.run(result);
  }

private:
  void SetUp() override {
    result.addListener(collector);
  }

protected:
  TestCollector collector;
  TestResult result;
};

TEST_F(TestCollectorSpec, run_one_simple_test) {
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


TEST_F(TestCollectorSpec, throw_assertion_error_on_run_test) {
  FailureOnRunningTest test;
  run(test);

  ASSERT_EQ(1, collector.failCount());
}

struct ErrorOnRunningTest : TestCase {
 void runTest() override {
    throw std::exception();
  }
};

TEST_F(TestCollectorSpec, throw_std_exception_on_run_test) {
  ErrorOnRunningTest test;
  run(test);
  ASSERT_EQ(1, collector.errorCount());
}

TEST_F(TestCollectorSpec, count_test_cases_from_collector) {
  TestSuite suite;
  suite.add(new TestCase);
  suite.add(new FailureOnRunningTest);

  run(suite);

  ASSERT_EQ(2, collector.runCount());
  ASSERT_EQ(1, collector.passCount());
  ASSERT_EQ(1, collector.failCount());
}

} // namespace

