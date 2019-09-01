#ifndef H2EF71F13_3C81_40F5_A187_225248B6C4B7
#define H2EF71F13_3C81_40F5_A187_225248B6C4B7

namespace cctest {

struct TestCaseMethod {
  virtual const char* where() const = 0;
  virtual bool operator()() const = 0;
  virtual ~TestCaseMethod() {}
};

} // namespace cctest

#endif
