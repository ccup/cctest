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

bool TestResult::protect(const TestCaseMethod& f) {
  try {
    return f();
  } catch (const AssertionError& e) {
    addFailure(std::string("assertion fail") + ' ' + f.where() + '\n' + e.what());
  } catch (const std::exception& e) {
    addError(std::string("uncaught std::exception") + ' ' + f.where() + '\n' + e.what());
  } catch (...) {
    addError(std::string("uncaught unknown exception") + " " + f.where() + "\n" + "");
  }
  return false;
}

} // namespace cctest
