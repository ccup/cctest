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
    self.setUp();
  }

  void runTest() override {
    (self.*method)();
  }

  void tearDown() override {
    self.tearDown();
  }

private:
  Fixture self;
  Method method;
};

} // namespace cctest

#endif
