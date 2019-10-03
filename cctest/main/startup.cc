#include "cctest/main/startup.h"
#include "cctest/core/test_runner.h"
#include "cctest/factory/test_suite_factory.h"
#include "cctest/listener/text/colorful_printer.h"
#include <iostream>

namespace cctest {

int run_all_tests(int /* argc */, char** /* argv */) {
  TestStatus status;
  ColorfulPrinter printer(std::cout);
  MultiListener listener({&status, &printer});

  TestRunner runner(listener, TestSuiteFactory::root());
  runner.run();
  return status.successful() ? EXIT_SUCCESS : EXIT_FAILURE;
}

} // namespace cctest

