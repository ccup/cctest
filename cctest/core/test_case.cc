#include "cctest/core/test_case.h"

namespace cctest {

TestCase::TestCase(const std::string& name)
  : name(name) {}

const std::string& TestCase::getName() const {
  return name;
}

void TestCase::run() {
  setUp();
  runTest();
  tearDown();
}

} // namespace cctest
