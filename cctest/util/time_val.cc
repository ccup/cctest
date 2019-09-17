#include "cctest/util/time_val.h"

namespace cctest {

TimeVal::TimeVal() {
  tv_sec  = 0;
  tv_usec = 0;
}

void TimeVal::now() {
  gettimeofday(this, 0);
}

bool TimeVal::operator<(const TimeVal& rhs) const {
  if (tv_sec < rhs.tv_sec) return true;
  if (rhs.tv_sec < tv_sec) return false;
  return tv_usec < rhs.tv_usec;
}

TimeVal& TimeVal::operator-=(const TimeVal& start) {
  while (tv_usec < start.tv_usec) {
    tv_usec += 1000000;
    tv_sec--;
  }
  tv_usec -= start.tv_usec;
  tv_sec  -= start.tv_sec;
  return *this;
}

} // namespace cctest
