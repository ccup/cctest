#ifndef HE6105773_56D7_4E99_868F_8161DC208246
#define HE6105773_56D7_4E99_868F_8161DC208246

#include <string>

namespace cctest {

struct TestResult;

struct Test {
  Test(const std::string& name = "");
  const std::string& getName() const;

  virtual void run(TestResult&) = 0;
  virtual ~Test() {}

private:
  std::string name;
};

} // namespace cctest

#endif
