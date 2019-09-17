#include "gtest/gtest.h"
#include "cctest/core/test_case.h"
#include "cctest/core/test_result.h"
#include "cctest/except/assertion_error.h"
#include "cctest/listener/test_collector.h"

using namespace cctest;

namespace {

struct TestCollectorSpec : testing::Test {
protected:
  void run(cctest::Test& test) {
    test.run(result);
  }

private:
  void SetUp() override {
    result.addListener(collector);
  }

protected:
  TestCollector collector;
  TestResult result;
};

TEST_F(TestCollectorSpec, run_one_simple_test) {
  TestCase test;
  run(test);
  ASSERT_EQ(1, collector.runCount());
}

} // namespace

