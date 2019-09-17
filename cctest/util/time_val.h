#ifndef H7B512A87_3C48_47F0_8D5E_0CE9AA25B6A0
#define H7B512A87_3C48_47F0_8D5E_0CE9AA25B6A0

#include <sys/time.h>
#include "cctest/util/struct_wrapper.h"

namespace cctest {

CCTEST_STRUCT_WRAPPER(TimeVal, timeval) {
  TimeVal();
  void now();

  bool operator<(const TimeVal&) const;
  TimeVal& operator-=(const TimeVal&);
};

} // namespace cctest

#endif
