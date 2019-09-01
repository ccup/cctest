#ifndef HEBA1EEE2_F46F_4F44_8247_10C8AB3D0FCA
#define HEBA1EEE2_F46F_4F44_8247_10C8AB3D0FCA

#include <string>
#include <vector>
#include "cctest/core/test.h"

namespace cctest {

struct TestSuite : Test {
  TestSuite(const std::string& name = "");
  ~TestSuite();

  void add(Test* test);
  void run();

  const std::string& getName() const;

private:
  std::string name;
  std::vector<Test*> tests;
};

} // namespace cctest

#endif
