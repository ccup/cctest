#ifndef HE7CED4CF_7B2A_4B82_86D9_0EA29C09E396
#define HE7CED4CF_7B2A_4B82_86D9_0EA29C09E396

namespace cctest {

struct Test;
struct TestResult;

struct BareTestSuite {
  virtual const Test& get() const = 0;
  virtual void runBare(TestResult&) = 0;

  virtual ~BareTestSuite() {}
};

} // namespace cctest

#endif
