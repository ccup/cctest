#ifndef H5AE4A350_14D4_4240_91AD_CBF726F25A47
#define H5AE4A350_14D4_4240_91AD_CBF726F25A47

namespace cctest {

struct TestCaseMethod;

struct TestCaseProtector {
  virtual bool protect(const TestCaseMethod&) = 0;
  virtual ~TestCaseProtector() {}
};

} // namespace cctest

#endif
