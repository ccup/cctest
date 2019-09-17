#include "cctest/core/test_result.h"
#include "cctest/core/test_listener.h"
#include "cctest/core/internal/test_case_method.h"
#include "cctest/except/assertion_error.h"
#include <algorithm>

namespace cctest {

void TestResult::addListener(TestListener& listener) {
  listeners.push_back(&listener);
}

void TestResult::startTestCase(const Test& test) {
  for (auto listener : listeners) {
    listener->startTestCase(test);
  }
}

int TestResult::errorCount() const {
  return std::count_if(failures.begin(), failures.end(), [](const TestFailure& f) {
    return !f.isFailure();
  });
}

const std::vector<TestFailure>& TestResult::getFailures() const {
  return failures;
}

inline void TestResult::addFailure(std::string&& msg) {
  failures.emplace_back(std::move(msg), true);
  for (auto listener : listeners) {
    listener->addFailure(failures.back());
  }
}

inline void TestResult::addError(std::string&& msg) {
  failures.emplace_back(std::move(msg), false);
  for (auto listener : listeners) {
    listener->addFailure(failures.back());
  }
}

namespace {
  inline std::string msg(const char* why, const char* where, const char* what) {
    return std::string(why) + ' ' + where + '\n' + what;
  }

  struct NilException {
    const char* what() const {
      return "";
    }
  } const e;
}

#define ON_FAIL(except)  addFailure(msg(except, f.where(), e.what()))
#define ON_ERROR(except) addError(msg(except, f.where(), e.what()))

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
