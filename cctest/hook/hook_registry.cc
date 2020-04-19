#include "cctest/hook/hook_registry.h"
#include "cctest/hook/hook.h"

namespace cctest {

HookRegistry& HookRegistry::before() {
  static HookRegistry inst;
  return inst;
}

HookRegistry& HookRegistry::after() {
  static HookRegistry inst;
  return inst;
}

void HookRegistry::add(Hook &hook) {
  hooks.push_back(&hook);
}

void HookRegistry::exec() {
  for (auto hook : hooks) {
    hook->invoke();
  }
}

} // namespace cctest
