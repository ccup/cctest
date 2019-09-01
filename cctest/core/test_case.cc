#include "cctest/core/test_case.h"
#include "cctest/core/assertion_error.h"
#include "cctest/core/test_result.h"

namespace cctest {

void TestCase::runBare(TestResult& result) {
  setUp();
  try {
    runTest();
  } catch (const AssertionError&) {
    result.addFailure();
  }
  tearDown();
}

void TestCase::run(TestResult& result) {
  result.startTestCase();
  runBare(result);
}

} // namespace cctest
