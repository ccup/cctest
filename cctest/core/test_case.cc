#include "cctest/core/test_case.h"

namespace cctest {

void TestCase::run() {
  setUp();
  runTest();
  tearDown();
}

} // namespace cctest
