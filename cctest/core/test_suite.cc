#include "cctest/core/test_suite.h"

namespace cctest {

TestSuite::TestSuite(const std::string& name)
  : name(name) {}

const std::string& TestSuite::getName() const {
  return name;
}

TestSuite::~TestSuite() {
  for (auto test : tests) {
    delete test;
  }
}

void TestSuite::add(Test* test) {
  tests.push_back(test);
}

void TestSuite::run() {
  for (auto test : tests) {
    test->run();
  }
}

} // namespace cctest

