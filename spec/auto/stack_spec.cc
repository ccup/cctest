#include "cctest/core/test_fixture.h"
#include "cctest/core/test_method.h"
#include "cctest/core/test_suite.h"
#include "cctest/core/test_result.h"
#include "cctest/listener/text/text_progress.h"
#include "gtest/gtest.h"
#include <stack>

using namespace cctest;

namespace {

struct StackSpec : TestFixture {
  std::stack<int> s;

  void setUp() override {
    s.push(1);
    s.push(2);
  }

  void apply_pop_0_time() {
    ASSERT_EQ(2, s.top());
  }

  void apply_pop_1_time() {
    s.pop();
    ASSERT_EQ(1, s.top());
  }

  void apply_pop_2_times() {
    s.pop();
    s.pop();
    ASSERT_TRUE(s.empty());
  }
};

struct ManualRegisterSpec : testing::Test {
protected:
  ManualRegisterSpec() : progress(ss) {
    result.addListener(progress);
  }

  void run(::Test& test) {
    result.runRootTest(test);
  }

  void assertOutput(const char* output) {
    ASSERT_EQ(ss.str(), output);
  }

protected:
  std::ostringstream ss;
  TestResult result;
  TextProgress progress;
};

TEST_F(ManualRegisterSpec, manually_registering_test_cases) {
  TestSuite suite("StackSpec");
  suite.add(new TestMethod<StackSpec>(&StackSpec::apply_pop_0_time));
  suite.add(new TestMethod<StackSpec>(&StackSpec::apply_pop_1_time));
  suite.add(new TestMethod<StackSpec>(&StackSpec::apply_pop_2_times));

  run(suite);
  assertOutput("starting...\n***\nend.\n");
}

} // namespace