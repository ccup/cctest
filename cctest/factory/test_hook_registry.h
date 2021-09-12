#ifndef H344C0C8D_F2FF_4CE5_8B1E_3BA9B1CF7B3C
#define H344C0C8D_F2FF_4CE5_8B1E_3BA9B1CF7B3C

#include <vector>
#include "cctest/core/test_fixture.h"

namespace cctest {

struct TestHookRegistry : TestFixture {
  static TestHookRegistry& inst();
  ~TestHookRegistry() override;

  void add(TestFixture*);

private:
  void setUp() override;
  void tearDown() override;

private:
  std::vector<TestFixture*> hooks;
};

} // namespace cctest

#endif /* H344C0C8D_F2FF_4CE5_8B1E_3BA9B1CF7B3C */
