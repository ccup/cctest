#ifndef H09FEEF0C_CD28_4C97_BCA9_CEEEC1063BBD
#define H09FEEF0C_CD28_4C97_BCA9_CEEEC1063BBD

#include "cctest/core/test_listener.h"

namespace cctest {

struct TestCollector : TestListener {
  TestCollector();

  int runCount() const;
  int failCount() const;

private:
  void startTestCase(const Test&) override;
  void addFailure(const TestFailure&) override;

private:
  int numOfRuns;
  int numOfFails;
};

} // namespace cctest

#endif
