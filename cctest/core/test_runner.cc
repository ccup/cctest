#include "cctest/core/test_runner.h"
#include "cctest/factory/test_hook_registry.h"
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
  TestFixture& hook = TestHookRegistry::inst();

  hook.setUp();
  result.runRootTest(*root);
  hook.tearDown();
}

} // namespace cctest
