#include "cctest/factory/test_hook_registry.h"

namespace cctest {

TestHookRegistry& TestHookRegistry::inst() {
  static TestHookRegistry registry;
  return registry;
}

void TestHookRegistry::add(TestFixture* hook) {
  hooks.push_back(hook);
}

TestHookRegistry::~TestHookRegistry() {
  for (auto hook : hooks) {
    delete hook;
  }
}

void TestHookRegistry::setUp() {
  for (auto hook : hooks) {
    hook->setUp();
  }
}

void TestHookRegistry::tearDown() {
  for (auto i = hooks.rbegin(); i != hooks.rend(); ++i) {
    (*i)->tearDown();
  }
}

} // namespace cctest
