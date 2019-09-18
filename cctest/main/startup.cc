#include "cctest/main/startup.h"
#include "cctest/core/test_runner.h"
#include "cctest/factory/test_suite_factory.h"
#include "cctest/listener/text/colorful_printer.h"
#include <iostream>

namespace cctest {

void run_all_tests(int /* argc */, char** /* argv */) {
  ColorfulPrinter printer(std::cout);
  TestRunner runner(printer, TestSuiteFactory::root());
  runner.run();
}

} // namespace cctest

