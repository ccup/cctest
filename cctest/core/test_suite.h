#ifndef HEBA1EEE2_F46F_4F44_8247_10C8AB3D0FCA
#define HEBA1EEE2_F46F_4F44_8247_10C8AB3D0FCA

#include <vector>
#include "cctest/core/test.h"

namespace cctest {

struct TestSuite : Test {
  ~TestSuite();

  void add(Test* test);
  void run();

private:
  std::vector<Test*> tests;
};

} // namespace cctest

#endif
