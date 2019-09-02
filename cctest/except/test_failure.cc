#include "cctest/except/test_failure.h"

namespace cctest {

TestFailure::TestFailure(std::string&& msg, bool failure)
  : msg(std::move(msg)), failure(failure) {
}

bool TestFailure::isFailure() const {
  return failure;
}

const std::string& TestFailure::getExceptionMsg() const {
  return msg;
}

} // namespace cctest
