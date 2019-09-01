#ifndef H7785F505_8D19_4C0A_8549_C4A62CD88C76
#define H7785F505_8D19_4C0A_8549_C4A62CD88C76

#include "cctest/core/test.h"
#include "cctest/core/test_fixture.h"

namespace cctest {

// clang bugs: should be private.
struct TestCase : Test, protected TestFixture {
  using Test::Test;

private:
  void run(TestResult& result) override;

private:
  virtual void runTest() {}
};

} // namespace cctest

#endif
