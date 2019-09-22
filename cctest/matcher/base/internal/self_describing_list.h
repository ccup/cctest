#ifndef H45BAF2B0_2509_4D34_AD51_7C0F34B56634
#define H45BAF2B0_2509_4D34_AD51_7C0F34B56634

#include <vector>
#include "cctest/matcher/base/internal/self_describing_value.h"

namespace cctest {

template<typename C>
struct SelfDescribingList {
  using value_type = SelfDescribingValue<typename C::value_type>;
  using iterator = typename std::vector<value_type>::iterator;
  using const_iterator = typename std::vector<value_type>::const_iterator;

  explicit SelfDescribingList(const C& list) {
    for (auto& e : list) {
      values.emplace_back(e);
    }
  }

  const_iterator begin() const {
    return values.begin();
  }

  const_iterator end() const {
    return values.end();
  }

  iterator begin() {
    return values.begin();
  }

  iterator end() {
    return values.end();
  }

private:
  std::vector<value_type> values;
};

} // namespace cctest

#endif
