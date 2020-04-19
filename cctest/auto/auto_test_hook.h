#ifndef HBFF0C9EB_84EF_464C_8919_D68C9ED28355
#define HBFF0C9EB_84EF_464C_8919_D68C9ED28355

#include "cctest/factory/test_hook_registry.h"

namespace cctest {

template <typename Hook>
struct AutoTestHook{
  AutoTestHook() {
    TestHookRegistry::inst().add(new Hook);
  }
};

} // namespace cctest

#endif /* HBFF0C9EB_84EF_464C_8919_D68C9ED28355 */
