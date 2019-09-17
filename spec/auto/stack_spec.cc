#include "cctest/core/test_fixture.h"
#include "cctest/core/test_method.h"
#include "cctest/core/test_suite.h"
#include "cctest/core/test_result.h"
#include "cctest/listener/text/text_progress.h"
#include "cctest/base/self.h"
#include "cctest/base/singleton.h"
#include "cctest/base/keywords.h"
#include "gtest/gtest.h"
#include <stack>
#include <vector>
#include <unordered_map>

using namespace cctest;

namespace {

struct TestFactory {
  virtual Test* make() = 0;
  virtual ~TestFactory() {}
};

struct TestSuiteFactory : TestFactory {
  void add(TestFactory&);

protected:
  Test* make() override;

private:
  std::vector<TestFactory*> factories;
};

void TestSuiteFactory::add(TestFactory &f) {
  factories.push_back(&f);
}

Test* TestSuiteFactory::make() {
  auto suite = new TestSuite;
  for (auto f : factories) {
    suite->add(f->make());
  }
  return suite;
}

template<typename Fixture>
struct TestMethodFactory : TestFactory {
  TestMethodFactory(const char *name, Method<Fixture> method) :
      name(name), method(method) {
  }

private:
  Test* make() override {
    return new TestMethod<Fixture>(method, name);
  }

private:
  const char *name;
  Method<Fixture> method;
};

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

struct AutoStackSpec : testing::Test {
protected:
  AutoStackSpec() : progress(ss), root(suite()) {
    result.addListener(progress);
  }

  ~AutoStackSpec() {
    delete root;
  }

protected:
  void run() {
    result.runRootTest(*root);
  }

  void assertOutput(const char* output) {
    ASSERT_EQ(ss.str(), output);
  }

private:
  static cctest::Test* suite() {
    TestFactory& factory = TestMethodRegistry<StackSpec>::inst();
    return factory.make();
  }

private:
  std::ostringstream ss;
  TextProgress progress;
  cctest::Test* root;
  TestResult result;
};

TEST_F(AutoStackSpec, auto_register_test_cases) {
  run();
  assertOutput("starting...\n***\nend.\n");
}

} // namespace
