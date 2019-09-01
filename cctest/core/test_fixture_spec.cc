#include "gtest/gtest.h"
#include "cctest/core/test_case.h"
#include "cctest/core/test_method.h"
#include "cctest/core/test_fixture.h"

using namespace cctest;

namespace {

bool wasSucc = false;

struct WasSucc : TestFixture {
  void testMethod() {
    wasSucc = true;
  }
};

struct TestFixtureSpec : testing::Test {
protected:
  TestFixtureSpec() {
    wasSucc = false;
  }

  void run(TestCase& test) {
    test.run();
  }
};

TEST_F(TestFixtureSpec, make_sure_be_succ) {
  TestMethod<WasSucc> test = &WasSucc::testMethod;

  ASSERT_FALSE(wasSucc);
  run(test);
  ASSERT_TRUE(wasSucc);
}

} // namespace




