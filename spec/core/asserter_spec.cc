#include "cctest/cctest.h"

using namespace cctest;

namespace {

FIXTURE(EqualSpec) {
  TEST("same types") {
    int result = 1;
    ASSERT_EQ(1, result);
  }

  TEST("different types") {
    long result = 1;
    ASSERT_EQ(1, result);
  }

  TEST("compare to nil") {
    int* p = nullptr;
    ASSERT_EQ(nullptr, p);
    ASSERT_EQ(0, p);
    ASSERT_EQ(NULL, p);
  }

  TEST("compare std::string with c-style string") {
    ASSERT_EQ("hello", std::string("hello"));
    ASSERT_EQ(std::string("hello"), "hello");    
    ASSERT_EQ(std::string("hello"), std::string("hello"));
  }
};

FIXTURE(NotEqualSpec) {
  TEST("same types") {
    int result = 1;
    ASSERT_NE(2, result);
  }

  TEST("different types") {
    long result = 1;
    ASSERT_NE(2, result);
  }

  TEST("compare to nil") {
    int n = 10;
    int* p = &n;
    ASSERT_NE(nullptr, p);
    ASSERT_NE(0, p);
    ASSERT_NE(NULL, p);
  }

  TEST("compare std::string with c-style string") {
    ASSERT_NE("hello", std::string("world"));
    ASSERT_NE(std::string("hello"), "world");    
    ASSERT_NE(std::string("hello"), std::string("world"));    
  }
};

FIXTURE(AssertTrueSpec) {
  TEST("assert for bool expr") {
    ASSERT_TRUE(1 == 1);
  }

  TEST("assert true for non zero expr") {
    ASSERT_TRUE(1);
    ASSERT_TRUE(1.0);
    ASSERT_TRUE("hello");
  }

  TEST("assert true for non nil") {
    int n = 1;
    int* p = &n;
    ASSERT_TRUE(p);
  }

  TEST("assert true for empty c-style string") {
    ASSERT_TRUE("");
  }
};

FIXTURE(AssertFalseSpec) {
  TEST("assert for bool expr") {
    ASSERT_FALSE(1 == 2);
  }

  TEST("assert false for zero expr") {
    ASSERT_FALSE(0);
    ASSERT_FALSE(0.0);           
    ASSERT_FALSE(0.0f);               
  }

  TEST("assert true for non nil") {
    ASSERT_FALSE(nullptr);
    ASSERT_FALSE(NULL); 

    int* p = nullptr;
    ASSERT_FALSE(p); 

    p = NULL;
    ASSERT_FALSE(p);     

    p = 0;
    ASSERT_FALSE(p);     
  }
};

FIXTURE(LessToSpec) {
  TEST("should allow compare to integer") {
    ASSERT_LT(0xEE, 0xFF);
    ASSERT_LT(0xEE, 0xFF);
  }

  TEST("should allow compare to string") {
    ASSERT_LT(std::string("hello"), "world");
    ASSERT_LT("hello", std::string("world"));
    ASSERT_LT(std::string("hello"), std::string("world"));
  }
};

FIXTURE(LessOrEqualToSpec) {
  TEST("should allow compare to integer") {
    ASSERT_LE(0xEE, 0xFF);
    ASSERT_LE(0xEE, 0xEE);
  }

  TEST("should allow compare to string") {
    ASSERT_LE("hello", std::string("hello"));
    ASSERT_LE(std::string("hello"), std::string("hello"));
    ASSERT_LE(std::string("hello"), "hello");    

    ASSERT_LE("hello", std::string("world"));
    ASSERT_LE(std::string("hello"), std::string("world"));
    ASSERT_LE(std::string("hello"), "world");    
  }
};

FIXTURE(GreaterToSpec) {
  TEST("should allow compare to integer") {
    ASSERT_GT(0xFF, 0xEE);
    ASSERT_GT(0xFF, 0xEE);
  }

  TEST("should allow compare to string") {
    ASSERT_GT("world", std::string("hello"));
    ASSERT_GT(std::string("world"), std::string("hello"));
    ASSERT_GT(std::string("world"), "hello");    
  }
};

FIXTURE(GreaterOrEqualToSpec) {
  TEST("should allow compare to integer") {
    ASSERT_GE(0xFF, 0xEE);
    ASSERT_GE(0xFF, 0xFF);
  }

  TEST("should allow compare to string") {
    ASSERT_GE("world", std::string("hello"));
    ASSERT_GE(std::string("world"), std::string("hello"));
    ASSERT_GE(std::string("world"), "hello");

    ASSERT_GE("world", std::string("world"));
    ASSERT_GE(std::string("world"), std::string("world"));
    ASSERT_GE(std::string("world"), "world");
  }
};

} // namespace
