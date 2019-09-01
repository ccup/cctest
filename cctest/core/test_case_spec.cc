#include "gtest/gtest.h"
#include "cctest/core/test_case.h"

using namespace cctest;

namespace {

std::string result;

struct WasRun : TestCase {
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
};

struct TestCaseSpec : testing::Test {
protected:
  TestCaseSpec() {
    result = "";
  }

  void run(TestCase& test) {
    test.run();
  }
};

TEST_F(TestCaseSpec, make_sure_be_succ) {
  WasRun test;
  run(test);
  ASSERT_EQ("[setUp][runTest][tearDown]", result);
}

} // namespace
