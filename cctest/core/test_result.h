#ifndef HC9E8B8E2_729D_469F_8C91_90EF3791FC8E
#define HC9E8B8E2_729D_469F_8C91_90EF3791FC8E

#include <vector>
#include "cctest/except/test_failure.h"

namespace cctest {

struct Test;
struct TestListener;
struct TestCaseMethod;

struct TestResult {
  void addListener(TestListener& listener);

  void startTestCase(const Test&);

  int errorCount() const;

  bool protect(const TestCaseMethod&);

  const std::vector<TestFailure>& getFailures() const;

private:
  void addFailure(std::string&& msg);
  void addError(std::string&& msg);

private:
  std::vector<TestFailure> failures;
  std::vector<TestListener*> listeners;
};

} // namespace cctest

#endif
