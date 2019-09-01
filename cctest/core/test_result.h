#ifndef HC9E8B8E2_729D_469F_8C91_90EF3791FC8E
#define HC9E8B8E2_729D_469F_8C91_90EF3791FC8E

#include <vector>
#include <string>

namespace cctest {

struct TestCaseMethod;

struct TestResult {
  TestResult();

  void startTestCase();
  int runCount() const;

  int failCount() const;
  int errorCount() const;

  bool protect(const TestCaseMethod&);

  using TestFailures = std::vector<std::string>;
  const TestFailures& getFailures() const;

  using TestErrors = std::vector<std::string>;
  const TestErrors& getErrors() const;

private:
  void addFailure(std::string&& msg);
  void addError(std::string&& msg);

private:
  int numOfRuns;
  int numOfFails;
  int numOfErrors;

  TestFailures failures;
  TestErrors errors;
};

} // namespace cctest

#endif
