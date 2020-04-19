#ifndef HA8711DB6_A489_48BC_817B_90A3C1A227D5
#define HA8711DB6_A489_48BC_817B_90A3C1A227D5

#include "cctest/base/symbol.h"
#include "cctest/hook/hook.h"

///////////////////////////////////////////////////////////////
#define __HOOK_NAME CCTEST_UNIQUE_NAME(HookObject)

///////////////////////////////////////////////////////////////
#define __CCTEST_HOOK(type, super) \
struct type : super {              \
private:                           \
  void invoke() override;          \
};                                 \
static type var##type;             \
void type::invoke()

///////////////////////////////////////////////////////////////
#define __BEFORE_ALL(obj) __CCTEST_HOOK(obj, cctest::BeforeHook)
#define __AFTER_ALL(obj)  __CCTEST_HOOK(obj, cctest::AfterHook)

///////////////////////////////////////////////////////////////
#define BEFORE_ALL __BEFORE_ALL(__HOOK_NAME)
#define AFTER_ALL  __AFTER_ALL(__HOOK_NAME)

#endif /* HA8711DB6_A489_48BC_817B_90A3C1A227D5 */
