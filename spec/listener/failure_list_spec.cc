#include "cctest/cctest.h"
#include "cctest/core/test_result.h"
#include "cctest/listener/collector/failure_list.h"

using namespace cctest;

namespace {

FIXTURE(FailureListerSpec) {
  FailureList list;
  TestResult result;

  SETUP {
    result.addListener(list);
  }

  void run(Test& test) {
    test.run(result);
  }

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

  TEST("extract except msg on running test failed") {
    FailureOnRunningTest test;
    run(test);

    list.foreach([&test](const TestFailure& fail) {
      ASSERT_TRUE(fail.isFailure());
      ASSERT_EQ(test.expectMsg(), fail.getExceptionMsg());
    });
  }
};

} // namespace
