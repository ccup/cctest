#ifndef HBC36D615_D4BB_449A_9829_16E8CE8EC076
#define HBC36D615_D4BB_449A_9829_16E8CE8EC076

#include "cctest/core/test_case.h"

namespace cctest {

template <typename Fixture>
struct TestMethod : TestCase {
private:
  using Method = void(Fixture::*)();

public:
  TestMethod(Method method) : method(method) {
  }

private:
  void setUp() override {
    self = fixture = new Fixture;
    self->setUp();
  }

  void runTest() override {
    (fixture->*method)();
  }

  void tearDown() override {
    self->tearDown();
    delete fixture;
  }

private:
  Fixture* fixture = nullptr;
  TestFixture* self = nullptr;
  Method method;
};

} // namespace cctest

#endif
