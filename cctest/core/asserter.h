#ifndef H21432787_83D8_45BF_A8E2_4E10EDA3E8D4
#define H21432787_83D8_45BF_A8E2_4E10EDA3E8D4

#include <string.h>
#include <float.h>
#include <math.h>

#include "cctest/base/formatter.h"
#include "cctest/base/logger.h"
#include "cctest/except/assertion_error.h"

namespace cctest {

//////////////////////////////////////////////////////////////////
#define __CCTEST_MAKE_STR(expr) " " #expr " "

//////////////////////////////////////////////////////////////////
#define __CCTEST_REPORT_FAILURE(what) \
    throw cctest::AssertionError(__FILE__, __LINE__, what)

//////////////////////////////////////////////////////////////////
#define __CCTEST_ASSERT_BOOL(expr, not_comp, expected_value, wrong_value) do { \
  if(not_comp(expr)) { \
    __CCTEST_REPORT_FAILURE(              \
      "expected (" #expr ") being"        \
      __CCTEST_MAKE_STR(expected_value)   \
      ", but it's actually"               \
      __CCTEST_MAKE_STR(wrong_value));    \
  } \
} while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_TRUE(expr)  \
  __CCTEST_ASSERT_BOOL(expr, !, true,  false)

//////////////////////////////////////////////////////////////////
#define ASSERT_FALSE(expr) \
  __CCTEST_ASSERT_BOOL(expr, ,  false, true)

//////////////////////////////////////////////////////////////////
#define __CCTEST_ASSERT_CMP(expected_value, not_comp, expected_comp, wrong_comp, value) do {\
   decltype(value) __cctest_value = (value); \
   if (not_comp(expected_value expected_comp __cctest_value)) { \
     std::stringstream ss; \
     ss << "expected (" #expected_value __CCTEST_MAKE_STR(expected_comp) #value "), found (" \
        << cctest::toTypeAndValueString(expected_value) \
        << __CCTEST_MAKE_STR(wrong_comp) \
        << cctest::toTypeAndValueString(__cctest_value) \
        << ")"; \
     __CCTEST_REPORT_FAILURE(ss.str()); \
   } \
} while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_EQ(expected, value) \
  __CCTEST_ASSERT_CMP(expected, !, ==, !=, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_NE(expected, value) \
  __CCTEST_ASSERT_CMP(expected, !, !=, ==, value)  

//////////////////////////////////////////////////////////////////
#define ASSERT_LT(expected, value) \
  __CCTEST_ASSERT_CMP(expected, !, <, >=, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_GT(expected, value) \
  __CCTEST_ASSERT_CMP(expected, !, >, <=, value)  

//////////////////////////////////////////////////////////////////
#define ASSERT_LE(expected, value) \
  __CCTEST_ASSERT_CMP(expected, !, <=, >, value)  

//////////////////////////////////////////////////////////////////
#define ASSERT_GE(expected, value) \
  __CCTEST_ASSERT_CMP(expected, !, >=, <, value)    

////////////////////////////////////////////////////////////////
#define __CCTEST_ASSERT_FLOAT_EQUALITY(eps, expected_value, not_equals, expected_equality, wrong_equality, value) do {\
  decltype(value) __cctest_value = (value); \
  if (not_equals(fabs(expected_value - __cctest_value) < eps)) { \
    std::stringstream ss; \
    ss << "expected (" #expected_value __CCTEST_MAKE_STR(expected_equality) #value "), found (" \
       << cctest::toTypeAndValueString(expected_value) \
       << __CCTEST_MAKE_STR(wrong_equality) \
       << cctest::toTypeAndValueString(__cctest_value) \
       << ")"; \
    __CCTEST_REPORT_FAILURE(ss.str()); \
  } \
} while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_FLOAT_EQ(expected, value) \
  __CCTEST_ASSERT_FLOAT_EQUALITY(FLT_EPSILON, expected, !, ==, !=, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_FLOAT_NE(expected, value) \
  __CCTEST_ASSERT_FLOAT_EQUALITY(FLT_EPSILON, expected, , !=, ==, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_DOUBLE_EQ(expected, value) \
  __CCTEST_ASSERT_FLOAT_EQUALITY(DBL_EPSILON, expected, !, ==, !=, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_DOUBLE_NE(expected, value) \
  __CCTEST_ASSERT_FLOAT_EQUALITY(DBL_EPSILON, expected, , !=, ==, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_LONG_DOUBLE_EQ(expected, value) \
  __CCTEST_ASSERT_FLOAT_EQUALITY(LDBL_EPSILON, expected, !, ==, !=, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_LONG_DOUBLE_NE(expected, value) \
  __CCTEST_ASSERT_FLOAT_EQUALITY(LDBL_EPSILON, expected, , !=, ==, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROW(expr, except) do { \
  bool cctest_caught_exception = false; \
  try { \
    expr; \
  } catch(except&){ \
    cctest_caught_exception = true; \
  } catch(...) {\
    __CCTEST_REPORT_FAILURE( \
        "expected " #expr " will throw an exception of type " #except \
        ", but actually raised a different kind of exception.", false); \
    throw; /*let user know which exception was throwed.*/\
  } \
  if (!cctest_caught_exception) { \
    __CCTEST_REPORT_FAILURE( \
        "expected " #expr " will throw an exception of type " #except ", but actually not."); \
  } \
} while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROW_ANYTHING(expr) do { \
  bool __cctest_caught_exception = false; \
  try { \
    expr; \
  } catch(...){ \
    __cctest_caught_exception = true; \
  } \
  if (!__cctest_caught_exception) { \
    __CCTEST_REPORT_FAILURE ( \
         "expected " #expr " will throw an exception of any type, but actually not."); \
  } \
} while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROW_NOTHING(expr) do { \
  try { \
    expr; \
  } catch(...){ \
    __CCTEST_REPORT_FAILURE ( \
        "expected " #expr " will not throw any exceptions, but it actually did."); \
  } \
} while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_SAME(addr1, addr2, size) do { \
  void* p1 = reinterpret_cast<void*>(addr1); \
  void* p2 = reinterpret_cast<void*>(addr2); \
  if (::memcmp((void*)p1, (void*)p2, size)) { \
    std::stringstream ss; \
    ss << "expected (" #addr1 ", " #addr2 ") have same data, found (" \
       << cctest::toBufferString(p1, size) \
       << ", " \
       << cctest::toBufferString(p2, size) \
       << ")"; \
    __CCTEST_REPORT_FAILURE(ss.str()); \
  } \
} while(0)

//////////////////////////////////////////////////////////////////
#define __CCTEST_ABS(value) ((value) > 0 ? (value) : -(value))

//////////////////////////////////////////////////////////////////
#define ASSERT_DELTA(x, y, d) do { \
  decltype(x) value1 = x; \
  decltype(y) value2 = y; \
  decltype(d) delta  = __CCTEST_ABS(d); \
  decltype(d) actual_delta = __CCTEST_ABS(value1 - value2); \
  if (actual_delta > delta) { \
    std::stringstream ss; \
    ss << "expected the delta of (" #x ", " #y ") <= (" \
       << cctest::toTypeAndValueString(delta) \
       << "), actual delta: (" \
       << cctest::toTypeAndValueString(actual_delta) \
       << ")"; \
    __CCTEST_REPORT_FAILURE(ss.str()); \
  } \
} while(0)

//////////////////////////////////////////////////////////////////
#define FAIL(msg) do { \
  __CCTEST_REPORT_FAILURE(msg); \
} while(0)

//////////////////////////////////////////////////////////////////
#define WARN(msg) do {    \
  CCTEST_WARN_LOG << msg; \
} while(0)

//////////////////////////////////////////////////////////////////
#define INFO(msg) do {    \
  CCTEST_INFO_LOG << msg; \
} while(0)

} // namespace cctest

#endif
