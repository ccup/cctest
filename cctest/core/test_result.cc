#include "cctest/core/test_result.h"
#include "cctest/core/test.h"
#include "cctest/core/test_listener.h"
#include "cctest/core/internal/test_case_method.h"
#include "cctest/core/internal/bare_test_case.h"
#include "cctest/core/internal/bare_test_suite.h"
#include "cctest/except/assertion_error.h"

namespace cctest {

void TestResult::runRootTest(Test& test) {
  MultiListener::startTestRun(test);
  test.run(*this);
  MultiListener::endTestRun(test);
}

void TestResult::runTestCase(BareTestCase& test) {
  MultiListener::startTestCase(test.get());
  test.runBare(*this);
  MultiListener::endTestCase(test.get());  
}

void TestResult::runTestSuite(BareTestSuite& test) {
  MultiListener::startTestSuite(test.get());
  test.runBare(*this);
  MultiListener::endTestSuite(test.get());
}

void TestResult::onFail(std::string who, std::string msg, bool failure) {
  failures.emplace_back(std::move(who), std::move(msg), failure);
  MultiListener::addFailure(failures.back());
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

#define ON_FAIL(why)  onFail(f.who(), msg(why, f.where(), e.what()), true)
#define ON_ERROR(why) onFail(f.who(), msg(why, f.where(), e.what()), false)

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
