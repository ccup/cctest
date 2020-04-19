#ifndef H179B809D_2067_4913_9B5A_17A74E2AFFAB
#define H179B809D_2067_4913_9B5A_17A74E2AFFAB

#include "cctest/core/test_functor.h"
#include <string>

namespace cctest {

struct TestOnceFunctor : TestFunctor {
  using Method = void(*)();

  TestOnceFunctor(Method method, const std::string& scope, const char* name);

private:
  const char* where() const override;
  void operator()() const override;

private:
  Method method;
  std::string place;
};

} // namespace cctest

#endif /* H179B809D_2067_4913_9B5A_17A74E2AFFAB */
