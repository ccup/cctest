#ifndef HCCE8CCEB_5C40_4730_A2D6_21CF103D8F22
#define HCCE8CCEB_5C40_4730_A2D6_21CF103D8F22

#include <vector>
#include "cctest/factory/test_factory.h"

namespace cctest {

struct TestSuiteFactory : TestFactory {
  void add(TestFactory&);

  static TestSuiteFactory& root();

protected:
  Test* make() override;

private:
  std::vector<TestFactory*> factories;
};

} // namespace cctest

#endif
