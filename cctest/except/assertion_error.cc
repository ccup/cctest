#include "cctest/except/assertion_error.h"
#include <sstream>
#include <iostream>

namespace cctest {

namespace {

std::string source(const char* file, int line) {
  std::stringstream ss;
  ss << file << ":" << line;
  return ss.str();
}

} // namespace

AssertionError::AssertionError
  ( const char* file, int line
  , const std::string& msg)
  : AssertionError(source(file, line), msg) {
}

AssertionError::AssertionError
  ( const std::string& src
  , const std::string& msg)
  : msg(src + "\n" + msg) {
}

const char* AssertionError::what() const noexcept {
  return msg.c_str();
}

} // namespace cctest
