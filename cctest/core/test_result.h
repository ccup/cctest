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

  void runRootTest(Test&);

  void startTestCase(const Test&);
  void endTestCase(const Test&);

  bool protect(const TestCaseMethod&);

private:
  void addFailure(std::string&& msg, bool failure);

private:
  std::vector<TestFailure> failures;
  std::vector<TestListener*> listeners;
};

} // namespace cctest

#endif
