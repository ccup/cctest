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
  void endTestCase(const Test&);

  bool protect(const TestCaseMethod&);

  const std::vector<TestFailure>& getFailures() const;

private:
  void onFail(std::string&& msg);
  void onError(std::string&& msg);
  void addFailure(TestFailure&&);

private:
  std::vector<TestFailure> failures;
  std::vector<TestListener*> listeners;
};

} // namespace cctest

#endif
