#ifndef HD8A7A410_095D_427A_BEC9_405E0884F6DF
#define HD8A7A410_095D_427A_BEC9_405E0884F6DF

#include "cctest/factory/test_factory.h"
#include "cctest/core/test_method.h"
#include "cctest/core/test_desc.h"

namespace cctest {

template<typename Fixture>
struct TestMethodFactory : TestFactory {
  TestMethodFactory(const char* desc, Method<Fixture> method)
      : desc(desc), method(method) {
  }

private:
  Test* make() const override {
    return new TestMethod<Fixture>(method, desc.name());
  }

private:
  TestDesc desc;
  Method<Fixture> method;
};

} // namespace cctest

#endif
