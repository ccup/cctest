#include "gtest/gtest.h"
#include "cctest/core/assertion_error.h"
#include "cctest/core/test_result.h"
#include "cctest/core/test_case.h"

using namespace cctest;

namespace {

struct TestResultSpec : testing::Test {
protected:
  void run(cctest::Test& test) {
    test.run(result);
  }

protected:
  TestResult result;
};

struct FailureOnRunTest : TestCase {
  const char* expectMsg() const {
    return "assertion fail in the runTest\n"
           "product.cc:57\n"
           "expected value == 2, but got 3";
  }

private:
  void runTest() override {
    throw AssertionError("product.cc:57", "expected value == 2, but got 3");
  }
};

TEST_F(TestResultSpec, throw_assertion_error_on_run_test) {
  FailureOnRunTest test;
  run(test);

  ASSERT_EQ(1, result.failCount());
}

TEST_F(TestResultSpec, assert_except_msg_on_running_test_failed) {
  FailureOnRunTest test;
  run(test);

  auto& fails = result.getFailures();
  ASSERT_EQ(1, fails.size());

  auto& fail = fails[0];
  ASSERT_TRUE(fail.isFailure());
  ASSERT_EQ(test.expectMsg(), fail.getExceptionMsg());
}

struct FailureOnSetUp : TestCase {
  bool wasRun = false;

private:
  void setUp() override {
    throw AssertionError("product.cc:57", "expected value == 2, but got 3");
  }

  void runTest() override {
    wasRun = true;
  }
};

TEST_F(TestResultSpec, throw_assertion_error_on_setup) {
  FailureOnSetUp test;
  run(test);

  ASSERT_EQ(1, result.failCount());
  ASSERT_FALSE(test.wasRun);
}

struct FailureOnTearDown : TestCase {
  void tearDown() override {
    throw AssertionError("product.cc:57", "expected value == 2, but got 3");
  }
};

TEST_F(TestResultSpec, throw_assertion_error_on_tear_down) {
  FailureOnTearDown test;
  run(test);
  ASSERT_EQ(1, result.failCount());
}

struct ErrorOnRunningTest : TestCase {
  const char* expectMsg() const {
    return "uncaught std::exception in the runTest\n"
           "std::exception";
  }

private:
  void runTest() override {
    throw std::exception();
  }
};

TEST_F(TestResultSpec, throw_std_exception_on_run_test) {
  ErrorOnRunningTest test;
  run(test);
  ASSERT_EQ(1, result.errorCount());
}

TEST_F(TestResultSpec, extract_error_msgt_on_running_test_failed) {
  ErrorOnRunningTest test;
  run(test);

  auto& errors = result.getErrors();
  ASSERT_EQ(1, errors.size());
  ASSERT_EQ(test.expectMsg(), errors.front());
}

struct NilException {};

struct UnknownErrorOnRunningTest : TestCase {
  const char* expectMsg() const {
    return "uncaught unknown exception in the runTest\n";
  }

private:
  void runTest() override {
    throw NilException();
  }
};

TEST_F(TestResultSpec, throw_unknown_exception_on_running_test) {
  UnknownErrorOnRunningTest test;
  run(test);
  ASSERT_EQ(1, result.errorCount());
}

TEST_F(TestResultSpec, extract_unknown_error_msg_on_running_test_failed) {
  UnknownErrorOnRunningTest test;
  run(test);

  auto& errors = result.getErrors();
  ASSERT_EQ(1, errors.size());
  ASSERT_EQ(test.expectMsg(), errors.front());
}


} // namespace
