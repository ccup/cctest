#include "cctest/cctest.h"

using namespace cctest;

namespace {

FIXTURE(SimpleTest) {
  TEST("add") {
    auto result = 1 + 1;
    ASSERT_EQ(2, result);
  }

  TEST("mul") {
    auto result = 2 * 2;
    ASSERT_EQ(4, result);
  }
};

} // namespace

