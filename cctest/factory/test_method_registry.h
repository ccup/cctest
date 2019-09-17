#ifndef H17ECBE7F_AB24_48CD_A1ED_CBE0460C95C4
#define H17ECBE7F_AB24_48CD_A1ED_CBE0460C95C4

#include "cctest/base/singleton.h"
#include "cctest/base/keywords.h"
#include "cctest/factory/test_method_factory.h"
#include "cctest/factory/test_suite_factory.h"
#include <unordered_map>

namespace cctest {

template<typename Fixture>
CCTEST_GENERIC_SINGLETON(TestMethodRegistry, Fixture) CCTEST_EXTENDS(TestSuiteFactory) {
  void add(int id, const char *name, Method<Fixture> method) {
    if (!exist(id)) {
      registry.insert({id, {name, method}});
      TestSuiteFactory::add(registry.at(id));
    }
  }

private:
  Test* make() override {
    static Fixture dummy; // register all test methods to this.
    return TestSuiteFactory::make();
  }

private:
  bool exist(int id) const {
    return registry.find(id) != registry.end();
  }

private:
  std::unordered_map<int, TestMethodFactory<Fixture>> registry;
};

} // namespace cctest

#endif
