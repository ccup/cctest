#ifndef HA70A13E6_14E3_4E91_8C50_D58B5BEB0DDC
#define HA70A13E6_14E3_4E91_8C50_D58B5BEB0DDC

#include <string>

namespace cctest {

struct TestFailure {
  TestFailure(std::string&& msg, bool failure);

  bool isFailure() const;
  const std::string& getTestName() const;
  const std::string& getExceptionMsg() const;

private:
  std::string msg;
  bool failure;
};

} // namespace cctest

#endif
