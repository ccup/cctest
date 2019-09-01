#ifndef HC9E8B8E2_729D_469F_8C91_90EF3791FC8E
#define HC9E8B8E2_729D_469F_8C91_90EF3791FC8E

#include <vector>
#include "cctest/core/test_failure.h"

namespace cctest {

struct TestCaseMethod;

struct TestResult {
  TestResult();

  void startTestCase();
  int runCount() const;

  int failCount() const;
  int errorCount() const;

  bool protect(const TestCaseMethod&);

  const std::vector<TestFailure>& getFailures() const;

private:
  void addFailure(std::string&& msg);
  void addError(std::string&& msg);

private:
  int numOfRuns;
  std::vector<TestFailure> failures;
};

} // namespace cctest

#endif
