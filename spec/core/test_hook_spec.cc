#include "cctest/cctest.h"
#include "cctest/factory/test_hook_registry.h"
#include <sstream>

using namespace cctest;

namespace {

std::stringstream stream;

HOOK(Hook1) {
  BEFORE {
    stream << "A";
  }

  AFTER {
    stream << "D";
  }
};

HOOK(Hook2) {
  BEFORE {
    stream << "B";
  }

  AFTER {
    stream << "C";
  }
};

FIXTURE(HooksTest) {
  TestFixture& hook = TestHookRegistry::inst();

  AFTER {
    stream.str("");
  }

  TEST("supoort before all") {
    // hook.setUp();
    ASSERT_EQ("AB", stream.str());
  }

  TEST("supoort after all") {
    hook.tearDown();
    ASSERT_EQ("CD", stream.str());
  }
};

} // namespace
