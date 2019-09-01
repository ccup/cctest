#include "gtest/gtest.h"
#include "cctest/core/test_method.h"

using namespace cctest;

namespace {

bool wasRun = false;
struct WasRun {
  void testMethod() {
    wasRun = true;
  }
};

TEST(TestMethodSpec, make_sure_test_method_was_ran) {
  ASSERT_FALSE(wasRun);

  TestMethod<WasRun> method(&WasRun::testMethod);
  method.run();
  ASSERT_TRUE(wasRun);
}

} // namespace
