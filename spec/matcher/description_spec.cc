#include "cctest/matcher/base/description.h"
#include "cctest/cctest.h"

using namespace cctest;

namespace {

FIXTURE(DescriptionSpec) {
  Description desc;

  TEST("false") {
    desc.appendValue(false);
    ASSERT_EQ("<(bool)false>", desc.toString());
  }

  TEST("true") {
    desc.appendValue(true);
    ASSERT_EQ("<(bool)true>", desc.toString());
  }

  TEST("null integer") {
    desc.appendValue((void*) 0);
    ASSERT_EQ("<(void*)NULL>", desc.toString());
  }

  TEST("NULL") {
    desc.appendValue((void*) NULL);
    ASSERT_EQ("<(void*)NULL>", desc.toString());
  }

  TEST("nullptr") {
    desc.appendValue(nullptr);
    ASSERT_EQ("<(std::nullptr_t)NULL>", desc.toString());
  }

  TEST("char") {
    desc.appendValue((char) 2); 
    ASSERT_EQ("<(char)0x2/2>", desc.toString());
  }

  TEST("signed char") {
    desc.appendValue((signed char) 2); 
    ASSERT_EQ("<(signed char)0x2/2>", desc.toString());
  }

  TEST("unsigned char") {
    desc.appendValue((unsigned char) 2); 
    ASSERT_EQ("<(unsigned char)0x2/2>", desc.toString());
  }

  TEST("short") {
    desc.appendValue((short) 2); 
    ASSERT_EQ("<(short)0x2/2>", desc.toString());
  }

  TEST("signed short") {
    desc.appendValue((signed short) 2); 
    ASSERT_EQ("<(short)0x2/2>", desc.toString());
  }

  TEST("unsigned short") {
    desc.appendValue((unsigned short) 2); 
    ASSERT_EQ("<(unsigned short)0x2/2>", desc.toString());
  }

  TEST("int") {
    desc.appendValue(2);
    ASSERT_EQ("<(int)0x2/2>", desc.toString());
  }

  TEST("signed int") {
    desc.appendValue((signed int) 2);
    ASSERT_EQ("<(int)0x2/2>", desc.toString());
  }

  TEST("unsigned int") {
    desc.appendValue(2U);
    ASSERT_EQ("<(unsigned int)0x2/2>", desc.toString());
  }

  TEST("long") {
    desc.appendValue(2L);
    ASSERT_EQ("<(long)0x2/2>", desc.toString());
  }

  TEST("unsigned long") {
    desc.appendValue(2UL);
    ASSERT_EQ("<(unsigned long)0x2/2>", desc.toString());
  }

  TEST("c style string") {
    desc.appendValue("hello, world"); 
    ASSERT_EQ("<(char [13])\"hello, world\">", desc.toString());
  }

  TEST("std::string") {
    desc.appendValue(std::string("hello, world"));
    ASSERT_EQ("<(std::string)\"hello, world\">", desc.toString());
  }

  TEST("append text") {
    desc.appendText("hello").appendText(", ").appendText("world");
    ASSERT_EQ("hello, world", desc.toString());
  }

  TEST("append value list") {
    desc.appendValueList("{", ", ", "}", std::vector<int> { 1, 2 });
    ASSERT_EQ("{<(int)0x1/1>, <(int)0x2/2>}", desc.toString());
  }
};

} // namespace
