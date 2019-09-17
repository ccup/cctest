#ifndef HB7C42AA9_BBDF_49BE_84B0_EBCD9E4B9CCB
#define HB7C42AA9_BBDF_49BE_84B0_EBCD9E4B9CCB

#include "cctest/core/test_result.h"

namespace cctest {

struct TestFactory;

struct TestRunner {
  TestRunner(TestListener&, TestFactory&);
  ~TestRunner();

  void run();

private:
  TestResult result;
  Test *root;
};

} // namespace cctest

#endif
