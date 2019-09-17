#include "cctest/listener/collector/test_collector.h"
#include "cctest/except/test_failure.h"

namespace cctest {

TestCollector::TestCollector()
  : numOfRuns(0)
  , numOfFails(0)
  , numOfErrors(0)
  , numOfPassed(0)
  , lastFailed(false) {}

int TestCollector::runCount() const {
  return numOfRuns;
}

int TestCollector::failCount() const {
  return numOfFails;
}

int TestCollector::errorCount() const {
  return numOfErrors;
}

int TestCollector::passCount() const {
  return numOfPassed;
}

void TestCollector::startTestCase(const Test&) {
  numOfRuns++;
  lastFailed = false;
}

void TestCollector::endTestCase(const Test&) {
  if (!lastFailed) numOfPassed++;
}

void TestCollector::addFailure(const TestFailure& f) {
  f.isFailure() ? numOfFails++ : numOfErrors++;
  lastFailed = true;
}

} // namespace cctest
