#include "cctest/base/string_utils.h"
#include "cctest/cctest.h"
#include <regex>
#include <iostream>

using namespace cctest;

namespace {

FIXTURE(StringUtilsSpec) {
  TEST("split then join") {
    using namespace strutils;
    ASSERT_TRUE(split("", ",").empty());
    ASSERT_EQ("a", join(split("a", ","), "|"));
    ASSERT_EQ("|", join(split(",", ","), "|"));
    ASSERT_EQ("a|b|c", join(split("a,b,c", ","), "|"));
    ASSERT_EQ("a|||b||c|", join(split("a,,,b,,c,", ","), "|"));
    ASSERT_EQ("a|||b||c|", join(split("a!,!b,!c,", ",!"), "|"));
  }
};

} // namespace cctest
