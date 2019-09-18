#ifndef HC1529C5B_742D_4014_BBBF_7533B3E13905
#define HC1529C5B_742D_4014_BBBF_7533B3E13905

#include <iostream>

#include "cctest/core/multi_listener.h"
#include "cctest/listener/collector/failure_list.h"
#include "cctest/listener/collector/test_collector.h"
#include "cctest/listener/collector/test_status.h"
#include "cctest/listener/collector/time_collector.h"

namespace cctest {

struct TestInfo;

struct ColorfulPrinter : MultiListener {
  explicit ColorfulPrinter(std::ostream& = std::cout);
  ~ColorfulPrinter();

private:
  void startTestRun(const Test&) override;
  void endTestRun(const Test&) override;

  void startTestSuite(const Test&) override;
  void endTestSuite(const Test&) override;

  void startTestCase(const Test&) override;
  void endTestCase(const Test&) override;

  void addFailure(const TestFailure&) override;

private:
  bool lastFailed;
  std::ostream& out;

  struct Writer;
  Writer* writer;

  TestStatus status;
  TestCollector collector;
  FailureList lister;
  TimeCollector clock;
};

} // namespace cctest

#endif
