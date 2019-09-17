#include "cctest/core/test_result.h"
#include "cctest/core/test.h"
#include "cctest/core/test_listener.h"
#include "cctest/except/assertion_error.h"
#include "cctest/core/internal/test_case_method.h"
#include "cctest/core/internal/bare_test_case.h"
#include "cctest/core/internal/bare_test_suite.h"

namespace cctest {

void TestResult::addListener(TestListener& listener) {
  listeners.push_back(&listener);
}

#define BOARDCAST(action) \
  for (auto listener : listeners) listener->action

void TestResult::startTestRun(const Test& test) {
  BOARDCAST(startTestRun(test));
}

void TestResult::endTestRun(const Test& test) {
  BOARDCAST(endTestRun(test));
}

void TestResult::runTestCase(BareTestCase& test) {
  BOARDCAST(startTestCase(test.get()));
  test.runBare(*this);
  BOARDCAST(endTestCase(test.get()));
}

void TestResult::runTestSuite(BareTestSuite& test) {
  BOARDCAST(startTestSuite(test.get()));
  test.runBare(*this);
  BOARDCAST(endTestSuite(test.get()));
}

void TestResult::addFailure(std::string&& msg, bool failure) {
  failures.emplace_back(std::move(msg), failure);
  BOARDCAST(addFailure(failures.back()));
}

namespace {
  std::string msg(const char* why, const char* where, const char* what) {
    return std::string(why) + ' ' + where + '\n' + what;
  }

  struct NilException {
    const char* what() const {
      return "";
    }
  } const e;
}

#define ON_FAIL(except)  addFailure(msg(except, f.where(), e.what()), true)
#define ON_ERROR(except) addFailure(msg(except, f.where(), e.what()), false)

bool TestResult::protect(const TestCaseMethod& f) {
  try {
    return f();
  } catch (const AssertionError& e) {
    ON_FAIL("assertion fail");
  } catch (const std::exception& e) {
    ON_ERROR("uncaught std::exception");
  } catch (...) {
    ON_ERROR("uncaught unknown exception");
  }
  return false;
}


} // namespace cctest
