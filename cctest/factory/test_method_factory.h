#ifndef HD8A7A410_095D_427A_BEC9_405E0884F6DF
#define HD8A7A410_095D_427A_BEC9_405E0884F6DF

#include "cctest/factory/test_factory.h"
#include "cctest/core/test_method.h"

namespace cctest {

template<typename Fixture>
struct TestMethodFactory : TestFactory {
  TestMethodFactory(const char *name, Method<Fixture> method)
      : name(name), method(method) {
  }

private:
  Test* make() const override {
    return new TestMethod<Fixture>(method, name);
  }

private:
  const char *name;
  Method<Fixture> method;
};

} // namespace cctest

#endif
