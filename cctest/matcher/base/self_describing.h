#ifndef H7FA0354F_611B_4C92_828F_B142978B0158
#define H7FA0354F_611B_4C92_828F_B142978B0158

namespace cctest {

struct Description;

struct SelfDescribing {
  virtual ~SelfDescribing() {}
  virtual void describeTo(Description& desc) const = 0;
};

} // namespace cctest

#endif
