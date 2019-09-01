#include "cctest/core/test_suite.h"

namespace cctest {

TestSuite::~TestSuite() {
  for (auto test : tests) {
    delete test;
  }
}

void TestSuite::add(Test* test) {
  tests.push_back(test);
}

void TestSuite::run(TestResult& result) {
  for (auto test : tests) {
    test->run(result);
  }
}

} // namespace cctest

