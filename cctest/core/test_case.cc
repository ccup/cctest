#include "cctest/core/test_case.h"
#include "cctest/core/assertion_error.h"
#include "cctest/core/test_result.h"

namespace cctest {

bool TestCase::protect(TestResult& result, Method method) {
  bool succ = false;
  try {
    (this->*method)();
    succ = true;
  } catch (const AssertionError&) {
    result.addFailure();
  } catch (const std::exception&) {
    result.addError();
  } catch (...) {
    result.addError();
  }
  return succ;
}

void TestCase::runBare(TestResult& result) {
  if (protect(result, &TestCase::setUp)) {
    protect(result, &TestCase::runTest);
  }
  protect(result, &TestCase::tearDown);
}

void TestCase::run(TestResult& result) {
  result.startTestCase();
  runBare(result);
}

} // namespace cctest
