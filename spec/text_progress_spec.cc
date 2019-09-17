#include "cctest/listener/text_progress.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_case.h"
#include "cctest/core/test_suite.h"
#include "cctest/except/assertion_error.h"
#include "gtest/gtest.h"
#include <sstream>

using namespace cctest;

namespace {

struct TextProgressSpec : testing::Test {
protected:
  TextProgressSpec() : progress(ss) {
    result.addListener(progress);
  }

  void run(cctest::Test& test) {
    result.runRootTest(test);
  }

  void assertOutput(const char* output) {
    ASSERT_EQ(ss.str(), output);
  }

protected:
  TestResult result;
  std::ostringstream ss;
  TextProgress progress;
};

TEST_F(TextProgressSpec, single_test_case_is_successful) {
  TestCase test;
  run(test);
  assertOutput("starting...\n*\nend.\n");
}

TEST_F(TextProgressSpec, all_of_test_cases_are_successful) {
  TestSuite suite;
  suite.add(new TestCase);
  suite.add(new TestCase);

  run(suite);
  assertOutput("starting...\n**\nend.\n");
}

namespace {
  struct FailureOnRunningTest : TestCase {
  private:
    void runTest() override {
      throw AssertionError("product.cc:57", "expected value == 2, but got 3");
    }
  };
}

TEST_F(TextProgressSpec, contains_failed_test_case) {
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

TEST_F(TextProgressSpec, contains_error_test_case) {
  TestSuite suite;
  suite.add(new TestCase);
  suite.add(new ErrorOnRunningTest);

  run(suite);
  assertOutput("starting...\n**E\nend.\n");
}

} // namespace
