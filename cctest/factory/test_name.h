#ifndef HE3FE562B_48F0_4A65_83BA_0FCB9791027C
#define HE3FE562B_48F0_4A65_83BA_0FCB9791027C

#include "cctest/base/string_view.h"

namespace cctest {

struct TestNameImpl;

/**
 * TestName prefix contains test meta.
 * for example:
 * "@{disable, id=id1, deps=id0, times=3} should do something"
 * */
struct TestName {
  TestName(const std::string& fullName);
  ~TestName();

private:
  TestNameImpl* impl;
};

} // namespace cctest

#endif
