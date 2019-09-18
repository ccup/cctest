#include "cctest/core/test_suite.h"
#include "cctest/core/test_result.h"

namespace cctest {

TestSuite::~TestSuite() {
  for (auto test : tests) {
    delete test;
  }
}

void TestSuite::add(Test* test) {
  tests.push_back(test);
}

int TestSuite::countTestCases() const {
  int result = 0;
  for (auto test : tests) {
    result += test->countTestCases();
  };
  return result;
}

void TestSuite::run(TestResult& result) {
  result.runTestSuite(*this);
}

void TestSuite::runBare(TestResult& result) {
  for (auto test : tests) {
    test->run(result);
  };
}

const Test& TestSuite::get() const {
  return *this;
}

} // namespace cctest

