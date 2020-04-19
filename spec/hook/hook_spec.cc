#include "cctest/cctest.h"
#include "cctest/hook/hook_registry.h"
#include <sstream>

using namespace cctest;

namespace {
std::stringstream before_all_stream;
std::stringstream after_all_stream;

BEFORE_ALL {
  before_all_stream << "A";
}

BEFORE_ALL {
  before_all_stream << "B";
}

AFTER_ALL {
  after_all_stream << "C";
}

AFTER_ALL {
  after_all_stream << "D";
}

FIXTURE(HooksTest) {
  AFTER {
    before_all_stream.str("");
    after_all_stream.str("");
  }

  TEST("should supoort keywards BEFORE_ALL") {
    // HookRegistry::before().exec();
    ASSERT_EQ("AB", before_all_stream.str());
  }

  TEST("should supoort keywards AFTER_ALL") {
    HookRegistry::after().exec();
    ASSERT_EQ("CD", after_all_stream.str());
  }
};

} // namespace
