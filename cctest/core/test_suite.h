#ifndef HEBA1EEE2_F46F_4F44_8247_10C8AB3D0FCA
#define HEBA1EEE2_F46F_4F44_8247_10C8AB3D0FCA

#include <vector>

namespace cctest {

struct TestCase;

struct TestSuite {
  ~TestSuite();

  void add(TestCase* test);
  void run();

private:
  std::vector<TestCase*> tests;
};

} // namespace cctest

#endif
