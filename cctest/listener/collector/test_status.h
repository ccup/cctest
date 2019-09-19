#ifndef H0AE72DDC_5590_4D3D_AC28_EF2FFE85561F
#define H0AE72DDC_5590_4D3D_AC28_EF2FFE85561F

#include "cctest/core/test_listener.h"

namespace cctest {

struct TestStatus : TestListener {
  TestStatus();
  bool successful() const;

private:
  void addFailure(const TestFailure&) override;

private:
  bool succ;
};

} // namespace cctest

#endif
