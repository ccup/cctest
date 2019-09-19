#include "cctest/cctest.h"
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

FIXTURE(TestCaseSpec) {
  TEST("full lifecycle") {
    WasRun test;
    run(test);
    test.expectResult("[setUp][runTest][tearDown]");
  }

  TEST("named test case") {
    TestCase test("test case");
    ASSERT_EQ("test case", test.getName());
  }
};

} // namespace
