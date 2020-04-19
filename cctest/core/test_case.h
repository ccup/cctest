#ifndef H7785F505_8D19_4C0A_8549_C4A62CD88C76
#define H7785F505_8D19_4C0A_8549_C4A62CD88C76

#include "cctest/core/test.h"
#include "cctest/core/test_fixture.h"
#include "cctest/core/bare_test_case.h"

namespace cctest {

struct TestCase : Test, private TestFixture, private BareTestCase {
  using Test::Test;

private:
  int countTestCases() const override;
  void run(TestResult&) override;

private:
  const Test& get() const override;
  void runBare(TestProtector&) override;

private:
  virtual void runTest() {}

private:
  void runBare(TestResult& result);
};

} // namespace cctest

#endif
