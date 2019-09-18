#ifndef H6BB49081_B0D8_4907_B529_6551096153DD
#define H6BB49081_B0D8_4907_B529_6551096153DD

#include "cctest/core/test_listener.h"
#include "cctest/base/time_val.h"
#include <stack>

namespace cctest {

struct TimeCollector : TestListener {
  ~TimeCollector() override;

  TimeVal caseTime() const;
  TimeVal suiteTime() const;
  TimeVal totalTime() const;

  void startTestRun(const Test&) override;
  void endTestRun(const Test&) override;

  void startTestSuite(const Test&) override;
  void endTestSuite(const Test&) override;

  void startTestCase(const Test&) override;
  void endTestCase(const Test&) override;

private:
  void start();
  void end(TimeVal&);
  void pop();

private:
  TimeVal casetime;
  TimeVal suitetime;
  TimeVal totaltime;

  struct Timer;
  std::stack<Timer*> stack;
};

} // namespace cctest

#endif
