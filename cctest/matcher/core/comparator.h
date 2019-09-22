#ifndef H5038E44D_A8CD_4B61_89B2_C09235ED2A94
#define H5038E44D_A8CD_4B61_89B2_C09235ED2A94

#include "cctest/matcher/base/description.h"

namespace cctest {

template<typename T, typename F>
struct Comparator {
protected:
  Comparator(std::string relationship, T expected)
    : relationship(std::move(relationship))
    , expected(std::move(expected)) {
  }

public:
  void describeTo(Description& desc) const {
    desc.appendText("a value ")
        .appendText(relationship)
        .appendText(" ")
        .appendValue(expected);
  }

  template <typename V>
  bool matches(const V& actual) const {
    return functor(actual, expected);
  }

  void describeMismatch(const T& actual, Description& desc) const {
    desc.appendValue(actual)
        .appendText(" ")
        .appendText(relationship)
        .appendText(" ")
        .appendValue(expected)
        .appendText(" got false");
  }

protected:
  std::string relationship;
  T expected;
  F functor;
};

} // namespace cctest

#endif
