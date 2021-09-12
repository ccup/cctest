#include "cctest/core/test_result.h"
#include "cctest/core/test.h"
#include "cctest/core/test_functor.h"
#include "cctest/core/bare_test_case.h"
#include "cctest/core/bare_test_suite.h"
#include "cctest/core/bare_test_once.h"
#include "cctest/except/assertion_error.h"

#include <sstream>

namespace cctest {

void TestResult::runRootTest(Test& test) {
  startTestRun(test);
  test.run(*this);
  endTestRun(test);
}

void TestResult::runTestCase(BareTestCase& test) {
  startTestCase(test.get());
  test.runBare(*this);
  endTestCase(test.get());
}

void TestResult::runTestSuite(BareTestSuite& test) {
  startTestSuite(test.get());
  test.runBare(*this);
  endTestSuite(test.get());
}

void TestResult::runTestOnce(BareTestOnce& test) {
  startTestOnce(test.get());
  test.runBare(*this);
  endTestOnce(test.get());
}

void TestResult::onFail(std::string who, std::string msg, bool failure) {
  failures.emplace_back(std::move(who), std::move(msg), failure);
  addFailure(failures.back());
}

namespace {
  std::string msg(const char* why, const char* where, const char* what) {
    std::ostringstream out;
    out << why   << " "
        << where << std::endl
        << what;
    return out.str();
  }

  struct NilException {
    const char* what() const {
      return "";
    }
  } const e;
}

#define ON_FAIL(why)  onFail(f.who(), msg(why, f.where(), e.what()), true)
#define ON_ERROR(why) onFail(f.who(), msg(why, f.where(), e.what()), false)

bool TestResult::protect(const TestFunctor& f) {
  try {
    return f(), true;
  } catch (const AssertionError& e) {
    ON_FAIL("assertion fail");
  } catch (const std::exception& e) {
    ON_ERROR("uncaught std::exception");
  } catch (...) {
    ON_ERROR("uncaught unknown exception");
  }
  return false;
}

TestResult& TestResult::result() {
  return *this;
}

} // namespace cctest
