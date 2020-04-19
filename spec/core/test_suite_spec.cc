#include "cctest/cctest.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_suite.h"
#include "cctest/listener/collector/test_collector.h"

using namespace cctest;

namespace {

FIXTURE(TestSuiteResult) {
  TestCollector collector;
  TestResult result;
  TestSuite suite;

  BEFORE {
    result.addListener(collector);
  }

  void run(Test& test) {
    test.run(result);
  }

  using SingleTestFactory = Test*(*)();

  void example(SingleTestFactory factory) {
    suite.add(factory());
    suite.add(factory());

    run(suite);
    ASSERT_EQ(2, collector.runCount());
  }

  static Test* singleCase() {
    return new TestCase;
  }

  TEST("package test case into test suite") {
    example(singleCase);
  }

  static Test* singleSuite() {
    TestSuite* suite = new TestSuite;
    suite->add(singleCase());
    return suite;
  }

  TEST("package sub suite into test suite") {
    example(singleSuite);
  }

  TEST("named test suite") {
    TestSuite suite("test suite");
    ASSERT_EQ("test suite", suite.getName());
  }
};

} // namespace
