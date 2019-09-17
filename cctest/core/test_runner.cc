#include "cctest/core/test_runner.h"
#include "cctest/core/test.h"
#include "cctest/factory/test_factory.h"

namespace cctest {

TestRunner::TestRunner(TestListener &listener, TestFactory &factory)
    : root(factory.make()) {
  result.addListener(listener);
}

TestRunner::~TestRunner() {
  delete root;
}

void TestRunner::run() {
  result.runRootTest(*root);
}

} // namespace cctest
