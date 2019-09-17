#ifndef HB0068EC5_B819_436E_A05B_A1BCD3ADF856
#define HB0068EC5_B819_436E_A05B_A1BCD3ADF856

namespace cctest {

struct Test;

struct TestListener {
  virtual void startTestCase(const Test&) {}
  virtual ~TestListener() {}
};

} // namespace cctest

#endif
