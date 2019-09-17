#ifndef H0F798A34_BDAD_4D58_9A69_F56A9CB0C59E
#define H0F798A34_BDAD_4D58_9A69_F56A9CB0C59E

#include <ostream>
#include "cctest/core/test_listener.h"

namespace cctest {

struct TextProgress : TestListener {
  explicit TextProgress(std::ostream&);

private:
  void startTestRun(const Test&) override;
  void startTestCase(const Test&) override;
  void addFailure(const TestFailure&) override;
  void endTestRun(const Test&) override;

private:
  std::ostream& out;
};

} // namespace cctest

#endif
