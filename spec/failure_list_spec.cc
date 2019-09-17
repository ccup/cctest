#include "gtest/gtest.h"
#include "cctest/core/test_case.h"
#include "cctest/core/test_result.h"
#include "cctest/except/assertion_error.h"
#include "cctest/listener/collector/failure_list.h"

using namespace cctest;

namespace {

struct FailureListerSpec : testing::Test {
protected:
  void run(cctest::Test& test) {
    test.run(result);
  }

private:
  void SetUp() override {
    result.addListener(list);
  }

protected:
  FailureList list;
  TestResult result;
};

struct FailureOnRunningTest : TestCase {
  const char* expectMsg() const {
    return "assertion fail in the runTest\n"
            "product.cc:57\n"
            "expected value == 2, but got 3";
  }

private:
  void runTest() override {
    throw AssertionError("product.cc:57", "expected value == 2, but got 3");
  }
};

TEST_F(FailureListerSpec, extract_except_msg_on_running_test_failed) {
  FailureOnRunningTest test;
  run(test);

  list.foreach([&test](const TestFailure& fail) {
    ASSERT_TRUE(fail.isFailure());
    ASSERT_EQ(test.expectMsg(), fail.getExceptionMsg());
  });
}

} // namespace
