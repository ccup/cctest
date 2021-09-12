#include "cctest/core/test_case.h"
#include "cctest/core/test_result.h"
#include "cctest/core/method.h"
#include "cctest/core/test_functor.h"
#include "cctest/except/assertion_error.h"

namespace cctest {

namespace {

struct TestCaseFunctor : TestFunctor {
  TestCaseFunctor(TestCase* self, Method<TestCase> method, const char* place)
    : self(self), method(method), place(place) {
  }

private:
  const char* who() const override {
    return self->getName().c_str();
  }

  const char* where() const override {
    return place.c_str();
  }

  void operator()() const override {
    (self->*method)();
  }

private:
  TestCase* self;
  Method<TestCase> method;
  std::string place;
};

} // namespace

#define PROTECT(method) \
  p.protect(TestCaseFunctor(this, &TestCase::method, "in the "#method))

void TestCase::runBare(TestProtector& p) {
  if (PROTECT(setUp)) {
    PROTECT(runTest);
  }
  PROTECT(tearDown);
}

const Test& TestCase::get() const {
  return *this;
}

int TestCase::countTestCases() const {
  return 1;
}

void TestCase::run(TestResult& result) {
  result.runTestCase(*this);
}

} // namespace cctest
