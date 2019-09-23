#ifndef H17ECBE7F_AB24_48CD_A1ED_CBE0460C95C4
#define H17ECBE7F_AB24_48CD_A1ED_CBE0460C95C4

#include "cctest/factory/test_method_factory.h"
#include "cctest/factory/test_suite_factory.h"
#include <unordered_map>

namespace cctest {

template<typename Fixture>
struct TestMethodRegistry : TestSuiteFactory {
  using TestSuiteFactory::TestSuiteFactory;

  static TestMethodRegistry<Fixture>& inst(const char* name = "") {
    static TestMethodRegistry<Fixture> registry(name);
    return registry;
  }

  void add(int id, const char *name, Method<Fixture> method) {
    if (!exist(id)) {
      registry.insert({id, {name, method}});
      TestSuiteFactory::add(registry.at(id));
    }
  }

private:
  Test* make() const override {
    // register all test methods to TestMethodRegistry<Fixture>, then
    // TestMethodRegistry<Fixture>::add will collect all TestMethod belong to it.
    static Fixture dummy;
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
