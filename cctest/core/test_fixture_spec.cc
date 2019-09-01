#include "gtest/gtest.h"
#include "cctest/core/test_case.h"
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

struct TestFixtureSpec : testing::Test {
protected:
  void run(cctest::Test& test) {
    TestResult dummy;
    test.run(dummy);
  }
};

TEST_F(TestFixtureSpec, make_sure_be_succ) {
  WasSucc test;
  run(test);
  ASSERT_TRUE(test.succ());
}

} // namespace




