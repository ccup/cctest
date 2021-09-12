#ifndef H4BFA83DC_DB94_4F49_93BF_AC5B41ED8E8B
#define H4BFA83DC_DB94_4F49_93BF_AC5B41ED8E8B

#include "cctest/core/test.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_once_functor.h"
#include "cctest/core/bare_test_once.h"

namespace cctest {

template <typename Fixture>
struct TestOnce : Test, private BareTestOnce {
  TestOnce(Test* test) : test(test) {}

  ~TestOnce() {
    delete test;
  }

private:
  const std::string& getName() const override {
    return test->getName();
  }

  int countTestCases() const override {
    return test->countTestCases();
  }

  void run(TestResult& result) override {
    result.runTestOnce(*this);
  }

private:
  const Test& get() const override {
    return *test;
  }

#define PROTECT(method) \
  p.protect(TestOnceFunctor(&Fixture::method, getName(), #method))

  void runBare(TestProtector& p) override {
    if (PROTECT(setUpFixture)) {
      test->run(p.result());
    }
    PROTECT(tearDownFixture);
  }

private:
  Test* test;
};

} // namespace cctest

#endif /* H4BFA83DC_DB94_4F49_93BF_AC5B41ED8E8B */
