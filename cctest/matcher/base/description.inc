#include "cctest/base/formatter.h"
#include "cctest/matcher/base/internal/self_describing_list.h"

namespace cctest {

template<typename C>
Description& Description::doAppendList(const std::string& sep, const C& list) {
  auto separate = false;
  for (auto &e : list) {
    separate ? append(sep) : (separate = true, append(""));
    appendDescriptionOf(e);
  }
  return *this;
}

template<typename T>
Description& Description::appendValue(const T &value) {
  desc += "<";
  desc += toTypeAndValueString(value);
  desc += ">";
  return *this;
}

template<typename C>
Description& Description::appendList
  ( const std::string &start
  , const std::string &separator
  , const std::string &end
  , const C& list) {
  return append(start).doAppendList(separator, list).append(end);
}

template<typename C>
Description& Description::appendValueList
  ( const std::string &start
  , const std::string &separator
  , const std::string &end
  , const C& list) {
  return appendList(start, separator, end, SelfDescribingList<C>(list));
}

} // namespace cctest
