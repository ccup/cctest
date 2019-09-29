#include "cctest/factory/test_name.h"
#include "cctest/cctest.h"

using namespace cctest;

namespace {

FIXTURE(TestNameSpec) {
  TEST("without annotation") {
    TestName namer("test name");
    ASSERT_EQ("test name", namer.realname());
  }

  TEST("extract test name") {
    TestName namer("@{id=xxx} test name");
    ASSERT_EQ("test name", namer.realname());
  }

  TEST("extract id") {
    TestName namer("@{id=xxx} test name");
    ASSERT_EQ("xxx", namer.id());
  }

  TEST("extract dep") {
    TestName namer("@{dep=xxx} test name");
    ASSERT_EQ("xxx", namer.dep());
  }

  TEST("extract disable") {
    TestName namer("@{disable} test name");
    ASSERT_TRUE(namer.disable());
  }

  TEST("extract times") {
    TestName namer("@{times=10} test name");
    ASSERT_EQ(10, namer.times());
  }

  TEST("constains unknown keywords") {
    TestName namer("@{unknown_key=unknown_value} test name");
    ASSERT_EQ("test name", namer.realname());
  }

  TEST("extract id, dep, and test name") {
    TestName namer("@{id=xxx, dep=yyy} test name");
    ASSERT_EQ("test name", namer.realname());
    ASSERT_EQ("xxx", namer.id());
    ASSERT_EQ("yyy", namer.dep());
  }

  TEST("prefix starts with blacks") {
    TestName namer("    @{id=xxx, dep=yyy} test name");
    ASSERT_EQ("test name", namer.realname());
    ASSERT_EQ("xxx", namer.id());
    ASSERT_EQ("yyy", namer.dep());
  }

  TEST("test name ends with blacks") {
    TestName namer("@{id=xxx, dep=yyy} test name   ");
    ASSERT_EQ("test name", namer.realname());
  }

  TEST("prefix contains blacks") {
    TestName namer("@{ id = xxx, dep = yyy } test name");
    ASSERT_EQ("test name", namer.realname());
    ASSERT_EQ("xxx", namer.id());
    ASSERT_EQ("yyy", namer.dep());
  }
};

} // namespace
