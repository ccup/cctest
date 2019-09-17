#include "gtest/gtest.h"
#include "cctest/core/test_case.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_suite.h"
#include "cctest/listener/test_collector.h"

using namespace cctest;

namespace {

struct TestSuiteResult : testing::Test {
protected:
  void run(cctest::Test& test) {
    test.run(result);
  }

  using SingleTestFactory = cctest::Test*(*)();

  void example(SingleTestFactory factory) {
    suite.add(factory());
    suite.add(factory());

    run(suite);
    ASSERT_EQ(2, collector.runCount());
  }

private:
  void SetUp() override {
    result.addListener(collector);
  }

protected:
  TestCollector collector;
  TestResult result;
  TestSuite suite;
};

cctest::Test* singleCase() {
  return new TestCase;
}

TEST_F(TestSuiteResult, package_test_case_into_test_suite) {
  example(singleCase);
}

cctest::Test* singleSuite() {
  TestSuite* suite = new TestSuite;
  suite->add(singleCase());
  return suite;
}

TEST_F(TestSuiteResult, package_sub_suite_into_test_suite) {
  example(singleSuite);
}

TEST(NamedTestSuite, named_test_suite) {
  TestSuite suite("test suite");
  ASSERT_EQ("test suite", suite.getName());
}


} // namespace
