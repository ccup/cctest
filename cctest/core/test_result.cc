#include "cctest/core/test_result.h"
#include "cctest/core/assertion_error.h"
#include "cctest/core/internal/test_case_method.h"

namespace cctest {

TestResult::TestResult()
  : numOfRuns(0), numOfFails(0), numOfErrors(0) {
}

void TestResult::startTestCase() {
  numOfRuns++;
}

int TestResult::runCount() const {
  return numOfRuns;
}

int TestResult::failCount() const {
  return numOfFails;
}

int TestResult::errorCount() const {
  return numOfErrors;
}

inline void TestResult::addFailure(std::string&& msg) {
  numOfFails++;
  failures.emplace_back(std::move(msg));
}

inline void TestResult::addError(std::string&& msg) {
  numOfErrors++;
  errors.emplace_back(std::move(msg));
}

bool TestResult::protect(const TestCaseMethod& f) {
  try {
    return f();
  } catch (const AssertionError& e) {
    addFailure(std::string("assertion fail") + ' ' + f.where() + '\n' + e.what());
  } catch (const std::exception& e) {
    addError(std::string("uncaught std::exception") + ' ' + f.where() + '\n' + e.what());
  } catch (...) {
    addError("");
  }
  return false;
}

const TestResult::TestFailures& TestResult::getFailures() const {
  return failures;
}

const TestResult::TestErrors& TestResult::getErrors() const {
  return errors;
}


} // namespace cctest
