#ifndef H848BC4AC_32FE_441A_A9F3_52CDD1D78F97
#define H848BC4AC_32FE_441A_A9F3_52CDD1D78F97

namespace cctest {

struct Test;

struct TestFactory {
  virtual Test* make() = 0;
  virtual ~TestFactory() {}
};

} // namespace cctest

#endif
