#include "cctest/listener/collector/time_collector.h"

namespace cctest {

struct TimeCollector::Timer {
  Timer() {
    start.now();
  }

  void elapsed(TimeVal& last) const {
    last.now();
    last -= start;
  }

private:
  TimeVal start;
};

TimeVal TimeCollector::caseTime() const {
  return casetime;
}

TimeVal TimeCollector::suiteTime() const {
  return suitetime;
}

TimeVal TimeCollector::totalTime() const {
  return totaltime;
}

inline void TimeCollector::start() {
  stack.push(new Timer);
}

inline void TimeCollector::pop() {
  auto top = stack.top();
  stack.pop();
  delete top;
}

inline void TimeCollector::end(TimeVal& val) {
  stack.top()->elapsed(val);
  pop();
}

TimeCollector::~TimeCollector() {
  while (!stack.empty()) {
    pop();
  }
}

void TimeCollector::startTestRun(const Test&) {
  start();
}

void TimeCollector::endTestRun(const Test&) {
  end(totaltime);
}

void TimeCollector::startTestSuite(const Test&) {
  start();
}

void TimeCollector::endTestSuite(const Test&) {
  end(suitetime);
}

void TimeCollector::startTestCase(const Test&) {
  start();
}

void TimeCollector::endTestCase(const Test&) {
  end(casetime);
}

} // namespace cctest
