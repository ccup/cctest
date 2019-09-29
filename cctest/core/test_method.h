#ifndef HBC36D615_D4BB_449A_9829_16E8CE8EC076
#define HBC36D615_D4BB_449A_9829_16E8CE8EC076

#include "cctest/core/test_case.h"
#include "cctest/core/method.h"

namespace cctest {

template <typename Fixture>
struct TestMethod : TestCase {
  TestMethod(Method<Fixture> method, const std::string& name = "")
    : TestCase(name), method(method) {}

private:
  void setUp() override {
    self = new Fixture;
    self->setUp();
  }

  void runTest() override {
    (self->*method)();
  }

  void tearDown() override {
    self->tearDown();
    delete self;
  }

private:
  Fixture* self = nullptr;
  Method<Fixture> method;
};

} // namespace cctest

#endif
