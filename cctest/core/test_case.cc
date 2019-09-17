#include "cctest/core/test_case.h"
#include "cctest/core/test_result.h"
#include "cctest/core/internal/test_case_method.h"
#include "cctest/except/assertion_error.h"

namespace cctest {

namespace {

struct Functor : TestCaseMethod {
  using Method = void(TestCase::*)();

  Functor(TestCase* self, Method method, const char* place)
    : self(self), method(method), place(place) {
  }

private:
  const char* where() const override {
    return place;
  }

  bool operator()() const override {
    (self->*method)();
    return true;
  }

private:
  TestCase* self;
  Method method;
  const char* place;
};

} // namespace

#define PROTECT(method) \
  p.protect(Functor(this, &TestCase::method,  "in the "#method))

void TestCase::runBare(TestCaseProtector& p) {
  if (PROTECT(setUp)) {
    PROTECT(runTest);
  }
  PROTECT(tearDown);
}

const Test& TestCase::get() const {
  return *this;
}

void TestCase::run(TestResult& result) {
  result.runTestCase(*this);
}

} // namespace cctest
