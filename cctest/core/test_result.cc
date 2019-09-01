#include "cctest/core/test_result.h"
#include "cctest/core/assertion_error.h"
#include "cctest/core/internal/test_case_method.h"
#include <algorithm>

namespace cctest {

TestResult::TestResult() : numOfRuns(0) {
}

void TestResult::startTestCase() {
  numOfRuns++;
}

int TestResult::runCount() const {
  return numOfRuns;
}

int TestResult::failCount() const {
  return std::count_if(failures.begin(), failures.end(), [](const TestFailure& f) {
    return f.isFailure();
  });
}

int TestResult::errorCount() const {
  return failures.size() - failCount();
}

const std::vector<TestFailure>& TestResult::getFailures() const {
  return failures;
}

inline void TestResult::addFailure(std::string&& msg) {
  failures.emplace_back(std::move(msg), true);
}

inline void TestResult::addError(std::string&& msg) {
  failures.emplace_back(std::move(msg), false);
}

namespace {

inline std::string msg(const char* why, const char* where, const char* what) {
  return std::string(why) + ' ' + where + '\n' + what;
}

struct NilException {
  const char* what() const {
    return "";
  }
} const e;

} // namespace

#define ON_FAIL(except)  addFailure(msg(except, f.where(), e.what()))
#define ON_ERROR(except) addError(msg(except, f.where(), e.what()))

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
