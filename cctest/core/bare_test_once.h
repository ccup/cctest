#ifndef H02CDBC79_0DE0_47E9_A087_D12F2BBAB30D
#define H02CDBC79_0DE0_47E9_A087_D12F2BBAB30D

namespace cctest {

struct Test;
struct TestProtector;

struct BareTestOnce {
  virtual const Test& get() const = 0;
  virtual void runBare(TestProtector&) = 0;

  virtual ~BareTestOnce() {}
};

} // namespace cctest


#endif /* H02CDBC79_0DE0_47E9_A087_D12F2BBAB30D */
