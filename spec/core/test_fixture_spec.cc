#include "cctest/cctest.h"
#include "cctest/core/test_result.h"

using namespace cctest;

namespace {

struct WasSucc : TestCase {
  bool succ() const {
    return wasSucc;
  }

private:
  void runTest() override {
    wasSucc = true;
  }

private:
  bool wasSucc = false;
};

FIXTURE(TestFixtureSpec) {
  void run(cctest::Test& test) {
    TestResult dummy;
    test.run(dummy);
  }

  TEST("make sure be succ") {
    WasSucc test;
    run(test);
    ASSERT_TRUE(test.succ());
  }
};

} // namespace




