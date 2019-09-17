#ifndef H12189C51_AA86_4087_AF4E_DCB29721D4A2
#define H12189C51_AA86_4087_AF4E_DCB29721D4A2

#include "cctest/core/test_listener.h"
#include <vector>

namespace cctest {

struct TestFailure;

struct FailureList : TestListener {
  template <typename F>
  void foreach(F f) const {
    for (auto failure : failures) {
      f(*failure);
    }
  }

private:
  void addFailure(const TestFailure&) override;

private:
  std::vector<const TestFailure*> failures;
};

} // namespace cctest

#endif
