#ifndef HC9E8B8E2_729D_469F_8C91_90EF3791FC8E
#define HC9E8B8E2_729D_469F_8C91_90EF3791FC8E

#include <vector>
#include "cctest/except/test_failure.h"
#include "cctest/core/internal/test_case_protector.h"

namespace cctest {

struct Test;
struct TestListener;
struct BareTestCase;
struct BareTestSuite;

struct TestResult : private TestCaseProtector {
  void addListener(TestListener& listener);

  void runRootTest(Test&);
  void runTestCase(BareTestCase&);
  void runTestSuite(BareTestSuite&);

private:
  bool protect(const TestCaseMethod&) override;

private:
  void addFailure(std::string&& msg, bool failure);

private:
  std::vector<TestFailure> failures;
  std::vector<TestListener*> listeners;
};

} // namespace cctest

#endif
