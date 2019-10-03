#include "cctest/cctest.h"
#include "cctest/core/test_desc.h"

using namespace cctest;

namespace {

FIXTURE(TestDescSpec) {
  TEST("without annotation") {
    TestDesc desc("test name");
    ASSERT_EQ("test name", desc.name());
  }

  TEST("extract test name") {
    TestDesc desc("@{id=xxx} test name");
    ASSERT_EQ("test name", desc.name());
  }

  TEST("extract id") {
    TestDesc desc("@{id=xxx} test name");
    ASSERT_EQ("xxx", desc.id());
  }

  TEST("extract dep") {
    TestDesc desc("@{dep=xxx} test name");
    ASSERT_EQ("xxx", desc.dep());
  }

  TEST("extract disable") {
    TestDesc desc("@{disable} test name");
    ASSERT_TRUE(desc.disable());
  }

  TEST("extract times") {
    TestDesc desc("@{times=10} test name");
    ASSERT_EQ(10, desc.times());
  }

  TEST("constains unknown keywords") {
    TestDesc desc("@{unknown_key=unknown_value} test name");
    ASSERT_EQ("test name", desc.name());
  }

  TEST("extract id, dep, and test name") {
    TestDesc desc("@{id=xxx, dep=yyy} test name");
    ASSERT_EQ("test name", desc.name());
    ASSERT_EQ("xxx", desc.id());
    ASSERT_EQ("yyy", desc.dep());
  }

  TEST("prefix starts with blacks") {
    TestDesc desc("    @{id=xxx, dep=yyy} test name");
    ASSERT_EQ("test name", desc.name());
    ASSERT_EQ("xxx", desc.id());
    ASSERT_EQ("yyy", desc.dep());
  }

  TEST("test name ends with blacks") {
    TestDesc desc("@{id=xxx, dep=yyy} test name   ");
    ASSERT_EQ("test name", desc.name());
  }

  TEST("prefix contains blacks") {
    TestDesc desc("@{ id = xxx, dep = yyy } test name");
    ASSERT_EQ("test name", desc.name());
    ASSERT_EQ("xxx", desc.id());
    ASSERT_EQ("yyy", desc.dep());
  }
};

} // namespace
