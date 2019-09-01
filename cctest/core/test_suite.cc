#include "cctest/core/test_suite.h"
#include "cctest/core/test_case.h"

namespace cctest {

TestSuite::~TestSuite() {
  for (auto test : tests) {
    delete test;
  }
}

void TestSuite::add(TestCase* test) {
  tests.push_back(test);
}

void TestSuite::run() {
  for (auto test : tests) {
    test->run();
  }
}

} // namespace cctest

