#include "cctest/main/startup.h"
#include "cctest/core/test_runner.h"
#include "cctest/factory/test_suite_factory.h"
#include "cctest/listener/text/colorful_printer.h"
#include <iostream>

namespace cctest {

int run_all_tests(int /* argc */, char** /* argv */) {
  ColorfulPrinter printer(std::cout);
  TestRunner(printer, TestSuiteFactory::root()).run();
  return 0;
}

} // namespace cctest

