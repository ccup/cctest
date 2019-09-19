#include "cctest/cctest.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_suite.h"
#include "cctest/listener/text/text_progress.h"
#include <sstream>

using namespace cctest;

namespace {

FIXTURE(TextProgressSpec) {
  TestResult result;
  std::ostringstream ss;
  TextProgress progress;

  TextProgressSpec() : progress(ss) {
    result.addListener(progress);
  }

  void run(cctest::Test& test) {
    result.runRootTest(test);
  }

  void assertOutput(const char* output) {
    ASSERT_EQ(ss.str(), output);
  }

  TEST("single test case is successful") {
    TestCase test;
    run(test);
    assertOutput("starting...\n*\nend.\n");
  }

  TEST("all of test cases are successful") {
    TestSuite suite;
    suite.add(new TestCase);
    suite.add(new TestCase);

    run(suite);
    assertOutput("starting...\n**\nend.\n");
  }

  struct FailureOnRunningTest : TestCase {
  private:
    void runTest() override {
      throw AssertionError("product.cc:57", "expected value == 2, but got 3");
    }
  };

  TEST("contains failed test case") {
    TestSuite suite;
    suite.add(new TestCase);
    suite.add(new FailureOnRunningTest);

    run(suite);
    assertOutput("starting...\n**F\nend.\n");
  }

  struct ErrorOnRunningTest : TestCase {
    void runTest() override {
      throw std::exception();
    }
  };

  TEST("contains error test case") {
    TestSuite suite;
    suite.add(new TestCase);
    suite.add(new ErrorOnRunningTest);

    run(suite);
    assertOutput("starting...\n**E\nend.\n");
  }
};

} // namespace
