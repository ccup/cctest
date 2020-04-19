#ifndef H5FA25ACD_7EBA_4B23_9FC1_2BE2836D2D62
#define H5FA25ACD_7EBA_4B23_9FC1_2BE2836D2D62

#include "cctest/auto/auto_test_fixture.h"
#include "cctest/core/test_fixture.h"
#include "cctest/base/symbol.h"
#include "cctest/base/self.h"

///////////////////////////////////////////////////////////////
namespace cctest {
template <typename... Fixtures>
struct GenericAutoFixture;

template <typename Head, typename... Tail>
struct GenericAutoFixture<Head, Tail...>
    : virtual Head
    , virtual GenericAutoFixture<Tail...>
{};

template <>
struct GenericAutoFixture<> : TestFixture
{};

} // cctest

///////////////////////////////////////////////////////////////
#define FIXTURE(type, ...)                                    \
struct type;                                                  \
static cctest::AutoTestFixture<type>                          \
CCTEST_UNIQUE_NAME(auto_suite_){CCTEST_STRING(type)};         \
struct type : virtual cctest::GenericAutoFixture<__VA_ARGS__> \
            , cctest::Self<type>

///////////////////////////////////////////////////////////////
#define BEFORE void setUp() override
#define AFTER  void tearDown() override

///////////////////////////////////////////////////////////////
#define SUPER_BEFORE(super) super::setUp()
#define SUPER_AFTER(super)  super::tearDown()

///////////////////////////////////////////////////////////////
#define BEFORE_FIXTURE static void setUpFixture()
#define AFTER_FIXTURE  static void tearDownFixture()

///////////////////////////////////////////////////////////////
#define SUPER_BEFORE_FIXTURE(super) super::setUpFixture()
#define SUPER_AFTER_FIXTURE(super)  super::tearDownFixture()

#endif
