#include "cctest/listener/collector/test_status.h"

namespace cctest {

TestStatus::TestStatus() : succ(true) {
}

bool TestStatus::successful() const {
  return succ;
}

void TestStatus::addFailure(const TestFailure&) {
  succ = false;
}


} // namespace cctest
