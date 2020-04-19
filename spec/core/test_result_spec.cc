#include "cctest/cctest.h"
#include "cctest/core/test_result.h"
#include "cctest/listener/collector/failure_list.h"
#include "cctest/listener/collector/test_collector.h"

using namespace cctest;

namespace {

FIXTURE(TestCaseSpec) {
  FailureList list;
  TestCollector collector;
  TestResult result;

  BEFORE {
    result.addListener(collector);
    result.addListener(list);
  }

  void run(::Test& test) {
    test.run(result);
  }

  struct FailureOnRunningTest : TestCase {
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

  TEST("throw assertion error on run test") {
    FailureOnRunningTest test;
    run(test);

    ASSERT_EQ(1, collector.failCount());
  }

  TEST("extract except msg on running test failed") {
    FailureOnRunningTest test;
    run(test);

    list.foreach([&test](const TestFailure& fail){
      ASSERT_TRUE(fail.isFailure());
      ASSERT_EQ(test.expectMsg(), fail.getExceptionMsg());
    });
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

  TEST("throw assertion error on setup") {
    FailureOnSetUp test;
    run(test);

    ASSERT_EQ(1, collector.failCount());
    ASSERT_FALSE(test.wasRun);
  }

  struct FailureOnTearDown : TestCase {
    void tearDown() override {
      throw AssertionError("product.cc:57", "expected value == 2, but got 3");
    }
  };

  TEST("throw assertion error on tear down") {
    FailureOnTearDown test;
    run(test);
    ASSERT_EQ(1, collector.failCount());
  }

  struct ErrorOnRunningTest : TestCase {
    const char* expectMsg() const {
      return "uncaught std::exception in the runTest\n"
              "std::exception";
    }

    void runTest() override {
      throw std::exception();
    }
  };

  TEST("throw std exception on run test") {
    ErrorOnRunningTest test;
    run(test);
    ASSERT_EQ(1, collector.errorCount());
  }

  TEST("extract error msgt on running test failed") {
    ErrorOnRunningTest test;
    run(test);

    list.foreach([&test](const TestFailure& error){
      ASSERT_FALSE(error.isFailure());
      ASSERT_EQ(test.expectMsg(), error.getExceptionMsg());
    });
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

  TEST("throw unknown exception on running test") {
    UnknownErrorOnRunningTest test;
    run(test);
    ASSERT_EQ(1, collector.errorCount());
  }

  TEST("extract unknown error msg on running test failed") {
    UnknownErrorOnRunningTest test;
    run(test);

    list.foreach([&test](const TestFailure& error){
      ASSERT_FALSE(error.isFailure());
      ASSERT_EQ(test.expectMsg(), error.getExceptionMsg());
    });
  }

};

} // namespace
