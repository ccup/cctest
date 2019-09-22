#include "cctest/matcher/base/description.h"
#include "cctest/matcher/base/self_describing.h"

namespace cctest {

Description& Description::append(const std::string &text) {
  desc += text;
  return *this;
}

Description& Description::appendText(const std::string &text) {
  return append(text);
}

Description& Description::appendDescriptionOf(const SelfDescribing &value) {
  value.describeTo(*this);
  return *this;
}

const std::string& Description::toString() const {
  return desc;
}

} // namespace cctest
