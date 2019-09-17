#include "cctest/listener/test_collector.h"

namespace cctest {

TestCollector::TestCollector()
  : numOfRuns(0), numOfFails(0) {}

int TestCollector::runCount() const {
  return numOfRuns;
}

int TestCollector::failCount() const {
  return numOfFails;
}

void TestCollector::startTestCase(const Test&) {
  numOfRuns++;
}

void TestCollector::addFailure(const TestFailure&) {
  numOfFails++;
}

} // namespace cctest
