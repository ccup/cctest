#ifndef HA8711DB6_A489_48BC_817B_90A3C1A227D5
#define HA8711DB6_A489_48BC_817B_90A3C1A227D5

#include "cctest/base/symbol.h"
#include "cctest/core/test_fixture.h"
#include "cctest/auto/auto_test_hook.h"

///////////////////////////////////////////////////////////////
#define __HOOK_NAME CCTEST_UNIQUE_NAME(HookObject)

///////////////////////////////////////////////////////////////
#define HOOK(type)                 \
struct type;                       \
static cctest::AutoTestHook<type>  \
CCTEST_UNIQUE_NAME(auto_hook_);    \
struct type : cctest::TestFixture  \

#endif /* HA8711DB6_A489_48BC_817B_90A3C1A227D5 */
