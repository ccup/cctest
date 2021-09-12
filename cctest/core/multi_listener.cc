#include "cctest/core/multi_listener.h"

namespace cctest {

MultiListener::MultiListener(std::vector<TestListener*> listeners)
  : listeners(std::move(listeners)) {
}

void MultiListener::addListener(TestListener& listener) {
  listeners.push_back(&listener);
}

#define BOARDCAST(action) \
for (auto listener : listeners) listener->action

void MultiListener::startTestRun(const Test& test) {
  BOARDCAST(startTestRun(test));
}

void MultiListener::endTestRun(const Test& test) {
  BOARDCAST(endTestRun(test));
}

void MultiListener::startTestSuite(const Test& test) {
  BOARDCAST(startTestSuite(test));
}

void MultiListener::endTestSuite(const Test& test) {
  BOARDCAST(endTestSuite(test));
}

void MultiListener::startTestOnce(const Test& test) {
  BOARDCAST(startTestOnce(test));
}

void MultiListener::endTestOnce(const Test& test) {
  BOARDCAST(endTestOnce(test));
}

void MultiListener::startTestCase(const Test& test) {
  BOARDCAST(startTestCase(test));
}

void MultiListener::endTestCase(const Test& test) {
  BOARDCAST(endTestCase(test));
}

void MultiListener::addFailure(const TestFailure& failure) {
  BOARDCAST(addFailure(failure));
}

} // namespace cctest
