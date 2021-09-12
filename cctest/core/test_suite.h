#ifndef HEBA1EEE2_F46F_4F44_8247_10C8AB3D0FCA
#define HEBA1EEE2_F46F_4F44_8247_10C8AB3D0FCA

#include <vector>
#include "cctest/core/test.h"
#include "cctest/core/bare_test_suite.h"

namespace cctest {

struct TestSuite : Test, private BareTestSuite {
  using Test::Test;

  ~TestSuite() override;

  void add(Test* test);

private:
  int countTestCases() const override;
  void run(TestResult& result) override;

private:
  const Test& get() const override;
  void runBare(TestResult&) override;

private:
  std::vector<Test*> tests;
};

} // namespace cctest

#endif
