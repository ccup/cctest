#include "cctest/base/string_view.h"
#include "cctest/cctest.h"

using namespace cctest;

namespace {

FIXTURE(StringViewTest) {
  TEST("c-style string without size") {
    // const char* without size.
    auto hello = "hello";
    StringView s20(hello);
    ASSERT_TRUE(s20.data() == hello);
    ASSERT_EQ(5, s20.size());
  }

  TEST("c-style string with size") {
    auto hello = "hello";
    StringView s21(hello, 4);
    ASSERT_TRUE(s21.data() == hello);
    ASSERT_EQ(4, s21.size());
  }

  // Not recommended, but valid C++
  TEST("c-style string with invalid size") {
    auto hello = "hello";
    StringView s22(hello, 6);
    ASSERT_TRUE(s22.data() == hello);
    ASSERT_EQ(6, s22.size());
  }

  TEST("std::string") {
    std::string hola = "hola";
    StringView s30(hola);
    ASSERT_TRUE(s30.data() == hola.data());
    ASSERT_EQ(4, s30.size());

    // std::string with embedded '\0'.
    hola.push_back('\0');
    hola.append("h2");
    hola.push_back('\0');
    StringView s31(hola);
    ASSERT_TRUE(s31.data() == hola.data());
    ASSERT_EQ(8, s31.size());
  }

  TEST("to std::string explicitly") {
    ASSERT_EQ("", std::string(StringView("")));
    ASSERT_EQ("foo", std::string(StringView("foo")));
  }
};

} // namespace
