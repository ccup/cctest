#ifndef HB21A8177_A417_4721_A654_779B14936704
#define HB21A8177_A417_4721_A654_779B14936704

#include <utility>
#include "cctest/matcher/base/self_describing.h"

namespace cctest {

struct Description;

template<typename T>
struct SelfDescribingValue : SelfDescribing {
  explicit SelfDescribingValue(T value)
    : value(std::move(value)) {}

private:
  void describeTo(Description& desc) const override {
    desc.appendValue(value);
  }

private:
  T value;
};

} // namespace cctest

#endif
