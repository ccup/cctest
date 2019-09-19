#include "cctest/cctest.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_suite.h"
#include "cctest/listener/collector/time_collector.h"

using namespace cctest;

namespace {

FIXTURE(TimeCollectorSpec) {
  TestResult result;
  TimeCollector clock;

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

  TEST("should be successful") {
    TestSuite suite;
    suite.add(new TestCase);

    run(suite);

    assertTime(clock.caseTime());
    assertTime(clock.suiteTime());
    assertTime(clock.totalTime());
  }
};



} // namespace

