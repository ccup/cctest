#include "cctest/factory/test_name.h"
#include "cctest/base/string_utils.h"
#include <unordered_map>
#include <regex>
#include <iostream>

namespace cctest {

namespace {
  std::regex regex("^\\s*@\\{(.+)\\}(.+)$");
} // namespace

TestName::TestName(const char* fullname) : times_(1), disable_(false) {
  std::cmatch result;
  if (std::regex_search(fullname, result, regex)) {
    annotation(result.str(1));
    testname(result.str(2));
  } else { // without annotation
    testname(fullname);
  }
}

void TestName::annotation(StringView prefix) {
  auto specs = strutils::split(prefix, ",");
  for (StringView spec : specs) {
    auto pair = spec.trim().split("=");
    auto rhs = pair.size() == 1 ? std::string("") : pair[1];
    save(pair[0], rhs);
  }
}

void TestName::save(StringView lhs, StringView rhs) {
  using Action = void(TestName::*)(StringView);
  static std::unordered_map<StringView, Action> actions = {
      {"disable", &TestName::enable},
      {"times",   &TestName::toTimes},
      {"id",      &TestName::toId},
      {"dep",     &TestName::toDep},
  };

  auto i = actions.find(lhs.trim());
  if (i != actions.end()) {
    (this->*i->second)(rhs.trim());
  }
}

void TestName::testname(StringView name) {
  name_ = std::string(name.trim());
}

void TestName::enable(StringView) {
  disable_ = true;
}

void TestName::toTimes(StringView value) {
  times_ = strutils::to_uint32(value);
}

void TestName::toId(StringView id) {
  id_ = std::string(id);
}

void TestName::toDep(StringView dep) {
  dep_ = std::string(dep);
}

const std::string& TestName::realname() const {
  return name_;
}

const std::string& TestName::id() const {
  return id_;
}

const std::string& TestName::dep() const {
  return dep_;
}

int TestName::times() const {
  return times_;
}

bool TestName::disable() const {
  return disable_;
}

} // namespace cctest
