#ifndef H09FEEF0C_CD28_4C97_BCA9_CEEEC1063BBD
#define H09FEEF0C_CD28_4C97_BCA9_CEEEC1063BBD

#include "cctest/core/test_listener.h"

namespace cctest {

struct TestCollector : TestListener {
  TestCollector();

  int runCount() const;
  int failCount() const;
  int errorCount() const;
  int passCount() const;
  int failTotal() const;

private:
  void startTestCase(const Test&) override;
  void endTestCase(const Test&) override;
  void addFailure(const TestFailure&) override;

private:
  int numOfRuns;
  int numOfFails;
  int numOfErrors;
  int numOfPassed;
  bool lastFailed;
};

} // namespace cctest

#endif
