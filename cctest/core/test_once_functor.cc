#include "cctest/core/test_once_functor.h"

namespace cctest {

TestOnceFunctor::TestOnceFunctor(Method method, const std::string& scope, const char* name)
    : method(method), place("in the "){
  place += scope;
  place += "::";
  place += name;
}

const char* TestOnceFunctor::where() const {
  return place.c_str();
}

void TestOnceFunctor::operator()() const{
  method();
}

} // namespace cctest
