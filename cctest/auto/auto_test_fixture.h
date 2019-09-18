#ifndef HC072EA23_AA1A_4C29_9635_2A954831DA04
#define HC072EA23_AA1A_4C29_9635_2A954831DA04

#include "cctest/factory/test_method_registry.h"
#include "cctest/factory/test_suite_factory.h"

namespace cctest {

template<typename Fixture>
struct AutoTestFixture {
  AutoTestFixture(const char* name) {
    auto &root = TestSuiteFactory::root();
    auto &leaf = TestMethodRegistry<Fixture>::inst(name);
    root.add(leaf);
  }
};

} // namespace cctest

#endif
