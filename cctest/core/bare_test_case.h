#ifndef H00FF0ED7_86D6_4C51_90F6_7E6EC833F1EB
#define H00FF0ED7_86D6_4C51_90F6_7E6EC833F1EB

namespace cctest {

struct Test;
struct TestProtector;

struct BareTestCase {
  virtual const Test& get() const = 0;
  virtual void runBare(TestProtector&) = 0;

  virtual ~BareTestCase() {}
};

} // namespace cctest

#endif
