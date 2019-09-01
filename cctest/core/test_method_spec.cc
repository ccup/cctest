#include "gtest/gtest.h"
#include "cctest/core/test_method.h"

using namespace cctest;

namespace {

bool wasSetUp = false;
bool wasRun = false;
bool wasTearDown = false;

struct WasRun {
  void setUp() {
    wasSetUp = true;
  }

  void tearDown() {
    wasTearDown = true;
  }

  void testMethod() {
    wasRun = true;
  }
};

struct TestMethodSpec : testing::Test {
protected:
  void makeSure(const bool& invoked) {
    ASSERT_FALSE(invoked);
    method.run();
    ASSERT_TRUE(invoked);
  }

private:
  void SetUp() override {
    wasSetUp = false;
    wasRun = false;
    wasTearDown = false;
  }

protected:
  TestMethod<WasRun> method = &WasRun::testMethod;
};

TEST_F(TestMethodSpec, make_sure_test_method_was_ran) {
  makeSure(wasRun);
}

TEST_F(TestMethodSpec, make_sure_setup_was_ran) {
  makeSure(wasSetUp);
}

TEST_F(TestMethodSpec, make_sure_teardown_was_ran) {
  makeSure(wasTearDown);
}

} // namespace
