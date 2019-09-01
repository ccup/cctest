#include "gtest/gtest.h"
#include "cctest/core/test_case.h"
#include "cctest/core/test_suite.h"

using namespace cctest;

namespace {

int numOfRuns = 0;

struct FooTest : TestCase {
private:
  void runTest() override {
    numOfRuns++;
  }
};

struct TestSuiteSpec : testing::Test {
protected:
  TestSuiteSpec() {
    numOfRuns = 0;
  }

protected:
  TestSuite suite;
};

TEST_F(TestSuiteSpec, package_test_case_into_test_suite) {
  suite.add(new FooTest);
  suite.add(new FooTest);

  suite.run();
  ASSERT_EQ(2, numOfRuns);
}

TEST_F(TestSuiteSpec, package_sub_suite_into_test_suite) {
  TestSuite* sub = new TestSuite;

  sub->add(new FooTest);
  sub->add(new FooTest);

  suite.add(sub);

  suite.run();
  ASSERT_EQ(2, numOfRuns);
}


} // namespace
