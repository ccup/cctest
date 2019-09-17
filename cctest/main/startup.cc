#include "cctest/main/startup.h"
#include "cctest/core/test_runner.h"
#include "cctest/factory/test_suite_factory.h"
#include "cctest/listener/text/text_progress.h"
#include <iostream>

namespace cctest {

void run_all_tests(int /* argc */, char** /* argv */) {
  TextProgress progress(std::cout);
  TestRunner runner(progress, TestSuiteFactory::root());
  runner.run();
}

} // namespace cctest

