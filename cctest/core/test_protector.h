#ifndef H5AE4A350_14D4_4240_91AD_CBF726F25A47
#define H5AE4A350_14D4_4240_91AD_CBF726F25A47

namespace cctest {

struct TestFunctor;
struct TestResult;

struct TestProtector {
  virtual bool protect(const TestFunctor&) = 0;
  virtual TestResult& result() = 0;
  virtual ~TestProtector() {}
};

} // namespace cctest

#endif
