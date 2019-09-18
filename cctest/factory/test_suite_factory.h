#ifndef HCCE8CCEB_5C40_4730_A2D6_21CF103D8F22
#define HCCE8CCEB_5C40_4730_A2D6_21CF103D8F22

#include <vector>
#include <string>
#include "cctest/factory/test_factory.h"

namespace cctest {

struct TestSuiteFactory : TestFactory {
  explicit TestSuiteFactory(std::string);
  void add(TestFactory&);

  static TestSuiteFactory& root();

protected:
  Test* make() const override;

private:
  std::string name;
  std::vector<TestFactory*> factories;
};

} // namespace cctest

#endif
