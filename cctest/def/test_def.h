#ifndef HB441B22F_5752_4937_8515_0FD95060C052
#define HB441B22F_5752_4937_8515_0FD95060C052

#include "cctest/auto/auto_test_method.h" 
#include "cctest/base/symbol.h"

/////////////////////////////////////////////////////////////
#define __CCTEST_TEST_NAME(id) CCTEST_JOIN(test_, id) 
#define __CCTEST_AUTO_TEST(id) CCTEST_JOIN(auto_test_, id)

/////////////////////////////////////////////////////////////
#define __CCTEST_DEF_TEST(id, name)             \
private:                                        \
cctest::AutoTestMethod __CCTEST_AUTO_TEST(id)   \
{id, name, &self_type::__CCTEST_TEST_NAME(id)}; \
public:                                         \
void __CCTEST_TEST_NAME(id)()

/////////////////////////////////////////////////////////////
#define TEST(name) __CCTEST_DEF_TEST(CCTEST_UNIQUE_ID, name)

#endif
