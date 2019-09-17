#include "cctest/cctest.h"
#include <gtest/gtest.h>

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  cctest::run_all_tests(argc, argv);
  return RUN_ALL_TESTS();
}
