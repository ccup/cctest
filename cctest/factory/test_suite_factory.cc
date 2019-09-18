#include "cctest/factory/test_suite_factory.h"
#include "cctest/core/test_suite.h"

namespace cctest {

TestSuiteFactory::TestSuiteFactory(std::string name)
  : name(std::move(name)) {}

TestSuiteFactory& TestSuiteFactory::root() {
  static TestSuiteFactory inst("All Tests");
  return inst;
}

void TestSuiteFactory::add(TestFactory &f) {
  factories.push_back(&f);
}

Test* TestSuiteFactory::make() {
  auto suite = new TestSuite(name);
  for (auto f : factories) {
    suite->add(f->make());
  }
  return suite;
}

} // namespace cctest
