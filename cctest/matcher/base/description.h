#ifndef HD713D4AF_130B_49C1_A037_CA27F6A55204
#define HD713D4AF_130B_49C1_A037_CA27F6A55204

#include <string>

namespace cctest {

struct SelfDescribing;

struct Description {
  const std::string& toString() const;

  Description& appendText(const std::string &text);
  Description& appendDescriptionOf(const SelfDescribing &value);

  template<typename T>
  Description& appendValue(const T &value);

  template<typename C>
  Description& appendList
    ( const std::string &start
    , const std::string &separator
    , const std::string &end
    , const C& list);

  template<typename C>
  Description& appendValueList
    ( const std::string &start
    , const std::string &separator
    , const std::string &end
    , const C& list);

private:
  Description& append(const std::string&);

  template<typename C>
  Description& doAppendList(const std::string& sep, const C& list);

private:
  std::string desc;
};

} // namespace cctest

#include "cctest/matcher/base/description.inc"

#endif
