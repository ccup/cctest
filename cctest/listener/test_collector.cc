#include "cctest/listener/test_collector.h"

namespace cctest {

TestCollector::TestCollector()
  : numOfRuns(0) {}

int TestCollector::runCount() const {
  return numOfRuns;
}

void TestCollector::startTestCase(const Test&) {
  numOfRuns++;
}

} // namespace cctest
