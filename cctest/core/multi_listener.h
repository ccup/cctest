#ifndef H8FA5782A_D507_4833_B2E7_BF0091F68899
#define H8FA5782A_D507_4833_B2E7_BF0091F68899

#include <vector>
#include "cctest/core/test_listener.h"

namespace cctest {

struct MultiListener : TestListener {
  MultiListener() = default;
  MultiListener(std::vector<TestListener*> listeners);

  void addListener(TestListener& listener);

protected:
  void startTestRun(const Test&) override;
  void endTestRun(const Test&) override;

  void startTestOnce(const Test&) override;
  void endTestOnce(const Test&) override;

  void startTestSuite(const Test&) override;
  void endTestSuite(const Test&) override;

  void startTestCase(const Test&) override;
  void endTestCase(const Test&) override;

  void addFailure(const TestFailure&) override;

private:
  std::vector<TestListener*> listeners;
};

} // namespace cctest

#endif
