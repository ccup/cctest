#include "gtest/gtest.h"
#include "cctest/core/test_method.h"

using namespace cctest;

namespace {


std::string result;

struct WasRun {
  void setUp() {
    result += "[setUp]";
  }

  void testMethod() {
    result += "[runTest]";
  }

  void tearDown() {
    result += "[tearDown]";
  }
};

TEST(TestMethodSpec, make_sure_the_invoked_order_is_ok) {
  TestMethod<WasRun> method = &WasRun::testMethod;
  method.run();
  ASSERT_EQ("[setUp][runTest][tearDown]", result);
}

} // namespace
