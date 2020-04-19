#include "cctest/hook/hook.h"
#include "cctest/hook/hook_registry.h"

namespace cctest {

BeforeHook::BeforeHook()
{
    HookRegistry::before().add(*this);
}

AfterHook::AfterHook()
{
    HookRegistry::after().add(*this);
}

} // namespace cctest
