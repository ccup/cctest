#include "cctest/except/test_failure.h"

namespace cctest {

TestFailure::TestFailure(std::string name, std::string msg, bool failure)
  : name(std::move(name)), msg(std::move(msg)), failure(failure) {
}

bool TestFailure::isFailure() const {
  return failure;
}

const std::string& TestFailure::getTestName() const {
  return name;
}

const std::string& TestFailure::getExceptionMsg() const {
  return msg;
}

} // namespace cctest
