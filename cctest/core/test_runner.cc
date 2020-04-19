#include "cctest/core/test_runner.h"
#include "cctest/hook/hook_registry.h"
#include "cctest/factory/test_factory.h"
#include "cctest/core/test.h"  // delete root

namespace cctest {

TestRunner::TestRunner(TestListener &listener, TestFactory &factory)
    : root(factory.make()) {
  result.addListener(listener);
}

TestRunner::~TestRunner() {
  delete root;
}

void TestRunner::run() {
  HookRegistry::before().exec();
  result.runRootTest(*root);
  HookRegistry::after().exec();
}

} // namespace cctest
