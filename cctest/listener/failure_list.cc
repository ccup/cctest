#include "cctest/listener/failure_list.h"

namespace cctest {

void FailureList::addFailure(const TestFailure& f) {
  failures.push_back(&f);
}

} // namespace cctest
