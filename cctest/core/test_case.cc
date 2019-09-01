#include "cctest/core/test_case.h"
#include "cctest/core/test_result.h"

namespace cctest {

void TestCase::run(TestResult& result) {
  result.startTestCase();
  setUp();
  runTest();
  tearDown();
}

} // namespace cctest
