#include "cctest/core/test_desc.h"
#include "cctest/base/string_utils.h"
#include <unordered_map>
#include <regex>
#include <iostream>

namespace cctest {

static std::regex regex("^\\s*@\\{(.+)\\}(.+)$");

TestDesc::TestDesc(const char* desc) : times_(1), disable_(false) {
  std::cmatch result;
  if (std::regex_search(desc, result, regex)) {
    annotation(result.str(1));
    testname(result.str(2));
  } else { // without annotation
    testname(desc);
  }
}

void TestDesc::annotation(StringView prefix) {
  auto specs = strutils::split(prefix, ",");
  for (StringView spec : specs) {
    auto pair = spec.trim().split("=");
    auto rhs = pair.size() == 1 ? std::string("") : pair[1];
    save(pair[0], rhs);
  }
}

inline void TestDesc::testname(StringView name) {
  name_ = name.trim().to_s();
}

inline void TestDesc::enable(StringView) {
  disable_ = true;
}

inline void TestDesc::toTimes(StringView value) {
  times_ = strutils::to_uint32(value);
}

inline void TestDesc::toId(StringView id) {
  id_ = id.to_s();
}

inline void TestDesc::toDep(StringView dep) {
  dep_ = dep.to_s();
}

void TestDesc::save(StringView lhs, StringView rhs) {
  using Action = void(TestDesc::*)(StringView);
  static std::unordered_map<StringView, Action> actions = {
      {"disable", &TestDesc::enable},
      {"times",   &TestDesc::toTimes},
      {"id",      &TestDesc::toId},
      {"dep",     &TestDesc::toDep},
  };

  auto i = actions.find(lhs.trim());
  if (i != actions.end()) {
    (this->*i->second)(rhs.trim());
  }
}

const std::string& TestDesc::name() const {
  return name_;
}

const std::string& TestDesc::id() const {
  return id_;
}

const std::string& TestDesc::dep() const {
  return dep_;
}

int TestDesc::times() const {
  return times_;
}

bool TestDesc::disable() const {
  return disable_;
}

} // namespace cctest
