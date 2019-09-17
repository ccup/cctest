#include "cctest/core/test_result.h"
#include "cctest/core/test_listener.h"
#include "cctest/core/internal/test_case_method.h"
#include "cctest/except/assertion_error.h"
#include <algorithm>

namespace cctest {

void TestResult::addListener(TestListener& listener) {
  listeners.push_back(&listener);
}

#define BOARDCAST(action) \
  for (auto listener : listeners) listener->action

void TestResult::startTestCase(const Test& test) {
  BOARDCAST(startTestCase(test));
}

void TestResult::endTestCase(const Test& test) {
  BOARDCAST(endTestCase(test));
}

inline void TestResult::addFailure(TestFailure&& fail) {
  failures.emplace_back(std::move(fail));
  BOARDCAST(addFailure(failures.back()));
}

inline void TestResult::onFail(std::string&& msg) {
  addFailure(TestFailure(std::move(msg), true));
}

inline void TestResult::onError(std::string&& msg) {
  addFailure(TestFailure(std::move(msg), false));
}

namespace {
  std::string msg(const char* why, const char* where, const char* what) {
    return std::string(why) + ' ' + where + '\n' + what;
  }

  struct NilException {
    const char* what() const {
      return "";
    }
  } const e;
}

#define ON_FAIL(except)  onFail(msg(except, f.where(), e.what()))
#define ON_ERROR(except) onError(msg(except, f.where(), e.what()))

bool TestResult::protect(const TestCaseMethod& f) {
  try {
    return f();
  } catch (const AssertionError& e) {
    ON_FAIL("assertion fail");
  } catch (const std::exception& e) {
    ON_ERROR("uncaught std::exception");
  } catch (...) {
    ON_ERROR("uncaught unknown exception");
  }
  return false;
}


} // namespace cctest
