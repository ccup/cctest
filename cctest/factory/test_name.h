#ifndef HE3FE562B_48F0_4A65_83BA_0FCB9791027C
#define HE3FE562B_48F0_4A65_83BA_0FCB9791027C

#include "cctest/base/string_view.h"

namespace cctest {

/**
 * TestName prefix contains test meta.
 * for example:
 * "@{disable, id=id1, deps=id0, times=3} real test name"
 * */
struct TestName {
  TestName(const char* fullname);

  int times() const;
  bool disable() const;

  const std::string& realname() const;
  const std::string& id() const;
  const std::string& dep() const;

private:
  void annotation(StringView);
  void save(StringView, StringView);
  void testname(StringView);

  void enable(StringView);
  void toTimes(StringView);
  void toId(StringView);
  void toDep(StringView);

private:
  int times_;
  bool disable_;
  std::string name_;
  std::string id_;
  std::string dep_;
};

} // namespace cctest

#endif
