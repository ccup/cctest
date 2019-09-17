#include "cctest/core/test_fixture.h"
#include "cctest/core/test_method.h"
#include "cctest/core/test_suite.h"
#include "cctest/core/test_result.h"
#include "cctest/factory/test_suite_factory.h"
#include "cctest/factory/test_method_factory.h"
#include "cctest/listener/text/text_progress.h"
#include "cctest/base/self.h"
#include "cctest/base/singleton.h"
#include "cctest/base/keywords.h"
#include "gtest/gtest.h"
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace cctest;

namespace {

template<typename Fixture>
CCTEST_GENERIC_SINGLETON(TestMethodRegistry, Fixture) CCTEST_EXTENDS(TestSuiteFactory) {
  void add(int id, const char *name, Method<Fixture> method) {
    if (!exist(id)) {
      registry.insert({id, {name, method}});
      TestSuiteFactory::add(registry.at(id));
    }
  }

private:
  Test* make() override {
    static Fixture dummy; // register all test methods to this.
    return TestSuiteFactory::make();
  }

private:
  bool exist(int id) const {
    return registry.find(id) != registry.end();
  }

private:
  std::unordered_map<int, TestMethodFactory<Fixture>> registry;
};

struct AutoTestMethod {
  template <typename Fixture>
  AutoTestMethod(int id, const char* name, Method<Fixture> method) {
    auto& registry = TestMethodRegistry<Fixture>::inst();
    registry.add(id, name, method);
  }
};

struct StackSpec : TestFixture {
  std::stack<int> v;

  void setUp() override {
    v.push(1);
    v.push(2);
  }

  void test1() {
    ASSERT_EQ(2, v.top());
  }

  AutoTestMethod m1{1, "apply pop 0 time", &StackSpec::test1};

  void test2() {
    v.pop();
    ASSERT_EQ(1, v.top());
  }

  AutoTestMethod m2{2, "apply pop 1 time", &StackSpec::test2};

  void test3() {
    v.pop();
    v.pop();
    ASSERT_TRUE(v.empty());
  }

  AutoTestMethod m3{3, "apply pop 2 times", &StackSpec::test3};
};

struct TestRunner {
  TestRunner(TestListener&, TestFactory&);
  ~TestRunner();

  void run();

private:
  TestResult result;
  Test *root;
};

TestRunner::TestRunner(TestListener &listener, TestFactory &factory)
    : root(factory.make()) {
  result.addListener(listener);
}

TestRunner::~TestRunner() {
  delete root;
}

void TestRunner::run() {
  result.runRootTest(*root);
}

template<typename Fixture>
struct GenericAutoSpec: testing::Test {
protected:
  GenericAutoSpec() : progress(ss), runner(progress, factory()) {
  }

private:
  static TestFactory& factory() {
    return TestMethodRegistry<Fixture>::inst();
  }

protected:
  std::ostringstream ss;
  TextProgress progress;
  TestRunner runner;
};

using AutoStackSpec = GenericAutoSpec<StackSpec>;

TEST_F(AutoStackSpec, auto_register_test_cases) {
  runner.run();
  ASSERT_EQ("starting...\n***\nend.\n", ss.str());
}

struct QueueSpec : TestFixture {
  std::queue<int> q;

  void setUp() override {
    q.push(1);
    q.push(2);
  }

  void apply_pop_0_time() {
    ASSERT_EQ(1, q.front());
    ASSERT_EQ(2, q.back());
  }

  AutoTestMethod m1 { 1, "apply_pop_0_time", &QueueSpec::apply_pop_0_time };

  void apply_pop_1_time() {
    q.pop();
    ASSERT_EQ(2, q.front());
    ASSERT_EQ(2, q.back());
  }

  AutoTestMethod m2 { 2, "apply_pop_1_time", &QueueSpec::apply_pop_1_time };

  void apply_pop_2_times() {
    q.pop();
    q.pop();
    ASSERT_TRUE(q.empty());
  }

  AutoTestMethod m3 { 3, "apply_pop_2_times", &QueueSpec::apply_pop_2_times };
};

using AutoQueueSpec = GenericAutoSpec<QueueSpec>;

TEST_F(AutoQueueSpec, auto_register_test_cases) {
  runner.run();
  ASSERT_EQ("starting...\n***\nend.\n", ss.str());
}

} // namespace
