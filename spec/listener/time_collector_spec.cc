#include "cctest/listener/collector/time_collector.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_case.h"
#include "cctest/core/test_suite.h"
#include "gtest/gtest.h"

using namespace cctest;

namespace {

struct TimeCollectorSpec : testing::Test {
protected:
  TimeCollectorSpec() {
    result.addListener(clock);
  }

  void run(cctest::Test& test) {
    result.runRootTest(test);
  }

  void assertTime(const TimeVal& val) {
    timeval max{0, 1000};  // 1000 us
    ASSERT_LT(val, TimeVal::by(max));
  }

protected:
  TestResult result;
  TimeCollector clock;
};

TEST_F(TimeCollectorSpec, should_be_successful) {
  TestSuite suite;
  suite.add(new TestCase);

  run(suite);

  assertTime(clock.caseTime());
  assertTime(clock.suiteTime());
  assertTime(clock.totalTime());
}

} // namespace

