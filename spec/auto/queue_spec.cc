#include "cctest/auto/auto_test_method.h"
#include "cctest/auto/auto_test_fixture.h"
#include <gtest/gtest.h>
#include <queue>

using namespace cctest;

namespace {

struct QueueSpec;
static AutoTestFixture<QueueSpec> suite2;

struct QueueSpec : TestFixture {
  std::queue<int> q;

  void setUp() override {
    q.push(1);
    q.push(2);
  }

  void apply_pop_0_time() {
    ASSERT_EQ(1, q.front());
    ASSERT_EQ(2, q.back());
  }

  AutoTestMethod m1 { 1, "apply_pop_0_time", &QueueSpec::apply_pop_0_time };

  void apply_pop_1_time() {
    q.pop();
    ASSERT_EQ(2, q.front());
    ASSERT_EQ(2, q.back());
  }

  AutoTestMethod m2 { 2, "apply_pop_1_time", &QueueSpec::apply_pop_1_time };

  void apply_pop_2_times() {
    q.pop();
    q.pop();
    ASSERT_TRUE(q.empty());
  }

  AutoTestMethod m3 { 3, "apply_pop_2_times", &QueueSpec::apply_pop_2_times };
};

} // namespace
