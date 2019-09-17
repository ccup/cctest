#ifndef H5FA25ACD_7EBA_4B23_9FC1_2BE2836D2D62
#define H5FA25ACD_7EBA_4B23_9FC1_2BE2836D2D62

#include "cctest/auto/auto_test_fixture.h"
#include "cctest/core/test_fixture.h"
#include "cctest/base/symbol.h"
#include "cctest/base/self.h"

/////////////////////////////////////////////////////////////
#define FIXTURE(type)                                    \
struct type;                                             \
static cctest::AutoTestFixture<type>                     \
CCTEST_UNIQUE_NAME(auto_suite_){CCTEST_STRINGIZE(type)}; \
struct type : cctest::TestFixture, cctest::Self<type>

/////////////////////////////////////////////////////////////
#define SETUP    void setUp() override 
#define TEARDOWN void tearDown() override

/////////////////////////////////////////////////////////////
#define SUPER_SETUP(super) super::setUp() 
#define SUPER_TEARDOWN(super) super::tearDown()

#endif
