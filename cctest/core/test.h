#ifndef HE6105773_56D7_4E99_868F_8161DC208246
#define HE6105773_56D7_4E99_868F_8161DC208246

#include <string>

namespace cctest {

struct TestResult;

struct Test {
  explicit Test(const std::string& name = "");
  virtual ~Test() {}

  virtual const std::string& getName() const;

  virtual int countTestCases() const = 0;
  virtual void run(TestResult&) = 0;

private:
  std::string name;
};

} // namespace cctest

#endif
