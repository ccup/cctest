#include "cctest/core/test.h"

namespace cctest {

Test::Test(const std::string& name) : name(name) {
}

const std::string& Test::getName() const {
  return name;
}

} // namespace cctest
