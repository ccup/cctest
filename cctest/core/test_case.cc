#include "cctest/core/test_case.h"
#include "cctest/core/assertion_error.h"
#include "cctest/core/test_result.h"
#include "cctest/core/internal/test_case_method.h"

namespace cctest {

namespace {

struct Functor : TestCaseMethod {
  using Method = void(TestCase::*)();

  Functor(TestCase* self, Method method)
    : self(self), method(method) {
  }

private:
  bool operator()() const override {
    (self->*method)();
    return true;
  }

private:
  TestCase* self;
  Method method;
};

} // namespace

#define PROTECT(method) result.protect(Functor(this, &TestCase::method))

void TestCase::runBare(TestResult& result) {
  if (PROTECT(setUp)) {
    PROTECT(runTest);
  }
  PROTECT(tearDown);
}

void TestCase::run(TestResult& result) {
  result.startTestCase();
  runBare(result);
}

} // namespace cctest
