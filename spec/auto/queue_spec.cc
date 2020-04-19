#include "cctest/cctest.h"
#include <queue>

using namespace cctest;

namespace {

FIXTURE(QueueSpec) {
  std::queue<int> q;

  static std::queue<int> shared;

  SETUP_FIXTURE {
    ASSERT_TRUE(shared.empty());
    FAIL("setup fixture fail");
  }

  TEARDOWN_FIXTURE {
    ASSERT_TRUE(shared.empty());
  }

  SETUP {
    ASSERT_TRUE(shared.empty());
    q.push(1);
    q.push(2);
  }

  TEARDOWN {
    ASSERT_TRUE(shared.empty());
  }

  TEST("apply pop 0 time") {
    ASSERT_EQ(1, q.front());
    ASSERT_EQ(2, q.back());
  }

  TEST("apply pop 1 time") {
    q.pop();
    ASSERT_EQ(2, q.front());
    ASSERT_EQ(2, q.back());
  }

  TEST("apply pop 2 times") {
    q.pop();
    q.pop();
    ASSERT_TRUE(q.empty());
  }
};

std::queue<int> QueueSpec::shared;

} // namespace
