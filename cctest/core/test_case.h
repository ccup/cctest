#ifndef H7785F505_8D19_4C0A_8549_C4A62CD88C76
#define H7785F505_8D19_4C0A_8549_C4A62CD88C76

namespace cctest {

struct TestCase {
  virtual ~TestCase() {}

  void run();

private:
  virtual void setUp() {}
  virtual void runTest() = 0;
  virtual void tearDown() {}
};

} // namespace cctest

#endif
