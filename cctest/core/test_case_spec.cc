#include "gtest/gtest.h"
#include "cctest/core/test_case.h"
#include "cctest/core/test_result.h"

using namespace cctest;

namespace {

struct WasRun : TestCase {
  void expectResult(const std::string& expected) {
    ASSERT_EQ(expected, result);
  }

private:
  void setUp() override {
    result += "[setUp]";
  }

  void runTest() override {
    result += "[runTest]";
  }

  void tearDown() override {
    result += "[tearDown]";
  }

private:
  std::string result;
};

void run(cctest::Test& test) {
  TestResult dummy;
  test.run(dummy);
}

TEST(TestLifecycle, full_lifecycle) {
  WasRun test;
  run(test);
  test.expectResult("[setUp][runTest][tearDown]");
}

TEST(NamedTestCase, named_test_case) {
  TestCase test("test case");
  ASSERT_EQ("test case", test.getName());
}

struct TestCaseResult : testing::Test {
protected:
  void run(cctest::Test& test) {
    test.run(result);
  }

protected:
  TestResult result;
};

TEST_F(TestCaseResult, run_one_simple_test) {
  TestCase test;
  run(test);
  ASSERT_EQ(1, result.runCount());
}

} // namespace
