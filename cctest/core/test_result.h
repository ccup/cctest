#ifndef HC9E8B8E2_729D_469F_8C91_90EF3791FC8E
#define HC9E8B8E2_729D_469F_8C91_90EF3791FC8E

#include "cctest/core/multi_listener.h"
#include "cctest/except/test_failure.h"
#include "cctest/core/test_protector.h"

namespace cctest {

struct Test;
struct TestListener;
struct BareTestCase;
struct BareTestSuite;
struct BareTestOnce;

struct TestResult : MultiListener, private TestProtector {
  void runRootTest(Test&);
  void runTestCase(BareTestCase&);
  void runTestSuite(BareTestSuite&);
  void runTestOnce(BareTestOnce&);

private:
  bool protect(const TestFunctor&) override;
  TestResult& result() override;

private:
  void onFail(std::string who, std::string msg, bool failure);

private:
  std::vector<TestFailure> failures;
};

} // namespace cctest

#endif
