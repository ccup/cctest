#include "cctest/core/test_result.h"

namespace cctest {

TestResult::TestResult() : numOfRuns(0) {
}

void TestResult::startTestCase() {
  numOfRuns++;
}

int TestResult::runCount() const {
  return numOfRuns;
}

} // namespace cctest
