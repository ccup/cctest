#include "cctest/factory/test_name.h"
#include "cctest/base/string_view.h"
#include "cctest/base/string_utils.h"
#include <regex>
#include <unordered_map>

namespace cctest {

static std::regex regex("^@\\{(.+)\\s*(.+)\\}");

struct TestNameImpl {
  TestNameImpl(const std::string& fullName) : times(1), disable(false) {
    std::smatch result;
    if (std::regex_search(std::string(fullName), result, regex)) {
      others(result.str(1));
      name = result.str(2);
    }
  }

private:
  using Action = void(TestNameImpl::*)(StringView);

  void save(StringView lhs, StringView rhs) {
    static std::unordered_map<std::string, Action> actions = {
        {"disable", &TestNameImpl::disable_},
        {"times",   &TestNameImpl::times_},
        {"id",      &TestNameImpl::id_},
        {"deps",    &TestNameImpl::deps_},
    };

    auto found = actions.find(std::string(lhs));
    if (found != actions.end()) {
      (this->*found->second)(rhs);
    }
  }

private:
  void others(const std::string& prefix) {
    auto specs = strutils::split(prefix, ",");
    for (StringView spec : specs) {
      auto pair = spec.trim().split("=");
      auto rhs = pair.size() == 1 ? StringView("") : pair[1];
      save(pair[0], rhs);
    }
  }

private:
  void disable_(StringView) {
    disable = true;
  }

  void times_(StringView value) {
    times = strutils::to_uint32(value);
  }

  void id_(StringView value) {
    id = std::string(value);
  }

  void deps_(StringView value) {
    deps = std::string(value);
  }

private:
  int times;
  bool disable;
  std::string id;
  std::string name;
  std::string deps;
};

TestName::TestName(const std::string& fullName)
  : impl(new TestNameImpl(fullName)) {}

TestName::~TestName() {
  delete impl;
}

} // namespace cctest
