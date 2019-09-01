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

  void run(cctest::Test& test) {
    test.run();
  }
};

TEST_F(TestCaseSpec, full_lifecycle_for_test_case) {
  WasRun test;
  run(test);
  ASSERT_EQ("[setUp][runTest][tearDown]", result);
}

TEST(NamedTestCase, named_test_case) {
  TestCase test("test case");
  ASSERT_EQ("test case", test.getName());
}


} // namespace
