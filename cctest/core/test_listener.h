#ifndef HB0068EC5_B819_436E_A05B_A1BCD3ADF856
#define HB0068EC5_B819_436E_A05B_A1BCD3ADF856

namespace cctest {

struct Test;
struct TestFailure;

struct TestListener {
  virtual void startTestRun(const Test&) {}
  virtual void endTestRun(const Test&) {}

  virtual void startTestOnce(const Test&) {}
  virtual void endTestOnce(const Test&) {}

  virtual void startTestSuite(const Test&) {}
  virtual void endTestSuite(const Test&) {}

  virtual void startTestCase(const Test&) {}
  virtual void endTestCase(const Test&) {}

  virtual void addFailure(const TestFailure&) {}

  virtual ~TestListener() {}
};

} // namespace cctest

#endif
