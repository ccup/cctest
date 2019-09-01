#include "cctest/core/test_result.h"

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

void TestResult::addFailure() {
  numOfFails++;
}

int TestResult::failCount() const {
  return numOfFails;
}

void TestResult::addError() {
  numOfErrors++;
}

int TestResult::errorCount() const {
  return numOfErrors;
}

} // namespace cctest
