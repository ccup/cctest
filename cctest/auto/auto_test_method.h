#ifndef H251D5941_391A_4E25_A55E_DA2656B4B6AD
#define H251D5941_391A_4E25_A55E_DA2656B4B6AD

#include "cctest/factory/test_method_registry.h"

namespace cctest {

struct AutoTestMethod {
  template <typename Fixture>
  AutoTestMethod(int id, const char* name, Method<Fixture> method) {
    auto& registry = TestMethodRegistry<Fixture>::inst();
    registry.add(id, name, method);
  }
};

} // namespace cctest

#endif
